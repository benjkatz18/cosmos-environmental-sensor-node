#include <Wire.h>
#include <Ambimate.h>
#include <Adafruit_BMP085.h>

Ambimate amb;
Adafruit_BMP085 bmp;

bool ambFound = false;
bool pressureFound = false;

void setup() {

  Serial.begin(9600);
  while (!Serial);

  Serial.println("Starting Sensors...");

  if (amb.begin()) {
    ambFound = true;
    Serial.println("AmbiMate Connected!");
  } else {
    Serial.println("AmbiMate Not Found");
  }

  if (bmp.begin()) {
    pressureFound = true;
    Serial.println("Pressure Sensor Connected!");
  } else {
    Serial.println("Pressure Sensor Not Found");
  }
}

void readAmbiMate() {

  if (!ambFound) {
    Serial.println("AmbiMate Not Connected");
    return;
  }

  if (amb.Measure()) {

    Serial.println("----- AmbiMate -----");

    Serial.print("Temperature (C): ");
    Serial.println(amb.TEMP);

    Serial.print("Humidity (%): ");
    Serial.println(amb.HUM);

    Serial.print("Light: ");
    Serial.println(amb.LUM);

    Serial.print("TVOC: ");
    Serial.println(amb.TVOC);

    Serial.print("eCO2: ");
    Serial.println(amb.eCO2);

    Serial.print("Voltage: ");
    Serial.println(amb.VOLTS);

    Serial.print("Motion/Event: ");
    Serial.println(amb.EVENT ? "TRUE" : "FALSE");
  }
}

void readPressureSensor() {

  if (!pressureFound) {
    Serial.println("Pressure Sensor Not Connected");
    return;
  }

  Serial.println("----- Pressure Sensor -----");

  Serial.print("Pressure (Pa): ");
  Serial.println(bmp.readPressure());

  Serial.print("Pressure (hPa): ");
  Serial.println(bmp.readPressure() / 100.0);

  Serial.print("Temperature (C): ");
  Serial.println(bmp.readTemperature());

  Serial.print("Altitude (m): ");
  Serial.println(bmp.readAltitude());
}

void loop() {

  Serial.println("============================");

  readAmbiMate();

  Serial.println();

  readPressureSensor();

  Serial.println();
  delay(2000);
}