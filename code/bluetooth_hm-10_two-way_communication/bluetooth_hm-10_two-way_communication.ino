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

struct Packet {
  byte a;
  int b;
  float c;
  int d;
} pkt_tx, pkt_rx;

//byte count = 10;

#define BAUDRATE 9600
 
void setup() {
  // Start Serial Monitor for feedback
  Serial.begin(BAUDRATE);

  // HM-10 default speed in AT command mode
  BTSerial.begin(BAUDRATE);
}

void loop() {  
  // Receive data from the bluetooth
  bluetooth_receive();

  // Necessary forced delay, if we transmit too fast (no delay)
  //  the error rate increases
  delay(50);
}

// Function responsible for transmitting data over bluetooth
void bluetooth_transmit() {
  // Update data to be transmitted
  pkt_tx.a = 0;
  pkt_tx.b = 255;
  pkt_tx.c = 888.888;
  pkt_tx.d = -100;

  // Write packet data to the bluetooth - and transmit
  BTSerial.write((byte *) & pkt_tx,sizeof(Packet));

  // Print the Packet contents
  Serial.print("TX: (a,b,c,d)=(");
  Serial.print(pkt_tx.a); Serial.print(",");
  Serial.print(pkt_tx.b); Serial.print(",");
  Serial.print(pkt_tx.c); Serial.print(",");
  Serial.print(pkt_tx.d); 
  Serial.println(")");  
}

// Function responsible for receiving data over bluetooth
void bluetooth_receive() {
  // Counting variable to fix a lost connection
  static byte count = 10;
  
  // Check the software serial buffer for data to read
  if(BTSerial.available() >= sizeof(Packet)) {
    // Read in the appropriate number of bytes to fit our Packet
    BTSerial.readBytes((byte *) & pkt_rx,sizeof(Packet));

    // Print the Packet contents
    Serial.print("RX: (a,b,c,d)=(");
    Serial.print(pkt_rx.a); Serial.print(",");
    Serial.print(pkt_rx.b); Serial.print(",");
    Serial.print(pkt_rx.c); Serial.print(",");
    Serial.print(pkt_rx.d); 
    Serial.println(")");

    // Flush the serial buffer
    while(BTSerial.available() > 0)
      BTSerial.read();   
    
    // Transmit data via bluetooth
    bluetooth_transmit();
  } else {
    // If a disconnect happens, start transmitting
    if(count >= 10) {
      count=0;  // Reset counter
      // Transmit to revive process
      bluetooth_transmit();
    }
    count++;
  }
}
