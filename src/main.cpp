#include <Arduino.h>
#include <avr/wdt.h>
#include <avr/sleep.h>
#include <LowPower.h>

#define LED_R A3
#define LED_G A2
#define LED_B A1
#define LIGHT_PIN (8)
#define LIGHTON_THRESHOLD (1)
#define MAX_CYCLES (360)

int counter = MAX_CYCLES;

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

void heartBeat(uint8_t pin)
{
  flash(pin, 50, 10);
}

void sleepNow()
{
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

bool isDark()
{
  return readLight() < LIGHTON_THRESHOLD;
}

void loop(void)
{
  if (counter > 0)
  {
    if (isDark())
    {
      lightUp();
      counter--;
    }
    else
    {
      heartBeat(LED_G);
      counter = MAX_CYCLES;
    }
  }
  else
  {
    if (!isDark())
    {
      counter = MAX_CYCLES;
    }
    else
    {
      heartBeat(LED_R);
    }
  }

  // LowPower.idle(SLEEP_8S, ADC_OFF, TIMER4_OFF, TIMER3_OFF, TIMER1_OFF, TIMER0_OFF, SPI_OFF, USART1_OFF, TWI_OFF, USB_OFF);
  LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF);
}