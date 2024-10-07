#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <UrlEncode.h>



const int incomingPin = D5; 
unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50;

int lastSignalState = LOW;
int signalState = LOW;

void setup() {
  Serial.begin(115200);
  pinMode(incomingPin, INPUT);

  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
  sendMessage("Hello from ESP32!");
}

void loop() {
  // int reading = digitalRead(incomingPin);

  // if (reading != lastSignalState) {
  //   lastDebounceTime = millis();  // Reset the debounce timer
  // }

  // if ((millis() - lastDebounceTime) > debounceDelay) {
  //   if (reading != signalState) {
  //     signalState = reading;

  //     if (signalState == HIGH) {
  //       Serial.println("Received HIGH signal from Arduino!");
  //     } else {
  //       Serial.println("Received LOW signal from Arduino.");
  //     }
  //   }
  // }

  // lastSignalState = reading;
}



void sendMessage(String message){

  // Data to send with HTTP POST
  String url = "http://api.callmebot.com/whatsapp.php?phone=" + phoneNumber + "&apikey=" + apiKey + "&text=" + urlEncode(message);
  WiFiClient client;    
  HTTPClient http;
  http.begin(client, url);

  // Specify content-type header
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");
  
  // Send HTTP POST request
  int httpResponseCode = http.POST(url);
  if (httpResponseCode == 200){
    Serial.print("Message sent successfully");
  }
  else{
    Serial.println("Error sending the message");
    Serial.print("HTTP response code: ");
    Serial.println(httpResponseCode);
  }

  // Free resources
  http.end();
}