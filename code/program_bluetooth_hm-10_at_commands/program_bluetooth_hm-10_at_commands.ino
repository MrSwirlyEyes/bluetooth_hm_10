// Basic serial communication with Bluetooth HM-10
// Uses serial monitor for communication with Bluetooth HM-10
//
//  Pins
//  Arduino pin 2 (RX) to HM-10 TX
//  Arduino pin 3 to voltage divider then to HM-10 RX
//  Connect GND from the Arduiono to GND on the HM-10
//
// When a command is entered in to the serial monitor on the computer 
// the Arduino will relay it to the HM-10
//

#include <SoftwareSerial.h>

SoftwareSerial BTSerial(3, 2); // RX | TX

void setup() {
  Serial.begin(9600);
  Serial.println("Enter AT commands:");
  BTSerial.begin(9600);  // HM-10 default speed in AT command more
}

void loop() {
  // Keep reading from HM-10 and send to Arduino Serial Monitor
  if (BTSerial.available()) { Serial.write(BTSerial.read()); }

  // Keep reading from Arduino Serial Monitor and send to HM-10
  if (Serial.available()) { BTSerial.write(Serial.read()); }
}
