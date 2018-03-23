#include <SoftwareSerial>;
 
SoftwareSerial BTSerial(10, 11); // TX | RX
 
void setup() {
  Serial.begin(9600);
  BTSerial.begin(9600);  // HM-10 default speed in AT command more
}
 
void loop() {
  // Keep reading from HM-10 and send to Arduino Serial Monitor
  char rc;
  while(BTSerial.available() > 0) {
  rc = BTSerial.read();
  Serial.println(rc);
  }
  delay(1000);
}
