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
 
SoftwareSerial BTSerial(RX, TX); // (RX, TX)

struct Data {
  int a;
  int b;
  int c;
  byte signature;
};

union Packet {
  Data data;
  byte pkt_size[sizeof(Data)];
} pkt_tx, pkt_rx;

byte signature = 0xDEAD;

#define BAUDRATE 9600
 
void setup() {
  // Start Serial Monitor for feedback
  Serial.begin(BAUDRATE);

  // HM-10 default speed in AT command mode
  BTSerial.begin(BAUDRATE);

  pkt_tx.data.signature = 0xDEAD;
}
 
void loop() {  
  // Keep reading from HM-10 and send to Arduino Serial Monitor
  bluetooth_transmit(); 
  delay(25);
  bluetooth_receive();
  delay(25);
}

void bluetooth_transmit() {
  // Set some hardcoded values to write in the packet
  pkt_tx.data.a = 1;
  pkt_tx.data.b = 2;
  pkt_tx.data.c = 3;

  BTSerial.write((byte *) & pkt_tx,sizeof(Packet));

  // Print the same string to the Serial Monitor for feedback
  Serial.print("TX: (a,b,c)=(");
  Serial.print(pkt_tx.data.a); Serial.print(",");
  Serial.print(pkt_tx.data.b); Serial.print(",");
  Serial.print(pkt_tx.data.c); Serial.println(")");  
}

void bluetooth_receive() {
  if(BTSerial.available() > 0) {
    for (int i = 0; i < sizeof(Packet); i++) {
      pkt_rx.pkt_size[i] = BTSerial.read();
    }    
  }

  if(pkt_rx.data.signature == signature) {
    Serial.print("RX: (a,b,c)=(");
    Serial.print(pkt_rx.data.a); Serial.print(",");
    Serial.print(pkt_rx.data.b); Serial.print(",");
    Serial.print(pkt_rx.data.c); Serial.println(")");
  } else {
    Serial.println("ERROR");
    BTSerial.flush();
  }
}
