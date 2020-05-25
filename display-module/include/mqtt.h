#include <Arduino.h>
#include <MicroSD.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include <stdlib.h>
#include <pinout.h>
//#include <Json.h>

//Json Read_Inf = Json();
WiFiClient espClient;
PubSubClient client(espClient);
//MicroSD Memory = MicroSD();

void callback(char* topic, byte* message, unsigned int length){
    StaticJsonBuffer<500> JSONBuffer;                     
    JsonObject& parsed = JSONBuffer.parseObject(message); 
    //return parsed;
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
    //value = Read_Inf.writeJson(product,ref,price,expiration,quantity,discount,description);
    //Memory.writeFile(SD, "data", value);
}

class mqtt {
    public:
        mqtt();
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

void mqtt::begin(const char* name_Component, const char* name_subscribe){
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
    }
    client.setServer(mqttServer, mqttPort);
    client.setCallback(callback);
    while (!client.connected()){
        client.connect(name_Component, mqtt_User, mqtt_Password);
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