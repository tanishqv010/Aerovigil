import paho.mqtt.client as mqtt
import json
import warnings
import joblib
import pandas as pd
import requests

warnings.filterwarnings("ignore")

# Load the model
rf_classifier = joblib.load('aerovigil.joblib')

# MQTT details
mqtt_broker = "5.196.95.208"
mqtt_port = 1883
mqtt_topic = "aerovigil/data"

# Weather API
OPENWEATHER_API_KEY = "19afcf230caf60baef22721aa216ae4c"
CITY = "Hamirpur"
WEATHER_API_URL = f"http://api.openweathermap.org/data/2.5/weather?q={CITY}&appid={OPENWEATHER_API_KEY}&units=metric"

SMOKE_THRESHOLD = 500  # Adjust as needed

def fetch_weather():
    try:
        response = requests.get(WEATHER_API_URL)
        weather = response.json()
        wind_speed = weather['wind']['speed']  # in m/s
        rain = weather.get('rain', {}).get('1h', 0)  # rain volume in last hour (mm)
        if(rain > 0):
            rain = 1
        return wind_speed, rain
    except Exception as e:
        print("Weather API error:", e)
        return None, None

def on_connect(client, userdata, flags, rc):
    print(f"Connected to MQTT broker with result code {rc}")
    client.subscribe(mqtt_topic)

def on_message(client, userdata, msg):
    payload = msg.payload.decode("utf-8")
    print(f"Message received: {payload}")
    
    try:
        data = json.loads(payload)
        smoke = data.get("smoke")
        temp = data.get("temp")
        humd = data.get("humidity")

        if None in [smoke, temp, humd]:
            print("Invalid data received, skipping.")
            return

        # Check for smoke threshold
        if smoke > SMOKE_THRESHOLD:
            print("Fire detected (smoke level is high).")
        else:
            wind, rain = fetch_weather()
            if wind is None:
                print("Skipping prediction due to weather data failure.")
                return

            # Prepare data
            prediction_data = pd.DataFrame([[temp, humd, wind, rain]], columns=['temp', 'humidity', 'wind', 'rain'])

            # Predict
            pred = rf_classifier.predict(prediction_data)
            print("Prediction:", "Fire will occur." if pred[0] == 1 else "Fire will not occur.")
    
    except json.JSONDecodeError:
        print("Error decoding JSON")

client = mqtt.Client()
client.on_connect = on_connect
client.on_message = on_message

client.connect(mqtt_broker, mqtt_port, 60)
client.loop_forever()