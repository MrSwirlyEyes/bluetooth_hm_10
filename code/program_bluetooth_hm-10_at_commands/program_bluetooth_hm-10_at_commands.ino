// Basic serial communication with Bluetooth HM-10
// Uses serial monitor for communication with Bluetooth HM-10
//
//  Pins
//  Arduino pin 2 (TX) to voltage divider then to HM-10 RX
//  Arduino pin 3 to HM-10 TX
//  Connect GND from the Arduiono to GND on the HM-10
//
// When a command is entered in to the serial monitor on the computer 
// the Arduino will relay the command to the HM-10


// Library to make a Software UART
#include <SoftwareSerial.h>

#define RX 3
#define TX 2

char c = ' ';
boolean new_line = true;

// Instantiation of a Software UART
SoftwareSerial BTSerial(RX, TX); // (RX, TX)

void setup() {  
  Serial.begin(9600);
  
  // HM-10 default speed in AT command mode
  BTSerial.begin(9600);
  
  Serial.println("Enter AT commands:");
}

void loop() {
  // Keep reading from HM-10 and send to Arduino Serial Monitor
  if (BTSerial.available())
    Serial.write(BTSerial.read());

  // Keep reading from Arduino Serial Monitor and send to HM-10
  if (Serial.available()) { 
    c = Serial.read();

    // Do not send newline ('\n') nor carriage return ('\r') characters
    if(c != 10 && c != 13)
      BTSerial.write(c);

    // If a newline ('\n') is true; print newline + prompt symbol; toggle
    if (new_line) { 
      Serial.print("\r\n>");
      new_line = false;
    }
    
    Serial.write(c);
    
    // If a newline ('\n') is read, toggle
    if (c == 10)
      new_line = true;
  }
}
