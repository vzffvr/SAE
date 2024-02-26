#include <Arduino.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#include <image.h>
#include <Ticker.h>
#include <TC74.h>
#include <DS3231.h>
#include <TSL2591.h>

#define RTC_adrs 0x68
#define adrs_TC74 72
#define adrsTSL 0x29

#define OLED_width 128
#define OLED_height 64
#define OLED_adrs 0x3C

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_SSD1306 OLED(OLED_width, OLED_height);
GFXcanvas1 canvas(SCREEN_WIDTH, SCREEN_HEIGHT);
tc74 TC74;
DS3231 RTC;
TSL2591 TSL;

void draw_temp();
void draw_clock();
void draw_date();

void action()
{
  static uint8_t val = 0;
  OLED.clearDisplay();
  /* OLED.drawLine(0, 0, 127, 63, 1);   // ligne
  OLED.drawRect(10, 10, 100, 35, 1); // Rectangle
  OLED.drawCircle(64, 32, 30, 1);    // cercle
  OLED.fillCircle(0, 0, 30, 1);      // cercle rempli
  OLED.fillCircle(128, 0, 30, 1);
  OLED.fillTriangle(0, 64, 64, 64, 0, 32, 1); // triangle
  OLED.drawBitmap(0, 0, bitmap_thermometre, 24, 24, 1);
  OLED.setTextSize(4);
  OLED.setTextColor(1);
  OLED.setCursor(10, 10);
  OLED.println("Tourad");
  OLED.display(); */

  switch (val)
  {
  case 1:
    draw_temp();
    break;
  case 2:
    draw_date();
    break;
  case 3:
    draw_clock();
    break;
  case 4:
    draw_clock();
    val = 0;
    break;
  default:
    OLED.clearDisplay();
    Serial.println("Probleme affichage");
    break;
  }
  val++;
  OLED.drawBitmap(0, 0, canvas.getBuffer(), SCREEN_WIDTH, SCREEN_HEIGHT, 1, 0);
  OLED.display();
}

Ticker ticker(action, 2000, 0, MILLIS);

void setup()
{
  Serial.begin(115200);
  Wire.begin();
  TC74.begin(adrs_TC74);
  RTC.begin(RTC_adrs);
  TSL.begin(adrsTSL);

  OLED.begin(SSD1306_SWITCHCAPVCC, OLED_adrs);
  OLED.clearDisplay();

  ticker.start();
}

void loop()
{
  ticker.update();
}

void draw_temp()
{
  canvas.fillScreen(BLACK);
  canvas.drawBitmap(52, 0, bitmap_thermometre, 24, 24, 1);
  canvas.setTextSize(2);
  canvas.setTextColor(1);
  canvas.setCursor(10, 50);
  canvas.println(String(TC74.read()) + "C"); // !!!!!!!!!!!!!!! afficher le °
}

void draw_date()
{
  canvas.fillScreen(BLACK);
  canvas.drawBitmap(52, 0, epd_bitmap_calendrier__1_, 24, 24, 1);
  canvas.setTextSize(2);
  canvas.setTextColor(1);
  canvas.setCursor(40, 30);
  canvas.println(RTC.get_jour());
  canvas.setCursor(30, 50);
  canvas.println(RTC.get_StringDate());
}

void draw_clock()
{
  canvas.fillScreen(BLACK);
  canvas.fillRect(64, 4, 40, WHITE);
  canvas.fillCircle(64, 25, 40, WHITE);
  canvas.setTextSize(2);
  canvas.setTextColor(1);
  canvas.setCursor(45, 50);
  canvas.println(RTC.get_StringTime());
}

void draw_lux()
{
  canvas.fillScreen(BLACK);
  canvas.fillRect(64, 4, 40, WHITE);
  canvas.fillCircle(64, 25, 40, WHITE);
  canvas.setTextSize(2);
  canvas.setTextColor(1);
  canvas.setCursor(45, 50);
  canvas.println(TSL.getString());
}
