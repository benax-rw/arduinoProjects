#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

HTTPClient http; 
WiFiClientSecure client;

void setup(){ 
  Serial.begin(115200);
  delay(150);  
  connectToWiFi("benax-iot", "ben@ks10+");
}

void loop(){
    client.setInsecure(); //When security is not a concern.
    String payload = "This is to test!";
    http.begin(client, "https://projects.benax.rw/f/o/r/e/a/c/h/p/r/o/j/e/c/t/s/4e8d42b606f70fa9d39741a93ed0356c/insecure-testing/getData.php?dummy="+urlencode(payload));  
    parseResponse();
    delay(5000); //Repeat after n milliseconds
}

/*
 * CONNECT WIFI
*/
void connectToWiFi(const char* ssid, const char* passwd){
  WiFi.mode(WIFI_OFF); //This prevents reconnection issue
  delay(10);
  WiFi.mode(WIFI_STA); //This hides the viewing of ESP as wifi hotspot
  WiFi.begin(ssid, passwd); //Connect to your WiFi router
  while(WiFi.status()!= WL_CONNECTED){
    delay(1000);
    Serial.print(".");
  }
  Serial.println();  
}

/*
 * PARSE THE RESPONSE
*/
void parseResponse(){
    if(http.GET() == 200){
        Serial.println("Data delivered!");
   }
   else{
    Serial.println("Data delivery failed!");
   }
}

String urlencode(String str){
    String encodedString="";
    char c;
    char code0;
    char code1;
    char code2;
    for (int i =0; i < str.length(); i++){
      c=str.charAt(i);
      if (c == ' '){
        encodedString+= '+';
      } else if (isalnum(c)){
        encodedString+=c;
      } else{
        code1=(c & 0xf)+'0';
        if ((c & 0xf) >9){
            code1=(c & 0xf) - 10 + 'A';
        }
        c=(c>>4)&0xf;
        code0=c+'0';
        if (c > 9){
            code0=c - 10 + 'A';
        }
        code2='\0';
        encodedString+='%';
        encodedString+=code0;
        encodedString+=code1;
        //encodedString+=code2;
      }
      yield();
    }
    return encodedString;   
}
