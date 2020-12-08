#include <SPI.h>
#include <NRFLite.h>
#include <HCSR04.h>

// define NRF transciever unit
NRFLite _radio;

// define US sensor unit
const int TRIG = 7;
const int ECHO = 6;
UltraSonicDistanceSensor usSensor(TRIG, ECHO);

// define radio constants
const int RADIO_NUM = 0;
const int TRANS_NUM = 1;
const int CE        = 9;
const int CSN       = 10;

// define button inputs
const int BUTTON_1 = 4;
const int BUTTON_2 = 3;
const int BUTTON_3 = 2;

// define a radio packet's data
struct RadioPacket {
  uint16_t pitch;
  uint16_t roll;
};

// declare global RadioData variable
RadioPacket _radioData;

// declare global button values
int button1Val = 0;
int button2Val = 0;
int button3Val = 0;

// define global ultrasonic value
int usDistanceVal = 0;

void setup() {
  // open the serial port
  Serial.begin(115200);
  Serial.println("Started.");

  // setup the radio
  _radio.init(RADIO_NUM, CE, CSN);

  // setup the buttons
  pinMode(BUTTON_1, INPUT_PULLUP);
  pinMode(BUTTON_2, INPUT_PULLUP);
  pinMode(BUTTON_3, INPUT_PULLUP);
}

void loop() {
  // read the incoming radio data
  readRadio();

  // read the button values
  readButtons();

  // read the ultrasonic distance value
  readUsSensor();

  // print the radio data to the serial port
  sendDataToSerial();
  //forceDataToSerial();
}

void readButtons() {
  button1Val = !digitalRead(BUTTON_1);
  button2Val = !digitalRead(BUTTON_2);
  button3Val = !digitalRead(BUTTON_3);
}

void readUsSensor() {
  double newDistanceVal = usSensor.measureDistanceCm();

  if (0 <= newDistanceVal && newDistanceVal <= 50) {
    //usDistanceVal = newDistanceVal;
    usDistanceVal = floor(newDistanceVal);
  }
}

void readRadio() {
  while (_radio.hasData()) {
    _radio.readData(&_radioData);
  }
}

void forceDataToSerial() {
  Serial.print(_radioData.pitch);
  Serial.print(",");
  Serial.print(_radioData.roll);
  Serial.print(",");
  Serial.print(button1Val);
  Serial.print(",");
  Serial.print(button2Val);
  Serial.print(",");
  Serial.print(button3Val);
  Serial.print(",");
  Serial.print(usDistanceVal);
  
  Serial.println();
}

void sendDataToSerial() {
  if (Serial.available() > 0 && Serial.read() == 'r') {
    Serial.print(_radioData.pitch);
    Serial.print(",");
    Serial.print(_radioData.roll);
    Serial.print(",");
    Serial.print(button1Val);
    Serial.print(",");
    Serial.print(button2Val);
    Serial.print(",");
    Serial.print(button3Val);
    Serial.print(",");
    Serial.print(usDistanceVal);
    
    Serial.println();
  }
}
