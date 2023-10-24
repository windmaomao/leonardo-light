#include <Arduino.h>

#define LED_R A3
#define LED_G A2
#define LED_B A1

void setup(void)
{
  Serial.begin(115200);
  pinMode(LED_R, OUTPUT);
  pinMode(LED_G, OUTPUT);
  pinMode(LED_B, OUTPUT);
}

void loop(void)
{
  digitalWrite(LED_B, HIGH);
}