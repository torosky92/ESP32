#include <Arduino.h>

#include <WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include <stdlib.h>


const char* ssid = "MEDINA"; //Nombre de red
const char* password =  "430610860"; // Contraseña de red
const char* mqttServer = "tailor.cloudmqtt.com"; // Direccion donde se ubica el mqtt
const int mqttPort = 18091; // Puerto del Mqtt
const char* mqttUser = "zbtbveka"; //torosky92 Nombre del Usuario
const char* mqttPassword = "3QAhOmlBfa90"; //123456 Clave del usuario

WiFiClient espClient;
PubSubClient client(espClient);

void callback(char* topic, byte* message, unsigned int length) {

  StaticJsonBuffer<500> JSONBuffer;                     //Memory pool
  JsonObject& parsed = JSONBuffer.parseObject(message); //Parse message
  
  const char * product = parsed["name"];           //Get sensor type value
  int ref = parsed["product_id"]; //Get sensor type value
  float price = parsed["price"];
  const char * expiration = parsed["expiration"];
  int quantity = parsed["quantity"];
  float discount = parsed["discount"];
  const char * description = parsed["description"];
  Serial.println(product);
  Serial.println(ref);
  Serial.println(price);
  Serial.println(expiration);
  Serial.println(quantity);
  Serial.println(discount);
  Serial.println(description);
}

void setup() {
  Serial.begin(9600);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }

  client.setServer(mqttServer, mqttPort);
  client.setCallback(callback);

  while (!client.connected()) {
    Serial.println("Conectando a Broquer MQTT...");
    if (client.connect("IOT-ESP32", mqttUser, mqttPassword )) {
      Serial.println("conectado");
    }
  }
  client.subscribe("DISPLAY/A");
  delay(500);
}

void loop() {
  StaticJsonBuffer<300> JSONbuffer;
  JsonObject& JSONencoder = JSONbuffer.createObject();
  JSONencoder["name"] = "ESP32";
  JSONencoder["quantity"] = 1;
  char JSONmessageBuffer[100];
  JSONencoder.printTo(JSONmessageBuffer, sizeof(JSONmessageBuffer));
  Serial.println("Sending message to MQTT topic..");
  Serial.println(JSONmessageBuffer);

  if (client.publish("esp/test", JSONmessageBuffer) == true) {
    Serial.println("Success sending message");
  } else {
    Serial.println("Error sending message");
  }

  client.loop();
  Serial.println("-------------");
  delay(1000);
}