#include <Arduino.h>
#include <WiFi.h>

const char *ssid = "Linksys01370";
const char *mdp = "3fanq5w4pb";
const uint8_t LED = 13;

void function_connect(WiFiEvent_t event, WiFiEventInfo_t info);

void function_disconnect(WiFiEvent_t event, WiFiEventInfo_t info);

void function_got_ip(WiFiEvent_t event, WiFiEventInfo_t info);

void setup()
{
  Serial.begin(115200);
  pinMode(LED, OUTPUT);
  WiFi.mode(WIFI_STA);
  WiFi.onEvent(function_connect, ARDUINO_EVENT_WIFI_STA_CONNECTED);
  WiFi.onEvent(function_disconnect, ARDUINO_EVENT_WIFI_STA_DISCONNECTED);
  WiFi.onEvent(function_got_ip, ARDUINO_EVENT_WIFI_STA_GOT_IP);

  WiFi.begin(ssid, mdp);
}

void loop()
{
}

void function_connect(WiFiEvent_t event, WiFiEventInfo_t info)
{
  digitalWrite(LED, HIGH);
  Serial.println("connecté");
}
void function_disconnect(WiFiEvent_t event, WiFiEventInfo_t info)
{
  digitalWrite(LED, LOW);
  Serial.println("déconnecté");
  WiFi.begin(ssid, mdp);
}
void function_got_ip(WiFiEvent_t event, WiFiEventInfo_t info)
{
  Serial.println(WiFi.localIP());
}