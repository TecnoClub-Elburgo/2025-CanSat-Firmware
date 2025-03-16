#include <Arduino.h>

#include "Tecnoclub_ST7789.h"
#include "Tecnoclub_SX1278.h"

#include <BlueDot_BME280_TSL2591.h>

#include <Wire.h>

BlueDot_BME280_TSL2591 bme280;
BlueDot_BME280_TSL2591 tsl2591;

// put function declarations here:

void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);

  Display::init(); // Init ST7789 240x240

  // initialize SX1278 with default settings
  Radio::init();

  // start transmitting the first packet
  Serial.println(F("[SX1278] Sending first packet ... "));
  Display::tft.println(F("[SX1278] Sending first packet ... "));

  // you can transmit C-string or Arduino string up to
  // 255 characters long
  Radio::startTransmit("Hello World!");

  // you can also transmit byte array up to 255 bytes long
  /*
    byte byteArr[] = {0x01, 0x23, 0x45, 0x67,
                      0x89, 0xAB, 0xCD, 0xEF};
    transmissionState = radio.startTransmit(byteArr, 8);
  */

  Serial.print(F("[BME280 + TSL2591] Initialising... "));
  Display::tft.print(F("[BMETSL] Initialising... "));

  bme280.parameter.I2CAddress =
      0x77; // The BME280 is hardwired to use the I2C Address 0x77
  tsl2591.parameter.I2CAddress = 0x29;
  Wire.begin();

  // Set BME280 + TSL2591 up
  tsl2591.parameter.gain = 0b01;
  tsl2591.parameter.integration = 0b000;
  tsl2591.config_TSL2591();

  bme280.parameter.sensorMode = 0b11;
  bme280.parameter.IIRfilter = 0b100;
  bme280.parameter.humidOversampling = 0b101;
  bme280.parameter.tempOversampling = 0b101;
  bme280.parameter.pressOversampling = 0b101;
  bme280.parameter.pressureSeaLevel = 1013.25;
  bme280.parameter.tempOutsideCelsius = 15;

  bool bmeFound = bme280.init_BME280() == 0x60;
  bool tslFound = tsl2591.init_TSL2591() == 0x50;
  if (!bmeFound) {
    Serial.print(F("BME280 could not be found! "));
    Display::tft.print(F("BME not found! "));
  }
  if (!tslFound) {
    Serial.print(F("TSL2591 could not be found!"));
    Display::tft.print(F("TSL not found!"));
  }
  if (bmeFound && tslFound) {
    Serial.print(F("success!"));
    Display::tft.print(F("success!"));
  }

  Serial.println();
  Display::tft.println();

  Display::tft.println();
  Display::tft.print("Setup took ");
  Display::tft.setTextColor(ST77XX_MAGENTA);
  Display::tft.print(millis() / 1000);
  Display::tft.setTextColor(ST77XX_WHITE);
  Display::tft.println(" seconds.");
}

// counter to keep track of transmitted packets
int count = 0;

float temperature;
float humidity;
float pressure;
float illuminance;
String measurements;
void loop() {
  // put your main code here, to run repeatedly:

  temperature = bme280.readTempC();
  humidity = bme280.readHumidity();
  pressure = bme280.readPressure();
  illuminance = tsl2591.readIlluminance_TSL2591();

  measurements = "T: " + (String)temperature + " H: " + (String)humidity +
                 " P: " + (String)pressure + " I: " + (String)illuminance;

  Display::tft.setCursor(0, 170);
  Display::tft.fillRect(0, 170, 240, 40, ST77XX_BLACK);
  Serial.println("[BME280 + TSL2591] Measurements: " + measurements);
  Display::tft.print("[BMETSL] Measurements: " + measurements);

  // check if the previous transmission finished
  if (Radio::checkTransmitFinish()) {

    // wait a second before transmitting again
    delay(1000);

    // send another one
    Display::tft.setCursor(0, 120);
    Display::tft.fillRect(0, 120, 240, 40, ST77XX_BLACK);

    Serial.print(F("[SX1278] Sending another packet ... "));
    Serial.print(count++);
    Display::tft.print(F("[SX1278] Sending packet # "));
    Display::tft.print(count);
    Display::tft.print(F(" ... "));

    // you can transmit C-string or Arduino string up to
    // 255 characters long
    String str = "Hello World! #" + String(count) + measurements;
    Radio::startTransmit(str);

    // you can also transmit byte array up to 255 bytes long
    /*
      byte byteArr[] = {0x01, 0x23, 0x45, 0x67,
                        0x89, 0xAB, 0xCD, 0xEF};
      transmissionState = radio.startTransmit(byteArr, 8);
      */
  }
}

// put function definitions here:
int myFunction(int x, int y) { return x + y; }
