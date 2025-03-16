#include "Tecnoclub_SX1278.h"
#include "Tecnoclub_ST7789.h"

// Anything defined in a nameless namespace is private for the file
namespace {
SX1278 radio = new Module(SX1278_NSS, SX1278_DIO0, SX1278_RESET, SX1278_DIO1);

// save transmission state between loops
int transmissionState = RADIOLIB_ERR_NONE;

bool available = true;

// flag to indicate that a packet was sent
volatile bool transmittedFlag = false;

// this function is called when a complete packet
// is transmitted by the module
// IMPORTANT: this function MUST be 'void' type
//            and MUST NOT have any arguments!
// Read into ISRs for more information
void setFlag(void) {
  // we sent a packet, set the flag
  transmittedFlag = true;
}

void waitForTransmissionFinish() {
  while (!available) {
    delay(10);
  }
}
} // namespace

namespace Radio {
void init() {
  // initialize SX1278 with default settings
  Serial.print(F("[SX1278] Initialising ... "));
  Display::tft.print(F("[SX1278] Initialising ... "));
  int state = radio.begin();
  if (state == RADIOLIB_ERR_NONE) {
    Serial.println(F("success!"));
    Display::tft.println(F("success!"));
  } else {
    Serial.print(F("failed, code "));
    Display::tft.print(F("failed, code "));
    Serial.println(state);
    Display::tft.println(state);
  }

  // set the function that will be called
  // when packet transmission is finished
  radio.setPacketSentAction(setFlag);
}

int16_t startTransmit(String &str, uint8_t addr) {
  return (startTransmit(str.c_str(), addr));
}

int16_t startTransmit(const char *str, uint8_t addr) {
  return (startTransmit((uint8_t *)str, strlen(str), addr));
}

int16_t startTransmit(const uint8_t *data, size_t len, uint8_t addr) {
  waitForTransmissionFinish();
  transmissionState = radio.startTransmit(data, len, addr);
  return transmissionState;
}

// Check whether a transmission has finished, and clean up if it has.
// Should be called often.
bool checkTransmitFinish() {
  if (!transmittedFlag) {
    return false;
  }

  // reset flag
  transmittedFlag = false;
  available = true;

  Display::tft.setCursor(0, 140);

  if (transmissionState == RADIOLIB_ERR_NONE) {
    // packet was successfully sent
    Serial.println(F("transmission finished!"));
    Display::tft.print(F("done!"));

    // NOTE: when using interrupt-driven transmit method,
    //       it is not possible to automatically measure
    //       transmission data rate using getDataRate()

  } else {
    Serial.print(F("failed, code "));
    Display::tft.print(F("failed, code "));
    Serial.println(transmissionState);
    Display::tft.println(transmissionState);
  }

  // clean up after transmission is finished
  // this will ensure transmitter is disabled,
  // RF switch is powered down etc.
  radio.finishTransmit();

  return true;
}
} // namespace Radio
