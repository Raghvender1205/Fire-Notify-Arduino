#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <dht.h>

dht DHT;
#define DHT11_PIN 2
int BUZZER(int);
int LED = 9;
int Buzzer =  12;
int Smoke_Detector = A0;
int a=0;
const char* ssid = "RC";
const char* password = "123454321";

ESP8266WebServer server(80);

String page = "";

void setup()
{
  pinMode(Buzzer,OUTPUT);
  pinMode(Smoke_Detector,INPUT);
  Serial.begin(9600);
  WiFi.begin(ssid,password);
  Serial.println("");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
   
  server.on("/", [](){
    server.send(200, "text/plain", "All good");
  });
  
  server.on("/data", [](){
  int chk = DHT.read11(DHT11_PIN);
    server.send(200, "text/plain", String(DHT.temperature)+"#"+String(DHT.humidity);
    if(BUZZER()==0)
    {
      server.send(200,"text/plain");
    }
    else if(BUZZER()==1)
    {
      server.send(200,"No Smoke Detected");
    }
    else
    {
      server.send(200,"ERROR");
    }
    delay(1000); 
  });
  
  server.begin();
  Serial.println("Web server started!");

  
}
void loop()
{
  server.handleClient();
}

int BUZZER()
{
  int threshold = 700;
  int Smoke_level = analogRead(Smoke_Detector);
  if(Smoke_level >= threshold)
  {
    tone(Buzzer,1000,200);
    return 1;
  }
  else
  {
    noTone(Buzzer);
    return 0;
  }
  delay(500);
}
