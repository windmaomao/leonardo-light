#include <Arduino.h>
#include <avr/wdt.h>

#define LED_R A3
#define LED_G A2
#define LED_B A1

void watchdogSetup(void)
{
  cli();
  wdt_reset();
  WDTCSR |= (1 << WDCE) | (1 << WDE);
  WDTCSR = (1 << WDIE) | (1 << WDP3); // 4s / interrupt, no system reset
  sei();
}

void setup(void)
{
  Serial.begin(115200);
  Serial.println("*******************");
  Serial.println("Starts...");

  pinMode(LED_R, OUTPUT);
  pinMode(LED_G, OUTPUT);
  pinMode(LED_B, OUTPUT);

  watchdogSetup();
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
  Serial.println("interrupt");
}