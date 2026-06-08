#include <Wire.h>
#include <Ambimate.h>
#include <Adafruit_BMP085.h>

Ambimate amb;
Adafruit_BMP085 bmp;

bool ambFound = false;
bool pressureFound = false;

const int micPin = A0;

void setup() {
  Serial.begin(9600);
  delay(1000);

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

    Serial.print("Raw Audio: ");
    Serial.println(amb.AUDIO);

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

    Serial.print("Nearby Motion: ");
    Serial.println(amb.EVENT ? "TRUE" : "FALSE");
  } else {
    Serial.println("AmbiMate Measurement Failed");
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

void readBOB09868Mic() {
  int signalMax = 0;
  int signalMin = 1023;

  unsigned long startTime = millis();

  while (millis() - startTime < 50) {
    int sample = analogRead(micPin);

    if (sample > signalMax) {
      signalMax = sample;
    }

    if (sample < signalMin) {
      signalMin = sample;
    }
  }

  int peakToPeak = signalMax - signalMin;

  Serial.println("----- BOB-09868 Microphone -----");

  Serial.print("Mic Min: ");
  Serial.println(signalMin);

  Serial.print("Mic Max: ");
  Serial.println(signalMax);

  Serial.print("Sound Level Raw Peak-to-Peak: ");
  Serial.println(peakToPeak);
}

void loop() {
  Serial.println("============================");

  readAmbiMate();
  Serial.println();

  readPressureSensor();
  Serial.println();

  readBOB09868Mic();
  Serial.println();

  delay(2000);
}
