#include <Arduino.h>
#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <SPIFFS.h>
#include <Ticker.h>
#include <TC74.h>
#include <DS3231.h>
#include <TSL2591.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#include <image.h>
#include <Adafruit_BME680.h>

//______Define______//
#define RTC_adrs 0x68
#define adrs_TC74 72
#define adrsTSL 0x29

#define OLED_adrs 0x3C

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

//_____Constantes________//
const char *ssid = "Linksys01370";
const char *mdp = "3fanq5w4pb";
const uint8_t LED_W = 13;
const uint8_t LED_controle = 21;
const char *PARAM_LED = "led";

//_______variables_globales//
float temperature = 0.0;
float lux = 0.0;

//_____Classes________//
AsyncWebServer server(80);
Adafruit_SSD1306 OLED(SCREEN_WIDTH, SCREEN_HEIGHT);
GFXcanvas1 canvas(SCREEN_WIDTH, SCREEN_HEIGHT);
tc74 TC74;
DS3231 RTC;
TSL2591 TSL;
Adafruit_BME680 bme;

//_____Prototypes______//
//
bool initSPIFFS();
//
void setRoutes();
//
void function_connect(WiFiEvent_t event, WiFiEventInfo_t info);
//
void function_disconnect(WiFiEvent_t event, WiFiEventInfo_t info);
//
void function_got_ip(WiFiEvent_t event, WiFiEventInfo_t info);
//
void action();

//__Ticker__//
Ticker ticker(action, 1000, 0, MILLIS);

void setup()
{ // Monitor
  Serial.begin(115200);

  pinMode(LED_W, OUTPUT);
  pinMode(LED_controle, OUTPUT);
  // wifi
  WiFi.mode(WIFI_STA);
  WiFi.onEvent(function_connect, ARDUINO_EVENT_WIFI_STA_CONNECTED);
  WiFi.onEvent(function_disconnect, ARDUINO_EVENT_WIFI_STA_DISCONNECTED);
  WiFi.onEvent(function_got_ip, ARDUINO_EVENT_WIFI_STA_GOT_IP);
  WiFi.begin(ssid, mdp);
  // capteur
  Wire.begin();
  TC74.begin(adrs_TC74);
  RTC.begin(RTC_adrs);
  TSL.begin(adrsTSL);
  TSL.config(TSL.GAIN_MEDIUM, TSL.ATIME_200);
  // serveur
  initSPIFFS();
  setRoutes();
  // ticker
  ticker.start();
  //bme680
  Serial.println(F("BME680 async test"));

  if (!bme.begin()) {
    Serial.println(F("Could not find a valid BME680 sensor, check wiring!"));
    while (1);
  }

  // Set up oversampling and filter initialization
  bme.setTemperatureOversampling(BME680_OS_8X);
  bme.setHumidityOversampling(BME680_OS_2X);
  bme.setPressureOversampling(BME680_OS_4X);
  bme.setIIRFilterSize(BME680_FILTER_SIZE_3);
  bme.setGasHeater(320, 150); // 320*C for 150 ms
}

void loop()
{
  ticker.update();
}

//_____Fonctions______//
void action()
{
  lux = TSL.calculateLux();
  temperature = TC74.read();
  Serial.printf("Lux : %.0f\n\r", lux);
  Serial.printf("température : %.0f\n\r", temperature);
}
//
void function_connect(WiFiEvent_t event, WiFiEventInfo_t info)
{
  digitalWrite(LED_W, HIGH);
  Serial.println("connecté");
}
//
void function_disconnect(WiFiEvent_t event, WiFiEventInfo_t info)
{
  digitalWrite(LED_W, LOW);
  Serial.println("déconnecté");
  WiFi.begin(ssid, mdp);
}
//
void function_got_ip(WiFiEvent_t event, WiFiEventInfo_t info)
{
  Serial.println(WiFi.localIP());
  server.begin();
  Serial.println("Serveur started on port 80");
}
//
bool initSPIFFS()
{
  bool res = false;
  res = SPIFFS.begin();
  if (res == false)
  {
    Serial.println("Error Init SPIFFS");
  }
  else
  {
    Serial.println("Init SPIFFS OK");
  }
  File root = SPIFFS.open("/");
  File file = root.openNextFile();

  while (file)
  {
    Serial.print("File: ");
    Serial.println(file.name());
    //
    file.close();
    file = root.openNextFile();
  }
  return res;
}

void setRoutes()
{
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request)

            { request->send(SPIFFS, "/index.html", "text/html"); });
  //
  server.on("/w3.css", HTTP_GET, [](AsyncWebServerRequest *request)
            { request->send(SPIFFS, "/w3.css", "text/css"); });
  //
  server.on("/justgage.js", HTTP_GET, [](AsyncWebServerRequest *request)
            { request->send(SPIFFS, "/justgage.js", "text/javascript"); });
  //
  server.on("/raphael.min.js", HTTP_GET, [](AsyncWebServerRequest *request)
            { request->send(SPIFFS, "/raphael.min.js", "text/javascript"); });
  //
  server.on("/script.js", HTTP_GET, [](AsyncWebServerRequest *request)
            { request->send(SPIFFS, "/script.js", "text/javascript"); });
  //
  server.on("/temperatureValue", HTTP_GET, [](AsyncWebServerRequest *request)
            { request->send(200, "/text/plain", String(temperature)); });

  server.on("/LuxValue", HTTP_GET, [](AsyncWebServerRequest *request)
            { request->send(200, "/text/plain", String(lux)); });

  server.on("/action", HTTP_GET, [](AsyncWebServerRequest *request)
            {
    if (request->hasParam(PARAM_LED))
    {
      String res = request->getParam(PARAM_LED)->value();
      if (res == "1")
      {
        digitalWrite(LED_controle, HIGH);
      }
      else
      {
        digitalWrite(LED_controle, LOW);
      }
    }
    request->send(200); });
}
