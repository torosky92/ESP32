#include <Arduino.h>

//PIN OLED
#define OLED_RESET 4

//PIN SENSOR
#define SENSOR 14

//PIN Indicador
#define LED 13

const char* ssid = "MEDINA"; //Nombre de red
const char* password =  "430610860"; // Contraseña de red
const char* mqttServer = "tailor.cloudmqtt.com"; // Direccion donde se ubica el mqtt
const int mqttPort = 18091; // Puerto del Mqtt
const char* mqtt_User = "zbtbveka"; //torosky92 Nombre del Usuario
const char* mqtt_Password = "3QAhOmlBfa90"; //123456 Clave del usuario

const char * product;           
int ref; 
float price;
const char * expiration;
int quantity;
float discount;
const char * description;

void setIO(){
    pinMode(LED, OUTPUT);
    pinMode(SENSOR, INPUT);
}