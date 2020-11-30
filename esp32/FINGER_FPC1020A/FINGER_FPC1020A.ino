#include <M5StickC.h>  
#include "finger.h"

/*
 * I think this is based on the OEM (M5Stack) sketch, but I'm not sure how it ended up in Arduino IDE.
 * Changed finger.cpp and this ino to include M5StickC; Adjust Serial2.begin(...)
 * Should work on any grove port as long as pin numbers are updated. Eg, should work on M5Atom (edit Serial2.begin)
 * (C) 2020-Nov-30 https://github.com/supaplextor/arduino-esp-sketches/tree/master/esp32/FINGER_FPC1020A 
 * - No Warranty express or implied.
 * 
 */

uint8_t res1;
uint8_t userNum;           //User number
FingerPrint FP_M;

void setup() {
  M5.begin();
  
  Serial.begin(115200);
  Serial.printf("Finger example\n");

  Serial2.begin(19200, SERIAL_8N1, 33, 32);  // this is M5StickC - not tested on M5atom
  
  delay(100);
  M5.update();
  delay(25);

  if (M5.BtnB.isPressed()) {
    res1 = FP_M.fpm_deleteAllUser();
  
    if (res1 == ACK_SUCCESS) {
      Serial.println("Delete All User Successful");
    }
    else {
      Serial.println("Delete All User Failed");
    }
  }

}

void loop() {
  delay(25);
  if (M5.BtnA.wasPressed()) {

    Serial.println("Matching");

    res1 = FP_M.fpm_compareFinger();
   
    if (res1 == ACK_SUCCESS) {
      userNum = FP_M.fpm_getUserNum();
      Serial.printf("Success; user [%d]\n",userNum);
    }
    if (res1 == ACK_NOUSER) {
      Serial.println("No Such User");
    }
    if (res1 == ACK_TIMEOUT) {
      Serial.println("Timeout");
    }
  }

  if (M5.BtnB.wasPressed()) {
    Serial.println("Fingerprint Typing");

    res1 = FP_M.fpm_addUser(++userNum, 1);
    if (res1 == ACK_SUCCESS) {
      Serial.println("Success");
    }
    else if (res1 == ACK_FAIL) {
      Serial.println("Fail");
    }
    else if (res1 == ACK_FULL) {
      Serial.println("Full");
    }
    else {
      Serial.println("Timeout");
    }
  }

  M5.update();
}
