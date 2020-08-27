//21 AUGUST 2020
//WIFI SWITCH WITH NODEMCU
//BY PRADEEP RAJ (M.P.R)
//OPE SOURCE CODE FOR 'THE FAUCETER' SUBSCRIBERS



#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

IPAddress ip(192,143,4,3);
IPAddress netmask(255,255,255,0);
ESP8266WebServer server (8080);

const char* ssid = "Fauceter WiFi Controller";

int S1 = 16; //D0
int S2 = 5 ; //D1
int S3 = 4 ; //D2
int S4 = 14; //D5
int S5 = 12; //D6

void setup() {
  pinMode(S1,OUTPUT);
  pinMode(S2,OUTPUT);

  WiFi.mode(WIFI_AP);
  WiFi.softAPConfig(ip,ip,netmask);
  WiFi.softAP(ssid);

  server.on("/switch",HTTP_GET,Switch);
  server.onNotFound(NotConnected);
  Serial.begin(115200);
  server.begin();
}

void loop() {
  server.handleClient();
  Serial.println("-----------");
  Serial.println("WiFi Connected");
  Serial.println("NODE MCU Local IP Address ");
  Serial.print(WiFi.localIP());
  
}

void Switch()  {
  if (!server.hasArg("con"))  {
    server.send(404,"text / plain","ERROR !");
    return;
  }
  
  String condition = server.arg("con");

  if (condition.equals("S1ON")) {
    digitalWrite(S1 , HIGH);
    server.send(500,"text / plain","Condition : Switch1ON //D0");
  }
  else if (condition.equals("S1OFF"))  {
    digitalWrite(S1 , LOW);
    server.send(500,"text / plain","Condition : Switch1OFF //D0");
  }
  else if (condition.equals("S2ON"))  {
    digitalWrite(S2 , HIGH);
    server.send(500,"text / plain","Condition : Switch2ON //D1");
  }
  else if (condition.equals("S2OFF")) {
    digitalWrite(S2 , LOW);
    server.send(500,"text / plain","Condition : Switch2OFF //D1");
  }
  else if (condition.equals("S3ON"))  {
    digitalWrite(S3 , HIGH);
    server.send(500,"text / plain","Condition : Switch3ON //D2");
  }
  else if (condition.equals("S3OFF")) {
    digitalWrite(S3 , LOW);
    server.send(500,"text / plain","Condition : Switch3OFF //D2");
  }
  else if (condition.equals("S4ON"))  {
    digitalWrite(S4 , HIGH);
    server.send(500,"text / plain","Condition : Switch4ON //D5");
  }
  else if (condition.equals("S4OFF")) {
    digitalWrite(S4 , LOW);
    server.send(500,"text / plain","Condition : Switch4OFF //D5");
  }
  else if (condition.equals("S5ON"))  {
    digitalWrite(S5 , HIGH);
    server.send(500,"text / plain","Condition : Switch5ON //D6");
  }
  else if (condition.equals("S5OFF")) {
    digitalWrite(S5 , LOW);
    server.send(500,"text / plain","Condition : Switch5OFF //D6");
  }
}

void NotConnected() {
  server.send(404,"text / plain","Device Not Connected");
}
