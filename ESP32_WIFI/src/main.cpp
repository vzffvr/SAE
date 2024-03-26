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
#include <Servo.h>
#include <BOUTON.h>

// Adresse IP : 192.168.1.181

//______Define______//
#define RTC_adrs 0x68
#define adrs_TC74 72
#define adrsTSL 0x29

#define OLED_adrs 0x3C

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

#define servoPin A0

#define PIN_BTN_UP A1
#define PIN_BTN_SELECT A2
#define PIN_BTN_DOWN A3

//_____Constantes________//
const char *ssid = "Linksys01370";
const char *mdp = "3fanq5w4pb";
const uint8_t LED_W = 13;
const uint8_t LED_controle = 21;
const char *PARAM_LED = "led";
const char *PARAM_angle = "angle";

//_______variables_globales//
float temperature = 0.0;
float lux = 0.0;
float humidity = 0.0;
float pressure = 0.0;
float angle = 0.0;
uint8_t val = 1;

//_____Classes________//
AsyncWebServer server(80);
Adafruit_SSD1306 OLED(SCREEN_WIDTH, SCREEN_HEIGHT);
GFXcanvas1 canvas(SCREEN_WIDTH, SCREEN_HEIGHT);
tc74 TC74;
DS3231 RTC;
TSL2591 TSL;
Adafruit_BME680 bme;
Servo servo;

BOUTON BOUTON_UP;
BOUTON BOUTON_DOWN;
BOUTON BOUTON_SELECT;

//_____Prototypes______//

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
//
void draw_temp();
//
void draw_date();
//
void draw_clock();
//
void draw_press();
//
void draw_lum();
//
void draw_hum();
//
void draw_menu();
//
void Traitement_bouton();
//
void Maj_date(String jour, String mois);
//
void Maj_RTC(String theHourValue, String theDateValue, String theDayValue);

//__Ticker__//
Ticker ticker(action, 1000, 0, MILLIS);

void setup()
{ // Monitor
  Serial.begin(115200);
  // pin
  pinMode(LED_W, OUTPUT);
  pinMode(LED_controle, OUTPUT);
  pinMode(servoPin, OUTPUT);

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
  // bme680
  bme.begin();
  bme.setHumidityOversampling(BME680_OS_2X);
  bme.setPressureOversampling(BME680_OS_4X);
  // serveur
  initSPIFFS();
  setRoutes();
  // Écran
  OLED.begin(SSD1306_SWITCHCAPVCC, OLED_adrs);
  OLED.clearDisplay();
  // servo
  servo.attach(servoPin, Servo::CHANNEL_NOT_ATTACHED, 0, 180);
  servo.write(0);
  delay(300);
  // Bouton
  BOUTON_UP.begin(PIN_BTN_UP);
  BOUTON_SELECT.begin(PIN_BTN_SELECT);
  BOUTON_DOWN.begin(PIN_BTN_DOWN);
  // ticker
  ticker.start();
}

void loop()
{
  ticker.update();
}

//_____Fonctions______//
void action()
{
  Traitement_bouton();
  OLED.clearDisplay();

  lux = TSL.calculateLux();
  temperature = TC74.read();

  bme.beginReading();

  if (!bme.endReading())
  {
    Serial.println(F("Failed to complete reading :("));
    return;
  }

  humidity = bme.humidity;
  pressure = bme.pressure / 100;

  // Serial.printf("Lux : %.0f\n\r", lux);
  // Serial.printf("température : %.0f\n\r", temperature);
  // Serial.printf("pression : %.0f\n\r", pressure);
  // Serial.printf("hum : %.0f\n\r", humidity);
  Serial.println();

  draw_menu();
  canvas.setTextSize(1);
  canvas.setTextColor(1);
  if (val < 1)
    val = 6;
  if (val > 6)
    val = 1;
  switch (val)
  {
  case 1:
    canvas.setCursor(20, 3);
    canvas.println("->");
    if (BOUTON_SELECT.pressed())
    {
      OLED.clearDisplay();
      draw_hum();
    }
    break;
  case 2:
    canvas.setCursor(20, 13);
    canvas.println("->");
    if (BOUTON_SELECT.pressed())
    {
      OLED.clearDisplay();
      draw_temp();
    }
    break;
  case 3:
    canvas.setCursor(20, 25);
    canvas.println("->");
    if (BOUTON_SELECT.pressed())
    {
      OLED.clearDisplay();
      draw_press();
    }
    break;
  case 4:
    canvas.setCursor(20, 35);
    canvas.println("->");
    if (BOUTON_SELECT.pressed())
    {
      OLED.clearDisplay();
      draw_lum();
    }
    break;
  case 5:
    canvas.setCursor(20, 45);
    canvas.println("->");
    if (BOUTON_SELECT.pressed())
    {
      OLED.clearDisplay();
      draw_date();
    }
    break;
  case 6:
    canvas.setCursor(20, 57);
    canvas.println("->");
    if (BOUTON_SELECT.pressed())
    {
      OLED.clearDisplay();
      draw_clock();
    }
    break;
  default:
    Serial.println("Probleme affichage");
    break;
  }
  if (BOUTON_SELECT.pressed())
  {
  }
  OLED.drawBitmap(0, 0, canvas.getBuffer(), SCREEN_WIDTH, SCREEN_HEIGHT, 1, 0);
  OLED.display();
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

  server.on("/Humvalue", HTTP_GET, [](AsyncWebServerRequest *request)
            { request->send(200, "/text/plain", String(humidity)); });

  server.on("/Presvalue", HTTP_GET, [](AsyncWebServerRequest *request)
            { request->send(200, "/text/plain", String(pressure)); });
  //
  //
  server.on("/post", HTTP_POST, [](AsyncWebServerRequest *request) // A Tester!!!!!!!!!!!!!!
            {
  String theDateValue = "";
  String theHourValue = "";
  String theDayValue = ""; 
  int params = request->params();
  //
  Serial.println(params);
  for (int i = 0; i < params; i++)                 //A Tester !!!!!!!!!!!!!!!!!!!!!
  {
    AsyncWebParameter *p = request->getParam(i);
    if (p->isPost())
    {
      if (p->name() == "theday")
      {
        theDayValue = p->value();
      }
      //
      if (p->name() == "thedate")
      {
        theDateValue = p->value();
      }
      //
      if (p->name() == "thetime")
      {
        theHourValue = p->value();
      }
    }
  }
  Serial.println(theDateValue);

  //
  //
  request->redirect("/"); 
 
  Maj_RTC(theHourValue,theDateValue,theDayValue);
 });

  // mise a jour de la date et heure
  //
  server.on("/action", HTTP_GET, [](AsyncWebServerRequest *request)
            {
    if (request->hasParam(PARAM_LED))
    {
      String res = request->getParam(PARAM_LED)->value();
      Serial.println(res);
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

  server.on("/servo", HTTP_GET, [](AsyncWebServerRequest *request)
            {
    if (request->hasParam(PARAM_angle))
    {
      String res = request->getParam(PARAM_angle)->value();
      Serial.println(res);
      angle = res.toInt();
      servo.write(angle);
    }
    request->send(200); });
}

void draw_temp()
{
  canvas.fillScreen(BLACK);
  canvas.drawBitmap(52, 8, epd_bitmap_thermometre__1_, 32, 32, 1);
  canvas.setTextSize(2);
  canvas.setTextColor(1);
  canvas.setCursor(40, 50);
  canvas.println(String(TC74.read()) + " C"); // !!!!!!!!!!!!!!! afficher le °
}

void draw_date()
{
  canvas.fillScreen(BLACK);
  canvas.drawBitmap(45, 0, epd_bitmap_calendar_days, 32, 32, 1);
  canvas.setTextSize(2);
  canvas.setTextColor(1);
  canvas.setCursor(40, 30);
  canvas.println(RTC.get_jour());
  canvas.setCursor(25, 50);
  canvas.println(RTC.get_StringDate());
}

void draw_clock()
{
  canvas.fillScreen(BLACK);
  canvas.drawBitmap(45, 0, epd_bitmap_clock, 32, 32, 1);
  // canvas.fillCircle(20, 20, 10, WHITE);
  // canvas.fillRect(100, 50, 20, 5, WHITE);
  // oled.drawBitmap(0, 0, canvas.getBuffer(), SCREEN_WIDTH, SCREEN_HEIGHT, 1, 0);
  // oled.display();
  canvas.setTextSize(2);
  canvas.setTextColor(1);
  canvas.setCursor(35, 50);
  canvas.println(RTC.get_StringTime());
}

void draw_press()
{
  canvas.fillScreen(BLACK);
  canvas.drawBitmap(45, 0, epd_bitmap_pressure_gauge, 32, 32, 1);
  canvas.setTextSize(2);
  canvas.setTextColor(1);
  canvas.setCursor(35, 50);
  canvas.println(String(pressure));
}

void draw_lum()
{
  canvas.fillScreen(BLACK);
  canvas.drawBitmap(45, 8, epd_bitmap_luminosite__1_, 32, 32, 1);
  canvas.setTextSize(2);
  canvas.setTextColor(1);
  canvas.setCursor(30, 50);
  canvas.println(String(lux));
}

void draw_hum()
{
  canvas.fillScreen(BLACK);
  canvas.drawBitmap(45, 8, epd_bitmap_humidity, 32, 32, 1);
  canvas.setTextSize(2);
  canvas.setTextColor(1);
  canvas.setCursor(35, 50);
  canvas.println(String(humidity));
}

void draw_menu()
{
  canvas.fillScreen(BLACK);
  canvas.setTextSize(1);
  canvas.setTextColor(1);
  canvas.setCursor(40, 2);
  canvas.println("Humidite");
  canvas.setCursor(40, 13);
  canvas.println("Temperature");
  canvas.setCursor(40, 24);
  canvas.println("Pression");
  canvas.setCursor(40, 35);
  canvas.println("Luminosite");
  canvas.setCursor(40, 46);
  canvas.println("Date");
  canvas.setCursor(40, 57);
  canvas.println("Heure");
}

void Traitement_bouton()
{
  if (BOUTON_UP.pressed())
  {
    val++;
    BOUTON_UP.wait_for_realesed();
  }
  if (BOUTON_DOWN.pressed())
  {
    val--;
    BOUTON_DOWN.wait_for_realesed();
  }
}

void Maj_RTC(String theHourValue, String theDateValue, String theDayValue)
{
  String hour=theHourValue.substring(0, 2);
  String minute=theHourValue.substring(3, 5);

  String jour=theDateValue.substring(5, 7);
  String mois=theDateValue.substring(8, 10);

  uint8_t _jour_ = jour.toInt();
  uint8_t _mois_ = mois.toInt();
  uint8_t _day_ = theDayValue.toInt();
  uint8_t _heure = hour.toInt();
  uint8_t _minute_ = minute.toInt();
  RTC.set_Date(_day_,_mois_,_jour_);
  RTC.set_Time(_heure, _minute_,0);
}