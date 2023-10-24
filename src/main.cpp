#include <Arduino.h>
#include <avr/wdt.h>
#include <avr/sleep.h>

#define LED_R A3
#define LED_G A2
#define LED_B A1

void watchdogSetup(void)
{
  cli();
  wdt_reset();
  WDTCSR |= (1 << WDCE) | (1 << WDE);
  WDTCSR = (1 << WDIE) | (0 << WDE) | (1 << WDP3) | (1 << WDP0); // 8s / interrupt, no system reset
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
}

void flash(uint8_t pin, int start, int stop)
{
  digitalWrite(pin, HIGH);
  delay(start);
  digitalWrite(pin, LOW);
  delay(stop);
}

void lightUp(void)
{
  Serial.println("light");
  flash(LED_R, 1000, 10);
  flash(LED_G, 1000, 10);
  flash(LED_B, 1000, 10);
  flash(LED_R, 1000, 10);
  flash(LED_G, 1000, 10);
  flash(LED_B, 1000, 10);
}

void sleepNow()
{
  watchdogSetup();
  Serial.println("sleep");
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
  sleep_mode();
  sleep_disable();
}

void loop(void)
{
  lightUp();
  sleepNow();
}

ISR(WDT_vect)
{
  Serial.println("interrupt");
}