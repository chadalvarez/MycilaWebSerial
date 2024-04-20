/*
  WebSerialLite Demo
  ------
  This example code works for both ESP8266 & ESP32 Microcontrollers
  WebSerial is accessible at your ESP's <IPAddress>/webserial URL.

  Author: HomeboyC
*/
#include <Arduino.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <WebSerialLite.h>
#include <WiFi.h>

AsyncWebServer server(80);

const char* ssid = "";     // Your WiFi SSID
const char* password = ""; // Your WiFi Password

/* Message callback of WebSerial */
void recvMsg(AsyncWebSocketClient* client, const String& msg) {
  WebSerial.println("Received Data...");
  WebSerial.println(msg);
}

void setup() {
  Serial.begin(9600);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  if (WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.printf("WiFi Failed!\n");
    return;
  }
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
  // WebSerial is accessible at "<IP Address>/webserial" in browser
  WebSerial.begin(&server);
  /* Attach Message Callback */
  WebSerial.onMessage(recvMsg);
  server.begin();
}

void loop() {
  delay(2000);

  // we suggest you to use `print + "\n"` instead of `println`
  // because the println will send "\n" separately, which means
  // it will cost a sending buffer just for storage "\n". (there
  // only 8 buffer space in ESPAsyncWebServer by default)
  WebSerial.print(F("IP address: "));
  // if not use toString the ip will be sent in 7 part,
  // which means it will cost 7 sending buffer.
  WebSerial.println(WiFi.localIP().toString());
  WebSerial.printf("Millis=%lu\n", millis());
  WebSerial.printf("Free heap=[%" PRIu32 "]\n", ESP.getFreeHeap());
}