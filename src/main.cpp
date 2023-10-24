#include <Arduino.h>
#include <avr/wdt.h>

#define LED_R A3
#define LED_G A2
#define LED_B A1

void watchdogSetup(void)
{
  wdt_reset();
  wdt_enable(WDTO_8S);
  WDTCSR |= (1 << WDIE);
}

void setup(void)
{
  Serial.begin(115200);
  Serial.println("*******************");
  Serial.println("Starts...");

  pinMode(LED_R, OUTPUT);
  pinMode(LED_G, OUTPUT);
  pinMode(LED_B, OUTPUT);

  //  watchdogSetup();
}

void lightup(void)
{
  digitalWrite(LED_R, HIGH);
  delay(1000);
  digitalWrite(LED_R, LOW);
  delay(10);
  digitalWrite(LED_G, HIGH);
  delay(1000);
  digitalWrite(LED_G, LOW);
  delay(10);
  digitalWrite(LED_B, HIGH);
  delay(1000);
  digitalWrite(LED_B, LOW);
  delay(10);
}

void loop(void)
{
  lightup();
  Serial.println("lightup");
}

ISR(WDT_vect)
{
  Serial.println("....but I will print this before I reset");
}