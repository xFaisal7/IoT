#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>  
#include<Servo.h>


const char *ssid = "HAWUEI-9FSRRH_HiLink";
const char *password  = "0554323096f";
const uint8_t servoPin = D4 ;
AsyncWebServer server(80);
Servo myservo ;
boolean turn = false;
boolean sp = false;
int pos=0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(57600);
  myservo.attach(servoPin);

  {
   delay(1000);
   Serial.print(".");
 }
 Serial.print(" \nConnected to the WiFi network: ");
 Serial.print(WiFi.SSID());
 Serial.print(" IP address: ");
 Serial.print(WiFi.localIP());


 server.on("/angle", HTTP_POST, [](AsyncWebServerRequest *request) {
    String angle = request->arg("angle");
    Serial.println("Current Position: " + angle + "°");
    myservo.write(angle.toInt());
    request->send(200);
  });
  
  server.on("/speed", HTTP_POST, [](AsyncWebServerRequest * request) {
   sp = !sp;
   request-> send(200);
  });

  DefaultHeaders:: Instance().addHeader("Access-Control-Allow-Origin"," * ");
  server.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  while ( turn == true )
 {
   for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(25);                       // waits 15ms for the servo to reach the position
   }
  for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(25);                       // waits 15ms for the servo to reach the position
  }}
  while (sp==true)
  {
    if(Serial.available())
  {
    Serial.write(Serial.read());
  }
  }
  

  
  
 }












