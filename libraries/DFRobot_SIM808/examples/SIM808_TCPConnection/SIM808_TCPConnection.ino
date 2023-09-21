#include <DFRobot_sim808.h>
#include <SoftwareSerial.h>

#define PIN_TX    10
#define PIN_RX    11

SoftwareSerial mySerial(PIN_TX,PIN_RX);
DFRobot_SIM808 sim808(&mySerial);//Connect RX,TX,PWR

char host[] = "insecure.benax.rw";
char http_cmd[] = "GET /tcp-test/index.html HTTP/1.1\r\n"
                  "Host: insecure.benax.rw\r\n"
                  "\r\n";
char buffer[512];

void setup(){
  mySerial.begin(9600);
  Serial.begin(9600);
  
 /******** Initialize sim808 module *************/
  while(!sim808.checkSIMStatus()){
      delay(1000);
      Serial.print("SIM Card error\r\n");
  } 
  Serial.println("SIM Card ready."); 
  Serial.println("GSM Started.");
    
  /*********** Attempt DHCP *******************/
  while(!sim808.join(F("cmnet"))) {
      Serial.println("Sim808 join network error");
      delay(2000);
  }

  /************ Successful DHCP ****************/
  Serial.print("IP Address is ");
  Serial.println(sim808.getIPAddress());

  /*********** Establish a TCP connection ************/
  if(!sim808.connect(TCP,host, 80)) {
      Serial.println("Connect error");
  }else{
      Serial.print("Connected to ");
      Serial.println(host);
  }

  /*********** Send a GET request *****************/
  Serial.println("Waiting to fetch...");
  sim808.send(http_cmd, sizeof(http_cmd)-1);
  while(true){
      int ret = sim808.recv(buffer, sizeof(buffer)-1);
      if (ret <= 0){
          Serial.println("fetch over...");
          break; 
      }
      buffer[ret] = '\0';
      Serial.print("Received: ");
      Serial.print(ret);
      Serial.print(" bytes: ");
      Serial.println(buffer);
      break;
  }

  /************* Close TCP or UDP connections **********/
  sim808.close();

  /*** Disconnect wireless connection, Close Moving Scene *******/
  sim808.disconnect();
}

void loop(){

}