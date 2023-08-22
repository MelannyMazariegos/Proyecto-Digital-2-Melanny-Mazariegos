#include <Arduino.h>
#define rojo 23
#define amarillo 21
#define verde 22
#define botemp 19
#define sensortemp 35

const int debounceDelay = 50;
unsigned long lastDebounceTime1 = 0;
bool lastButtonState1 = HIGH;
bool buttonState1 = HIGH;
int ADCraw = 0;

void setup() {
  pinMode(rojo, OUTPUT);
  pinMode(amarillo, OUTPUT);
  pinMode(verde, OUTPUT);
  pinMode(botemp, INPUT_PULLUP);
  Serial.begin(115200);
}

void loop() {
  int reading1 = digitalRead(botemp);
  if ((millis() - lastDebounceTime1) > debounceDelay) {
    if (reading1 != lastButtonState1) {
      lastDebounceTime1 = millis();
      lastButtonState1 = reading1;
      if (lastButtonState1 == LOW) {
        ADCraw = analogRead(sensortemp);
      }
    }
  }
}
