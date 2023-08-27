#include <Arduino.h>
#include "display7.h"
#include <driver/ledc.h>
#include <esp_adc_cal.h>
#define rojo 23
#define amarillo 21
#define verde 22
#define botemp 19
#define sensortemp 35
//Pines para los displays
#define A 27
#define B 14
#define C 15
#define D 25
#define E 26
#define F 12
#define G 13
#define dP 2
#define display1 4
#define display2 5
#define display3 18

const int debounceDelay = 50;
unsigned long lastDebounceTime1 = 0;
bool lastButtonState1 = HIGH;
bool buttonState1 = HIGH;
int ADCraw = 0;

float temperatura = 0.0;
int temp = 0;


uint32_t readADC_Cal(int ADC_RAW){
  esp_adc_cal_characteristics_t adc_chars;
  esp_adc_cal_characterize(ADC_UNIT_1, ADC_ATTEN_DB_11, ADC_WIDTH_BIT_12, 1100, &adc_chars);
  return (esp_adc_cal_raw_to_voltage(ADC_RAW, &adc_chars));
}

void setup() {
  configurar(A, B, C, D, E, F, G, dP);
  pinMode(display1, OUTPUT);
  pinMode(display2, OUTPUT);
  pinMode(display3, OUTPUT);
  digitalWrite(display1, LOW);
  digitalWrite(display2, LOW);
  digitalWrite(display3, LOW);
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
        float voltaje = readADC_Cal(ADCraw);
        temperatura = ((voltaje/4095)*3.3)/0.01;
        temp = temperatura*10;
        int decenas = temp/100;
        temp = temp-(decenas*10);
        int unidades = temp/10;
        int decimal = temp-(unidades*10);
        digitalWrite(display1, HIGH);
        digitalWrite(display2, LOW);
        digitalWrite(display3, LOW);
        desplegarValor(decenas);
        desplegarPunto(0);
        delay(5);
        digitalWrite(display1, LOW);
        digitalWrite(display2, LOW);
        digitalWrite(display3, HIGH);
        desplegarValor(unidades);
        desplegarPunto(1);
        delay(5);
        digitalWrite(display1, LOW);
        digitalWrite(display2, LOW);
        digitalWrite(display3, HIGH);
        desplegarValor(decimal);
        desplegarPunto(0);
        delay(5);
      }
    }
  }
  if (temperatura < 37.0){
    digitalWrite(rojo, LOW);
    digitalWrite(amarillo, LOW);
    digitalWrite(verde, HIGH);
  } else if(temperatura >= 37.0 && temperatura <=37.5){
    digitalWrite(rojo, LOW);
    digitalWrite(amarillo, HIGH);
    digitalWrite(verde, LOW);
  } else{
    digitalWrite(rojo, HIGH);
    digitalWrite(amarillo, LOW);
    digitalWrite(verde, LOW);
  }
}
