// Custom one-way communication with Bluetooth HM-10
// Receiving data in the form of a struct from transmitter
//
// Reads from the software UART and prints the received packet


// Library to make a Software UART
#include <SoftwareSerial.h>

#define RX 3
#define TX 2

#define BAUDRATE 9600
 
SoftwareSerial BTSerial(RX, TX); // (RX, TX)

// Struct to hold the data we want to transmit
struct Packet {
  byte a;
  int b;
  float c;
  int d;
} pkt; // Instantiate a Packet struct
 
void setup() {
  // Start Serial Monitor for feedback
  Serial.begin(BAUDRATE);

  // HM-10 virtual UART
  BTSerial.begin(BAUDRATE);
}
 
void loop() {
  // Receive data from the bluetooth
  bluetooth_receive();  

  // Necessary forced delay, if we receive too fast
  //  the error rate will increase sharply
  delay(25);
}

// Function responsible for receiving data over bluetooth
void bluetooth_receive() {
  // Check the software serial buffer for data to read
  if(BTSerial.available() > 0) {
    // Read in the appropriate number of bytes to fit our Packet
    BTSerial.readBytes((byte *) & pkt,sizeof(Packet));
    
    // Print packet (debug)
    print_packet();

    // Flush the software serial buffer (refresh for new data)
    BTSerial.flush();
  }   
}

// Function to print packet data (debug)
void print_packet() {
  Serial.print("RX: (a,b,c)=(");
  Serial.print(pkt.a); Serial.print(",");
  Serial.print(pkt.b); Serial.print(",");
  Serial.print(pkt.c); Serial.print(",");
  Serial.print(pkt.d);
  Serial.println(")");
}
