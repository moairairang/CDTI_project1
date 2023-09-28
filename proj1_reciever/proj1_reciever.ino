#include <WiFi.h>
const char* ssid = "ESP32_Server";
const char* password = "12345678";

#define IN1 14
#define IN2 27
#define IN3 26
#define IN4 25

WiFiServer server(80);

void setup() {
  Serial.begin(115200);
  

  // Motor Setup
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  // Set up Wi-Fi as an access point
  WiFi.softAP(ssid, password);
  server.begin();
  Serial.println("Server started");

  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  delay(10);
}

void loop() {
  WiFiClient client = server.available();
  if (client) {
    Serial.println("Client connected");
    String receivedData = "";

    while (client.connected()) {
      while (client.available()) {
        char c = client.read();
        Serial.write(c);

        if (c == '\n') {  // End of line, let's process
          if (receivedData == "1") {
            analogWrite(IN1, 100);
            analogWrite(IN2, 0);
            analogWrite(IN3, 0);
            analogWrite(IN4, 100);
          } else if (receivedData == "2") {
            analogWrite(IN1, 0);
            analogWrite(IN2, 100);
            analogWrite(IN3, 100);
            analogWrite(IN4, 0);
          } else if (receivedData == "0") {
            digitalWrite(IN1, 0);
            digitalWrite(IN2, 0);
            digitalWrite(IN3, 0);
            digitalWrite(IN4, 0);
          } else if (receivedData == "3") {  //right
            analogWrite(IN1, 0);
            analogWrite(IN2, 100);
            analogWrite(IN3, 0);
            analogWrite(IN4, 100);
          } else if (receivedData == "4") {  //left
            analogWrite(IN1, 100);
            analogWrite(IN2, 0);
            analogWrite(IN3, 100);
            analogWrite(IN4, 0);
          }
          receivedData = "";  // clear the string after processing
        } else {
          receivedData += c;  // accumulate incoming data into a string
        }
      }

      delay(10);  // Give a small delay to allow data to be read properly
    }
    client.stop();
    Serial.println("Client disconnected");
  }
}
