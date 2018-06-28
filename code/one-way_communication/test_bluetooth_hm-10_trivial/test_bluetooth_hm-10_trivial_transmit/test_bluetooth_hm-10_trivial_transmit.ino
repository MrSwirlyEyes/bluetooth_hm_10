// Basic serial communication with Bluetooth HM-10
// Transmit a trivial string through the Bluetooth HM-10
//
//  Arduino to HM-10 connections
//  Arduino pin 2 (TX) to voltage divider then to HM-10 RX
//  Arduino pin 3 to HM-10 TX
//  Connect GND from the Arduiono to GND on the HM-10
//
// When a command is entered in to the serial monitor on the computer 
// the Arduino will relay the command to the HM-10


// Library to make a Software UART
#include <SoftwareSerial>;

#define RX 3
#define TX 2

#define BAUDRATE 9600
 
SoftwareSerial BTSerial(RX, TX); // (RX, TX)
 
void setup() {

  // Start Serial Monitor for feedback
  Serial.begin(BAUDRATE);

  // HM-10 default speed in AT command mode
  BTSerial.begin(BAUDRATE);
}
 
void loop() {
  // Send a string for the bluetooth module to transmit
  BTSerial.print("Hello");

  // Print the same string to the Serial Monitor for feedback
  Serial.print("Hello");
  
  delay(1000);
}
