#include <Arduino.h>
#include <driver/ledc.h>
#include <esp_adc_cal.h>
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

float temperatura = 0.0;


uint32_t readADC_Cal(int ADC_RAW){
  esp_adc_cal_characteristics_t adc_chars;
  esp_adc_cal_characterize(ADC_UNIT_1, ADC_ATTEN_DB_11, ADC_WIDTH_BIT_12, 1100, &adc_chars);
  return (esp_adc_cal_raw_to_voltage(ADC_RAW, &adc_chars));
}

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
        float voltaje = readADC_Cal(ADCraw);
        temperatura = ((voltaje/4095)*3.3)/0.01;
      }
    }
  }
}
