# Aerovigil

Don't hesitate to ⭐ the repo if you enjoy our work !

## Table of Content :
- [I. Objective](https://github.com/tanishqv010/Aerovigil?tab=readme-ov-file#i-objective)
- [II. Features](https://github.com/tanishqv010/Aerovigil?tab=readme-ov-file#ii-features)
- [III. Methodology](https://github.com/tanishqv010/Aerovigil?tab=readme-ov-file#iii-methodology)
- [IV. Circuit](https://github.com/tanishqv010/Aerovigil?tab=readme-ov-file#vi-circuit)
- [V. Data Sources](https://github.com/tanishqv010/Aerovigil?tab=readme-ov-file#v-data-sources)
- [VI. Model](https://github.com/tanishqv010/Aerovigil?tab=readme-ov-file#vi-model)
- [VII. Requirements](https://github.com/tanishqv010/Aerovigil?tab=readme-ov-file#vii-requirements)

## I. Objective
The primary objective of this project is to develop a surveillance system using a custom-built drone equipped with advanced sensors. The system aims to monitor vegetation-rich areas, particularly forests, to detect potential forest fires at an early stage. The key focus is on providing a reliable and efficient solution for early warning and intervention, ultimately minimising the damage caused by forest fires.

## II. Features
1. **Sensor Integration**:
- Integrate high-resolution cameras for visual monitoring of vegetation and potential fire sources.
- Integrate temperature and humidity sensor(s) for detecting heat anomalies associated with fire.
- Integrate gas sensors to identify early signs of smoke or combustible gases.

2. **Real-time Data Transmission**:
- Establish a reliable communication system for real-time data transmission from the drone to the ground station using MQTT protocol over TCP/IP.
- Implement a secure and efficient data transfer protocol for transmitting surveillance data.

3. **Fire Prediction and Detection**:
- Implement a machine learning-based fire prediction algorithm using environmental sensor data and live weather parameters like wind speed.
- Integrate predictive models to assess the likelihood of fire outbreaks based on current conditions.
- Use a threshold-based system to detect fire based on smoke sensor data.

4. **Weather Data Integration**:
- Integrate OpenWeatherMap API to fetch real-time wind and rain data from the drone's geographical location.
- Improve prediction accuracy by incorporating live weather conditions.

4. **Emergency Response System**:
- Integrate an alert system to notify relevant authorities in the event of a detected forest fire.
- Include GPS coordinates in the alert to facilitate a rapid response.

## III. Execution
1. **Design and Prototyping**:
- Design the drone frame and structure to accommodate all necessary components.
- Complete all the processes of calibration anf flight testing.

2. **Sensor Integration**:
- Integrate temparature and humidity sensors, and gas sensors onto the drone platform.
- Calibrate and test each sensor for optimal performance in a forest environment.

3. **Fire Prediction and Detection Implementation**:
- Deploy pre-trained machine learning models onboard or on a ground station for real-time predictions.
- Integrate real-time environmental sensor data and weather API responses for enhanced prediction reliability.

4. **System Integration**:
- Integrate all subsystems, including flight system, sensors, fire prediction, and detection, into a cohesive and unified system.
- Ensure seamless communication and interoperability between different components.

## IV. Circuit
The following image shows the circuit diagram of the sensor-based system initially developed using an Arduino. A similar setup, involving the same sensors (MQ-2 for smoke, SHT-20 for temperature and humidity), was later replicated on an ESP32 microcontroller. This transition enabled MQTT-based data transmission over TCP/IP using Wi-Fi for real-time environmental monitoring and fire prediction.<br/>
![image](https://github.com/tanishqv010/Aerovigil/blob/main/Static/Circuit.png)

## V. Data Sources
We made some alterations in the dataset of burned area of forest fires, in the East Portugal region, available on the UCI Machine Learning Repository.
<br/>Link - https://archive.ics.uci.edu/dataset/162/forest+fires
<br/>Altered dataset comprises of the following Independent factors:
- Temperature (in degree Celsius)
- Relative Humidity (on a scale of 1 to 100)
- Wind Speed (int m/s)
- Rain (1 or 0, i.e., Yes or No)
And we are predicting the Categorical Variable
- Forest Fire (1 or 0)

## VI. Model
On the modified dataset, we trained a Random Forest Classifier and fine-tuned it using the Bayesian Optimization Technique, achieving an accuracy of 66.35%. The trained model is saved and used for real-time prediction using incoming sensor data and weather API responses.

## VII. Requirements
- Drone / Parts to make Drone
- ESP32
- SHT-20 Humidity and Temperature Sensor Probe
- MQ-2 Smoke Sensor
- Breadboard and wiring components
- Internet Connectivity for MQTT and Weather API
- OpenWeatherMap API Key
