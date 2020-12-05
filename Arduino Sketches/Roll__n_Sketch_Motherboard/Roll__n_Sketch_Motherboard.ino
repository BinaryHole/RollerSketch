#include <SPI.h>
#include <NRFLite.h>

// define NRF transciever unit
NRFLite _radio;

// define radio constants
const int RADIO_NUM = 0;
const int TRANS_NUM = 1;
const int CE        = 9;
const int CSN       = 10;

// define a radio packet's data
struct RadioPacket {
  uint16_t pitch;
  uint16_t roll;
};

// declare global RadioData variable
RadioPacket _radioData;

void setup() {
  // open the serial port
  Serial.begin(115200);
  Serial.println("Started.");

  // setup the radio
  _radio.init(RADIO_NUM, CE, CSN);
}

void loop() {
  // read the incoming radio data
  readRadio();

  // print the radio data to the serial port
  sendDataToSerial();
}

void readRadio() {
  while (_radio.hasData()) {
    _radio.readData(&_radioData);
  }
}

void sendDataToSerial() {
  if (Serial.available() > 0 && Serial.read() == 'r') {
    Serial.print(_radioData.pitch);
    Serial.print(",");
    Serial.println(_radioData.roll);
  }
}
