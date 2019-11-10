#include <Arduino.h>

//PIN OLED
#define OLED_RESET 4

//PIN SENSOR
#define SENSOR 14

//PIN Indicador
#define LED 13

void setIO(){
    pinMode(LED, OUTPUT);
    pinMode(SENSOR, INPUT);
}