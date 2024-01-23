#include <DS3231.h>
#include <Ticker.h>

#define RTC_adrs 102

void action()
{
}

DS3231 RTC;

Ticker ticker(action, 2000, 0, MILLIS);

void setup()
{
  RTC.begin(RTC_adrs);
  ticker.start();
}

void loop()
{

  ticker.update();
}
