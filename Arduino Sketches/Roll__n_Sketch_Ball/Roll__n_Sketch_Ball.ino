#include <Wire.h>
#include <MPU6050.h>
#include <SPI.h>
#include <NRFLite.h>
#include <Math.h>

// define NRF transciever unit
NRFLite _radio;

// define radio constants
const int RADIO_NUM = 1;
const int RECIP_NUM = 0;
const int CE        = 9;
const int CSN       = 10;

// define a radio packet's data
struct RadioPacket {
  uint16_t pitch;
  uint16_t roll;
};

// declare global RadioData variable
RadioPacket _radioData;


// define mpu unit
MPU6050 _mpu;

void setup() {
  // open the serial port
  Serial.begin(115200);

  // setup the mpu
  _mpu.begin(MPU6050_SCALE_2000DPS, MPU6050_RANGE_2G);

  // setup the radio
  _radio.init(RADIO_NUM, CE, CSN);
}

void loop() {
  // read the gyro's values
  Vector normAccel = _mpu.readNormalizeAccel();

  // calculate pitch and roll
  double pitch = -(atan2(normAccel.XAxis, sqrt(normAccel.YAxis*normAccel.YAxis + normAccel.ZAxis*normAccel.ZAxis))*180.0)/M_PI;
  double roll = (atan2(normAccel.YAxis, normAccel.ZAxis)*180.0)/M_PI;

  // remap pitch and roll to 0-999 range
  int newPitch = floor(map(pitch, -180, 180, 0, 999));
  int newRoll  = floor(map(roll, -180, 180, 0, 999));
  
  // update the radio data
  updateRadioData(newPitch, newRoll);

  // send the radio packet
  sendRadioData();

  printMPU(newPitch, newRoll);

  // delay before next loop
  delay(10);
}

void sendRadioData() {
  // send the current _radioData to the recipient radio unit
  _radio.send(RECIP_NUM, &_radioData, sizeof(_radioData)); 
}

void updateRadioData(double pitch, double roll) {
  _radioData.pitch  = pitch;
  _radioData.roll   = roll;
}

void printMPU(double pitch, double roll) {
  Serial.print(" Pitch= ");
  Serial.print(pitch);
  Serial.print(" Roll= ");
  Serial.println(roll);
}
