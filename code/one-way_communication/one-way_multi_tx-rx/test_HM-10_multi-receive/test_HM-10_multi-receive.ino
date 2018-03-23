/*
 * MICROCONTROLLER: ATMEGA328p
 * BLUETOOTH: HM-10
 * 
 * 
 */

 #include <SoftwareSerial.h>

byte your_var1;
byte your_var2;


// TX and RX pins
#define TX 11
#define RX 10

// Initialize our Bluetooth Serial
SoftwareSerial BTSerial(RX,TX);


#define num_chars 9  // 3 (# of digits) * 2 (num readings) + 1 (semicolons) + 1 (end marker) + 1 (start marker)
char received_chars[num_chars]; // Char array of our received data
bool new_data = false;  // 



/*****     Setup     *****/
void setup() {   

//    pinMode(RX,INPUT);
//    pinMode(TX,OUTPUT);
    // Open/start our Bluetooth serial communication link
    BTSerial.begin(9600);
    Serial.begin(9600);
}



/*****     Main Loop.  Contintually receives! (No transmit)     *****/
/*****          NOTE: 50ms delay is necessary!     *****/
void loop() {
    BT_RX();  // Just keep receiving!
    delay(50);
}



/*****     Performs Bluetooth data (RX) transmission     *****/
/*****          Receives Turn data from Servo OTA (over the air)     *****/
/*****          Receives Throttle data from Motor OTA (over the air)     *****/
void BT_RX() {
    receive_msg();  // Retrieve data over BT
    process_msg();  // Manipulate the retrieved data
    BTSerial.flush(); // Flushes our buffer for new data (if for some reason it started to pile up) TODO: Check if this is necessary...
}



/*****     Receives the message from the TX Bluetooth     *****/
void receive_msg() {
    static bool receive_in_progress=false;
    static byte idx=0;
    char start_marker='<';
    char end_marker='>';
    char rc;
 
    while (BTSerial.available() > 0 && new_data == false) {
        rc=BTSerial.read(); // Read from the BT buffer
//        BTSerial.print(rc);
        if (receive_in_progress == true) {
            if (rc != end_marker) {
                received_chars[idx] = rc;
                idx++;
                if (idx >= num_chars) {
                    idx = num_chars - 1;
                }
            } else {
                received_chars[idx] = '\0'; // terminate the string
                receive_in_progress = false;
                idx = 0;
                new_data = true;
            }
        } else if (rc == start_marker) {
            receive_in_progress = true;     
        }   
    }
}



/*****     Processes message     *****/
void process_msg() {
    if (new_data == true) {
        
        String sensor_data=received_chars;
        //Serial.println(sensor_data);
        parse_sensor_readings(sensor_data);        
        new_data=false;
    }
}



/*****     Parses received data     *****/
void parse_sensor_readings(String sensor_data) {
//    Serial.print(sensor_data);
    int s_idx=0;
    String tmp="";
    char c;
    int i=0;
  
    while(c=sensor_data[s_idx]) {
      
       if(c == ';') {
          if(i<1) {
            your_var1=tmp.toInt();
            Serial.println(your_var1);
            xxx
          }
  
          tmp="";
          i++;
       } else {
          tmp+=c;      
       }
      s_idx++;
    }   
    if(i<2) {
        your_var2=tmp.toInt();
        Serial.println(your_var2);
    }
    tmp="";  
}
