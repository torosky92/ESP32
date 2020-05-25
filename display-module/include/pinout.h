#include <Arduino.h>

//PIN OLED
#define OLED_RESET 4

//PIN SENSOR
#define SENSOR 14

//PIN Indicador
#define LED 13

const char* ssid = "Redmi"; //Nombre de red
const char* password =  "6b32ad6dac12"; // Contraseña de red
const char* mqttServer = "tailor.cloudmqtt.com"; // Direccion donde se ubica el mqtt del broker
const int mqttPort = 18091; // Puerto del Mqtt del broker
const char* mqtt_User = "zbtbveka"; //Nombre del Usuario del broker
const char* mqtt_Password = "3QAhOmlBfa90"; //Clave del usuario del broker

const char * product;           
int ref; 
float price;
const char * expiration;
int quantity;
float discount;
const char * description;

const char * memory_Pro;
unsigned long tini=0;
unsigned long tini2=0;
unsigned long tact=0;
unsigned long trel=0;
unsigned long trel2=0;

String inf;
String inf2;
String inf3;
String inf4;
String inf5;
String inf6;
String inf7;

String value;

String data;

void setIO(){
    pinMode(LED, OUTPUT);
    pinMode(SENSOR, INPUT);
}