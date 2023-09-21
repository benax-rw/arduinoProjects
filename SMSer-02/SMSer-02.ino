#include <SoftwareSerial.h>
#define PIN_TX    4
#define PIN_RX    5

SoftwareSerial sim808(PIN_TX,PIN_RX);

String CellNumtemp;
String CellNum;
String textMessage;
String latitude;
String longitude;
String consumotemp;

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  Serial.println("Serial begin ok");

  // set the data rate for the SoftwareSerial port
  sim808.begin(9600);
  sim808.println("AT");
}

void loop(){
  ricezione();
  delay(2000);
}

// check if there are incoming SMS
void ricezione(){
  Serial.println ("controllo ricezione SMS");
  // AT command to set sim808 to SMS mode
  sim808.print("AT+CMGF=1\r");
  delay(100);
  // Read the first SMS saved in the sim
  sim808.print("AT+CMGR=1\r");
  delay(10); 
  if(sim808.available()>0){
    textMessage = sim808.readString();
    Serial.print(textMessage); 
    delay(10);
  }
  // check if the SMS is "STATO"
  if(textMessage.indexOf("STATO")>=0){   
    Serial.println("Invio info stato arnia");
    //save the phone number of the senders in a string (this works with italian region you must adapt to  yours) 
    CellNumtemp = textMessage.substring(textMessage.indexOf("+250"));
    CellNum = CellNumtemp.substring(0,13);
    smsstato();
    CellNumtemp = "";
    textMessage = ""; 
  }
  sim808.print("AT+CMGD=1\r");
  delay(100);
  sim808.print("AT+CMGD=2\r");
  delay(100); 
}

// Send sms with all the information to the number stored
void smsstato(){
  // delete the first SMS
  sim808.print("AT+CMGD=1\r");
  delay(100);
  sim808.print("AT+CMGF=1\r"); 
  delay(1000);
  sim808.print("AT+CMGS=");
  sim808.print(CellNum);
  sim808.print("\r"); 
  delay(1000);
  //The text of the message to be sent.
  sim808.print("INFO: Latitude: ");
  sim808.print(latitude);
  sim808.print(", Longitude: ");
  sim808.print(longitude);
  sim808.print(", Ampere: ");
  sim808.print(consumotemp);
  delay(1000);
  sim808.write(0x1A);
  delay(1000);
  Serial.println("sms stato");
}
