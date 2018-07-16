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
struct Data {
  int a;
  int b;
  int c;
  
  // Checksum to minimize errors
  byte checksum;
} data; // Instantiate a Data struct

// Union to allow porting between different computer architectures
union Packet {
  Data data;
  byte pkt_size[sizeof(Data)];
} pkt; // Instantiate a Packet union

byte checksum = 0xDEAD;
 
void setup() {
  // Start Serial Monitor for feedback
  Serial.begin(BAUDRATE);

  // HM-10 virtual UART
  BTSerial.begin(BAUDRATE);
}
 
void loop() {
  // Receive data from the bluetooth
  bluetooth_receive();  

  // Necessary forced delay, if we transmit too fast
  //  the error rate will increase sharply
  delay(20);
}

// Function responsible for receiving data over bluetooth
void bluetooth_receive() {
   // (software serial buffer)
  // Keep reading from HM-10 and send to Arduino Serial Monitor  
  // Check the software serial buffer for data to read
  if(BTSerial.available() > 0) {
    // Read in the appropriate number of bytes to fit out Packet
    for (int i = 0; i < sizeof(Packet); i++) {
      pkt.pkt_size[i] = BTSerial.read();
    }
  }

  // Error checking
  //  If: checksum matches, print packet
  //  Else: checksum does not match, printe error & flush buffer
  if(pkt.data.checksum == checksum) {
    // Print packet (debug)
    print_packet();
  } else {
    Serial.println("ERROR");

    // Flush the software serial buffer (refresh for new data)
    BTSerial.flush();
  }  
}

// Function to print packet data (debug)
void print_packet() {
  Serial.print("(a,b,c)=(");
  Serial.print(pkt.data.a); Serial.print(",");
  Serial.print(pkt.data.b); Serial.print(",");
  Serial.print(pkt.data.c); 
  Serial.println(")");
}
