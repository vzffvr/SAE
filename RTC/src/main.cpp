#include <DS3231.h>
#include <Ticker.h>

#define RTC_adrs 0x68

DS3231 RTC;

void action()
{ String res = RTC.get_StringTime();
  Serial.print("Secondes : ");
  Serial.println(RTC.get_sec());
  /* Serial.print("minutes : ");
  Serial.println(RTC.get_min());
  Serial.print("Heure : ");
  Serial.println(RTC.get_hour()); */
  Serial.print("Temps : ");
  Serial.println(res);
  Serial.print("DATE : ");
  Serial.print(RTC.get_jour());
  Serial.print(" / ");
  Serial.print(RTC.get_nb());
  Serial.print(" / ");
  Serial.print(RTC.get_mois());
  Serial.println("");
  Serial.println("");
}

Ticker ticker(action, 2000, 0, MILLIS);

void setup()
{
  Serial.begin(115200);
  RTC.begin(RTC_adrs);
  ticker.start();
  //RTC.set_Time(15, 47, 00);
  //RTC.set_Date(2, 5 , 2); //jour nombre date
}

void loop()
{
  ticker.update();
}
