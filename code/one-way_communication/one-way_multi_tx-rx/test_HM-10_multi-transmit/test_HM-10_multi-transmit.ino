/*
 * MICROCONTROLLER: ATTiny85
 * BLUETOOTH: HM-10
 * 
 * 
 */

#include <SoftwareSerial.h>

// TX and RX pins
#define TX 11
#define RX 10

// Initialize our Bluetooth Serial
SoftwareSerial BTSerial(RX,TX);

//#define Serial BTSerial // Good if prototyping on Arduino


byte your_var1;
byte your_var2;


/*****     Setup     *****/
void setup() {

  // Initialize our TX and RX pins (might not be necessary. TODO)
//  pinMode(RX,INPUT);
//  pinMode(TX,OUTPUT);

  // Open/start our Bluetooth virtual/software serial communication link
  BTSerial.begin(9600);
}



/*****     Main Loop.  Continually transmits! (No receive)     *****/
/*****          NOTE: 50ms delay is necessary!     *****/
void loop() {
  BT_TX();  // Just keep transmitting!
  delay(50);
}



/*****     Performs Bluetooth data (TX) transmission     *****/
/*****          Sends Turn data to Servo OTA (over the air)     *****/
/*****          Sends Throttle data to Motor OTA (over the air)     *****/
void BT_TX() {
  print_start_deliminator();  // Start of every transmission (message)

  send_var_1(); // Transmits turn data (to servo)

  print_data_deliminator(); // Separates our data

  send_var_2(); // Transmits throttle data (to motor)

  print_end_deliminator();  // End of every transmission (message)

  BTSerial.flush(); // Flushes our buffer for new data (if for some reason it started to pile up) TODO: Check if this is necessary...
}


/*****     Transmits throttle data (to motor) from Throttle gimbal (thumbstick)     *****/
void send_var_1() {  
  your_var1 = 10;
  BTSerial.print(your_var1);
}

void send_var_2() {  
  your_var1 = 20;
  BTSerial.print(your_var2);
}



/*****     Zero pads (adds 0's to FRONT) integer and returns as a 3 character long String     *****/
/*****          Ex] (int) 3 => (String) "003"     *****/
String zero_pad(int mapped) {
  String str = "";
  str += mapped;

  if (mapped < 99)  // If integer is < 3 digits, append a 0 (to front)
    str = "0" + str;
  if (mapped < 10)  // If integer is < 2 digits, append a/another 0 (to front)
    str = "0" + str;

  return str;
}



/*****     Prints Start Deliminator for BT transmission     *****/
void print_start_deliminator() {
  BTSerial.print("<");
}



/*****     Prints Data separation deliminator for BT transmission     *****/
void print_data_deliminator() {
  BTSerial.print(";");
}



/*****     Prints End Deliminator for BT transmission     *****/
void print_end_deliminator() {
  BTSerial.println(">");
}
