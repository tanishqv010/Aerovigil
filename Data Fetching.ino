#include "DFRobot_SHT20.h"
#include <SoftwareSerial.h>

DFRobot_SHT20 sht20(&Wire, SHT20_I2C_ADDR);
SoftwareSerial B(0,1);
int smoke_detector = A0;
int x = 5;

void setup(){
    pinMode(smoke_detector, INPUT);
    B.begin(9600);
    sht20.initSHT20();
    delay(100);
    Serial.println("Sensor init finish!");
    sht20.checkSHT20();
}

void  loop(){
    int sensor_read = analogRead(smoke_detector);
    float humd = sht20.readHumidity();
    float temp = sht20.readTemperature();
    B.println(sensor_read);
    B.print(",");
    B.print(temp, 1);
    B.print("C");
    B.print(",");
    B.print(humd, 1);
    B.print("%");
    delay(100);
    B.print(";");
}
