//***************************************
//Melanny Gabriela Mazariegos Fuentes - 21055
//Proyecto Digital 2
//****************************************

//***************************************
//Librerias
//***************************************
#include <Arduino.h>
//Libreria para configurar los displays
#include "display7.h"
#include <driver/ledc.h>
#include <esp_adc_cal.h>
//************************************
//Definicion de etiquetas
//************************************
//Pines para los leds
#define rojo 23
#define amarillo 21
#define verde 22
#define botemp 19 //Pin para el boton
#define sensortemp 35  //Pin para el sensor
#define pinservo 32 //Pin para el servo
//Pines para los displays
#define A 27
#define B 14
#define C 15
#define D 25
#define E 26
#define pF 12
#define G 13
#define dP 2
#define display1 4
#define display2 5
#define display3 18
//********************************
//Variables globales
//********************************
//Constantes para el debounce
const int debounceDelay = 50;
unsigned long lastDebounceTime1 = 0;
bool lastButtonState1 = HIGH;
bool buttonState1 = HIGH;
//Constante para el ADC
int ADCraw = 0;
//Constantes para la temperatura
float temperatura = 0.0;
int decenas =0;
int unidades=0;
int decimal=0;
//Funcion para convertir el analogico a digital
uint32_t readADC_Cal(int ADC_RAW){
  esp_adc_cal_characteristics_t adc_chars;
  esp_adc_cal_characterize(ADC_UNIT_1, ADC_ATTEN_DB_11, ADC_WIDTH_BIT_12, 1100, &adc_chars);
  return (esp_adc_cal_raw_to_voltage(ADC_RAW, &adc_chars));
}
//***********************************
//Configuracion
//***********************************
void setup() {
  //Configuracion de displays
  configurar(A, B, C, D, E, pF, G, dP);
  pinMode(display1, OUTPUT);
  pinMode(display2, OUTPUT);
  pinMode(display3, OUTPUT);
  digitalWrite(display1, LOW);
  digitalWrite(display2, LOW);
  digitalWrite(display3, LOW);
  //Modo para leds
  pinMode(rojo, OUTPUT);
  pinMode(amarillo, OUTPUT);
  pinMode(verde, OUTPUT);
  //Modo para boton
  pinMode(botemp, INPUT_PULLUP);
  //Configuracion del servo
  ledcSetup(0, 50, 10);
  ledcAttachPin(pinservo, 0);
  ledcWrite(0, 0);
  Serial.begin(115200);
}
//*********************************
//Loop principal
//*********************************
void loop() {
  int reading1 = digitalRead(botemp);
  //Debounce para el boton
  if ((millis() - lastDebounceTime1) > debounceDelay) {
    if (reading1 != lastButtonState1) {
      lastDebounceTime1 = millis();
      lastButtonState1 = reading1;
      if (lastButtonState1 == LOW) {
        //Calculo de la temperatura en centigrados
        ADCraw = analogRead(sensortemp);
        float voltaje = readADC_Cal(ADCraw);
        temperatura = ((voltaje/4095)*3.3)/0.01;
        Serial.print("Temperatura: ");   
        Serial.print(temperatura);
        Serial.println(",");
        //Dividir la temperatura en decenas, unidades y decimales
        int temp = temperatura*100;
        Serial.print("Decenas: ");   
        Serial.print(decenas);
        Serial.println(",");
        Serial.print("Unidades: ");   
        Serial.print(unidades);
        Serial.println(",");
        Serial.print("Decimales: ");   
        Serial.print(decimal);
        Serial.println(",");
        decenas = (temp/1000);
        temp = temp - (decenas*1000);
        unidades = (temp/100);
        temp = temp - (unidades*100);
        decimal = (temp/10); 
        //Mostrar la temperatura en displays
        digitalWrite(display1, HIGH);
        digitalWrite(display2, LOW);
        digitalWrite(display3, LOW);
        desplegarValor(8);
        desplegarPunto(1);
        delay(5);
//        digitalWrite(display1, LOW);
  //      digitalWrite(display2, HIGH);
    //    digitalWrite(display3, LOW);
      //  desplegarValor(7);
        //desplegarPunto(0);
      //  delay(5);
//        digitalWrite(display1, LOW);
  //      digitalWrite(display2, LOW);
    //    digitalWrite(display3, HIGH);
      //  desplegarValor(3);
        //desplegarPunto(1);
        //delay(5);
      }
    }
  }
  //Encender los leds de acuerdo a la temperatura
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
  //Mover el servo dependiendo de la temperatura
  if (temperatura <23.0){
    ledcWrite(0, 0);
  } else if (23.0 <= temperatura && temperatura <23.5){
    ledcWrite(0, 10);
  } else if (23.5 <= temperatura && temperatura <24.5){
    ledcWrite(0, 20);
  } else if (24.5 <= temperatura && temperatura <25.5){
    ledcWrite(0, 30);
  } else if (25.5 <= temperatura && temperatura <26.5){
    ledcWrite(0, 40);
  } else if (26.5 <= temperatura && temperatura <29.5){
    ledcWrite(0, 50);
  } else if (29.5 <= temperatura && temperatura <32.5){
    ledcWrite(0, 60);
  } else if (32.5 <= temperatura && temperatura <35.5){
    ledcWrite(0, 70);
  } else if (35.5 <= temperatura && temperatura <36.5){
    ledcWrite(0, 80);
  } else if (37.0 <= temperatura && temperatura <37.5){
    ledcWrite(0, 90);
  } else if (37.5 <= temperatura && temperatura <39.5){
    ledcWrite(0, 100);
  } else if (39.5 <= temperatura && temperatura <40.5){
    ledcWrite(0, 120);
  } else if (40.5 <= temperatura && temperatura <41.5){
    ledcWrite(0, 150);
  } else {
    ledcWrite(0, 180);
  }
}