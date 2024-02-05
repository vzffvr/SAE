#include <Arduino.h>
#include <Ticker.h>
#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#include <image.h>

#define OLED_width 128
#define OLED_height 64 
#define OLED_adrs 0x3C


Adafruit_SSD1306 OLED(OLED_width,OLED_height);  


void action()
{
  OLED.clearDisplay();
  /* OLED.drawLine(0,0,127,63,1);   //ligne
  OLED.drawRect(10,10, 100, 35, 1); //Rectangle
  OLED.drawCircle(64,32,30,1);    // cercle
  OLED.fillCircle( 0,0,30,1);     //cercle rempli
  OLED.fillCircle( 128,0,30,1);
  OLED.fillTriangle(0, 64 ,64, 64 , 0,32,1 );  // triangle */
  
  //OLED.drawBitmap(0,0,bitmap_thermometre, 24,24,1);

  OLED.setTextSize(4);
  OLED.setTextColor(1);
  OLED.setCursor(10,10);
  OLED.println("Tourad");
  OLED.display();
}

Ticker ticker(action, 2000, 0, MILLIS);

void setup()
{
  Serial.begin(115200);
  Wire.begin();

  OLED.begin(SSD1306_SWITCHCAPVCC, OLED_adrs);
  OLED.clearDisplay();

  ticker.start();
}

void loop()
{
  ticker.update();
}
