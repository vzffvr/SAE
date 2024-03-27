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
void Init();
//
void Traitement_Oled();