#include <Arduino.h>
#include <Ticker.h>
#include <TSL2591.h>

#define adrs 0x29

float lux = 0.0;

TSL2591 TSL;

void action()
{
  // TSL.getAllDatas();
  // TSL.getFullSpectrum();
  // TSL.getInfraRedSpectrum();
  // TSL.getVisibleSpectrum();
  lux = TSL.calculateLux();
  Serial.printf("luminosité : %.0f\n\r", lux);
  TSL.getVisibleSpectrum();
}

Ticker ticker(action, 2000, 0, MILLIS);

void setup()
{
  Serial.begin(115200);
  TSL.begin(adrs);
  TSL.config(TSL.GAIN_MEDIUM, TSL.ATIME_200);
  ticker.start();
}

void loop()
{
  ticker.update();
}
