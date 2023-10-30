#include <Arduino.h>
#include <avr/wdt.h>
#include <avr/sleep.h>

#define DISABLE_SLEEP 0
#define LED_R A3
#define LED_G A2
#define LED_B A1
#define LIGHT_PIN (8)
#define LIGHTON_THRESHOLD (1)

int counter = 0;

void watchdogSetup(void)
{
  cli();
  wdt_reset();
  WDTCSR |= (1 << WDCE) | (1 << WDE);
  WDTCSR = (1 << WDIE) | (0 << WDE) | (1 << WDP3) | (1 << WDP0); // 8s / interrupt, no system reset
  // WDTCSR = (1 << WDIE) | (0 << WDE) | (1 << WDP2) | (1 << WDP1) | (1 << WDP0); // 2s / interrupt, no system reset
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

  pinMode(LIGHT_PIN, INPUT);
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
  flash(LED_R, 2000, 10);
  flash(LED_G, 2000, 10);
  flash(LED_B, 2000, 10);
  flash(LED_R, 2000, 10);
  flash(LED_G, 2000, 10);
  flash(LED_B, 2000, 10);
}

void sleepNow()
{
  if (DISABLE_SLEEP == 1)
  {
    return;
  }
  flash(LED_R, 50, 10);
  watchdogSetup();
  Serial.println("sleep");
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
  sleep_mode();
  sleep_disable();
}

int readLight()
{
  int light = analogRead(LIGHT_PIN);
  Serial.println(light);
  return light;
}

void loop(void)
{
  int c = readLight();
  if (c < LIGHTON_THRESHOLD)
  {
    lightUp();
  }
  sleepNow();
}

ISR(WDT_vect)
{
  Serial.println("interrupt");
}