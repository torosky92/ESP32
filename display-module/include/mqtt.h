#include <Arduino.h>

#include <WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include <stdlib.h>
#include <pinout.h>

WiFiClient espClient;
PubSubClient client(espClient);

class mqtt {
    public:
        mqtt();
        void callback(char* topic, byte* message, unsigned int length);
        void begin(const char* name_Component, const char* name_subscribe);
        void sending(const char* direction_mqtt, const char* product, int quantity);
    private:
        const char* _product; 
        const char* _expiration; 
        const char* _description;
        float _price; 
        float _discount;
        int _ref; 
        int _quantity;
};

mqtt::mqtt(){}

void mqtt::callback(char* topic, byte* message, unsigned int length){
    StaticJsonBuffer<500> JSONBuffer;                     
    JsonObject& parsed = JSONBuffer.parseObject(message); 

    _product = parsed["name"];           
    _ref = parsed["product_id"]; 
    _price = parsed["price"];
    _expiration = parsed["expiration"];
    _quantity = parsed["quantity"];
    _discount = parsed["discount"];
    _description = parsed["description"];
}

void mqtt::begin(const char* name_Component, const char* name_subscribe){
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
    }
    client.setServer(mqttServer, mqttPort);
    client.setCallback(callback);
    while (!client.connected()){
        client.connect(name_Component, mqtt_User, mqttPassword);
    }
    client.subscribe(name_subscribe);
}

void mqtt::sending(const char* direction_mqtt, const char* product, int quantity){
    StaticJsonBuffer<300> JSONbuffer;
    JsonObject& JSONencoder = JSONbuffer.createObject();
    JSONencoder["name"] = product;
    JSONencoder["quantity"] = quantity;
    char JSONmessageBuffer[100];
    JSONencoder.printTo(JSONmessageBuffer, sizeof(JSONmessageBuffer));
    if (client.publish(direction_mqtt,JSONmessageBuffer) == true) {
      Serial.println("Success sending message");
    } else {
      Serial.println("Error sending message");
    }
    client.loop();
    Serial.println("-------------");
    delay(1000);
}