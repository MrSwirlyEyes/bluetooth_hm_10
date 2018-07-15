// Basic serial communication with Bluetooth HM-10
// Receive a trivial string through the Bluetooth HM-10
//
//  Arduino to HM-10 connections
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

#define BAUDRATE 9600
 
SoftwareSerial BTSerial(RX, TX); // (RX, TX)

struct Data {
  int a;
  int b;
  int c;
  byte signature;
} data;

union Packet {
  Data data;
  byte pkt_size[sizeof(Data)];
} pkt;

byte signature = 0xDEAD;
 
void setup() {
  // Start Serial Monitor for feedback
  Serial.begin(BAUDRATE);

  // HM-10 default speed in AT command mode
  BTSerial.begin(BAUDRATE);
}
 
void loop() {  
  bluetooth_receive();
  delay(25);
}

void bluetooth_receive() {
  // Keep reading from HM-10 and send to Arduino Serial Monitor  
  if(BTSerial.available() > 0) {
    for (int i = 0; i < sizeof(Packet); i++) {
      pkt.pkt_size[i] = BTSerial.read();
    }
  }

  if(pkt.data.signature == signature) {
    Serial.print("(a,b,c)=(");
    Serial.print(pkt.data.a); Serial.print(",");
    Serial.print(pkt.data.b); Serial.print(",");
    Serial.print(pkt.data.c); Serial.println(")");
  } else {
    Serial.println("ERROR");
    BTSerial.flush();
  }  
}
