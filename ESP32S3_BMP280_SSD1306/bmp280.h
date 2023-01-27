#pragma once

#include <Adafruit_BMP280.h>



#define BMP280_SDA 10
#define BMP280_SCL 11
#define BMP280_GND 12


Adafruit_BMP280 bmp(&Wire1); // I2C


Adafruit_Sensor *bmp_temp = bmp.getTemperatureSensor();
Adafruit_Sensor *bmp_pressure = bmp.getPressureSensor();

void bmp280_pins_setup() {
  pinMode(BMP280_GND, OUTPUT);
  digitalWrite(BMP280_GND, LOW);
}

void bmp280_init() {
  Wire1.begin(BMP280_SDA, BMP280_SCL);

  if (!bmp.begin(0x76)) {
    Serial.println(F("Could not find a valid BMP280 sensor, check wiring or "
                     "try a different address!"));
    while (1) delay(10);
  }

  /* Default settings from datasheet. */
  bmp.setSampling(Adafruit_BMP280::MODE_FORCED,     /* Operating Mode. */
                  Adafruit_BMP280::SAMPLING_X2,     /* Temp. oversampling */
                  Adafruit_BMP280::SAMPLING_X16,    /* Pressure oversampling */
                  Adafruit_BMP280::FILTER_X16,      /* Filtering. */
                  Adafruit_BMP280::STANDBY_MS_500); /* Standby time. */

  bmp_temp->printSensorDetails();
}

float temperature = 0;
float pressure = 0;
float altitude = 0;

void bmp280_force_measure() {
  // must call this to wake sensor up and get new measurement data
  // it blocks until measurement is complete
  if (bmp.takeForcedMeasurement()) {
    // can now print out the new measurements
    // Serial.print(F("Temperature = "));
    temperature = bmp.readTemperature();
    Serial.print(temperature);
    // Serial.println(" *C");
    Serial.print("  ");

    // Serial.print(F("Pressure = "));
    pressure = bmp.readPressure();
     Serial.print(pressure);
     Serial.print("  ");
    // Serial.println(" Pa");

    // Serial.print(F("Approx altitude = "));
    altitude = bmp.readAltitude(1013.25);
    Serial.print(altitude); /* Adjusted to local forecast! */
    // Serial.println(" m");
    Serial.println();
  } else {
    Serial.println("Forced measurement failed!");
  }
}
