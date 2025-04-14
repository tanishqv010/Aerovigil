#include <WiFi.h>
#include <PubSubClient.h>
#include <Wire.h>
#include "DFRobot_SHT20.h"

// Sensor setup
DFRobot_SHT20 sht20(&Wire, SHT20_I2C_ADDR);
#define MQ2_PIN 34  // Change if needed

// WiFi credentials
const char* ssid = "myesp";
const char* password = "12107300";

// MQTT broker
const char* mqtt_server = "5.196.95.208";
const int mqtt_port = 1883;
const char* mqtt_topic = "aerovigil/data";

// MQTT client
WiFiClient espClient;
PubSubClient client(espClient);

void setup_wifi() {
  delay(10);
  Serial.print("Connecting to WiFi");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected. IP address: ");
  Serial.println(WiFi.localIP());
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Connecting to MQTT...");
    if (client.connect("ESP32Client")) {
      Serial.println("connected.");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" retrying in 2s...");
      delay(2000);
    }
  }
}

void setup() {
  Serial.begin(115200);
  Wire.begin();
  sht20.initSHT20();
  delay(100);
  sht20.checkSHT20();
  Serial.println("Sensor init finish!");

  setup_wifi();
  client.setServer(mqtt_server, mqtt_port);
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  int sensor_read = analogRead(MQ2_PIN);
  float temp = sht20.readTemperature();
  float humd = sht20.readHumidity();

  // Check if readings are valid
  if (isnan(temp) || isnan(humd)) {
    Serial.println("Failed to read from SHT20 sensor!");
    return;
  }

  // Create JSON-style payload string
  char payload[128];
  snprintf(payload, sizeof(payload), "{\"smoke\":%d,\"temp\":%.1f,\"humidity\":%.1f}", sensor_read, temp, humd);
  
  // Publish data
  if (client.publish(mqtt_topic, payload)) {
    Serial.println("Data published successfully:");
    Serial.println(payload);
  } else {
    Serial.println("Failed to publish data");
  }

  delay(1000);  // Send data every 1 second
}