#include <WiFi.h>
const char *ssid = "ESP32_Server";
const char *password = "12345678";

const int flexPin1 = 34;
const int flexPin2 = 35;
const int flexPin3 = 32;
const int flexPin4 = 33;

float flexPrev1 = 0.0;
float flexFilt1 = 0.0;
float flexPrev2 = 0.0;
float flexFilt2 = 0.0;
float flexPrev3 = 0.0;
float flexFilt3 = 0.0;
float flexPrev4 = 0.0;
float flexFilt4 = 0.0;

int x1;
int x2;
int x3;
int x4;

int value;

WiFiServer server(80);
WiFiClient client;  // Declare a client object

void setup() {
  Serial.begin(115200);
  pinMode(flexPin1, INPUT);
  pinMode(flexPin2, INPUT);
  pinMode(flexPin3, INPUT);
  pinMode(flexPin4, INPUT);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi!");

  while (!client.connect(WiFi.gatewayIP(), 80)) {
    delay(1000);
    Serial.println("Connecting to Server...");
  }
  Serial.println("Connected to Server!");
}

void loop() {
  filt();
  convert();
  // if (x4 == 1 && x3 == 1 && x2 == 1 && x1 == 1) {
  //   value = 0;  //stop
  // } else {
  //   value = 0;  //stop
  // }
  // if (x4 == 0 && x3 == 1 && x2 == 0 && x1 == 0) {
  //   value = 1;  //forward
  // } else {
  //   value = 0;  //stop
  // }
  // if (x4 == 0 && x3 == 0 && x2 == 0 && x1 == 1) {
  //   value = 2;  //backward

  // } else {
  //   value = 0;  //stop
  // }
  // if (x4 == 1 && x3 == 1 && x2 == 0 && x1 == 1) {
  //   value = 3;  //right

  // } else {
  //   value = 0;  //stop
  // }
  // if (x4 == 0 && x3 == 1 && x2 == 1 && x1 == 1) {
  //   value = 4;  //left

  // } else {
  //   value = 0;  //stop
  // }

  if (x4 == 1 && x3 == 1 && x2 == 1 && x1 == 1) {
    value = 0;  //stop
  } else if (x4 == 1 && x3 == 0 && x2 == 0 && x1 == 0) {
    value = 1;  //forward
  } else if (x4 == 0 && x3 == 1 && x2 == 0 && x1 == 0) {
    value = 2;  //backward
  } else if (x4 == 0 && x3 == 0 && x2 == 1 && x1 == 0) {
    value = 3;  //right
  } else if (x4 == 0 && x3 == 0 && x2 == 0 && x1 == 1) {
    value = 4;  //left
  } else {
    value = 0;  //stop
  }

  // Send the value to the server ESP32 over Wi-Fi, terminated with a newline character
  client.println(String(value) + "\n");
  client.flush();

  // You might add logic to handle reconnections, etc.
  delay(10);
}
