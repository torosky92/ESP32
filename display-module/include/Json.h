#include <Arduino.h>
#include <ArduinoJson.h>

class Json {
    public:
        Json();
        String readJson(String message2, int which);
        String writeJson(const char * product, int ref, float price, const char * expiration, int quantity, float discount, const char * description);
        char* writeJsonMqtt(const char * product, int quantity);
    private:
};

Json::Json(){
}

String Json::readJson(String message2, int which){
    StaticJsonBuffer<400> JSONBuffer2;                     //Memory pool
    JsonObject& parsed = JSONBuffer2.parseObject(message2); //Parse message
    
    const char * name = parsed["name"];           //Get sensor type value
    int id = parsed["product_id"]; //Get sensor type value
    float prices = parsed["price"];
    const char * expirations = parsed["expiration"];
    int quantitys = parsed["quantity"];
    float discounts = parsed["discount"];
    const char * descriptions = parsed["description"];

    if(which == 0){
        return String(name);
    } else if(which == 1){
        return String(id);
    } else if(which == 2){
        return String(prices);
    } else if(which == 3){
        return String(expirations);
    } else if(which == 4){
        return String(quantitys);
    } else if(which == 5){
        return String(discounts);
    } else if(which == 6){
        return String(descriptions);
    } else{
        return "None";
    }
    
}

String Json::writeJson(const char * product, int ref, float price, const char * expiration, int quantity, float discount, const char * description){
    StaticJsonBuffer<300> JSONbuffer;
    JsonObject& JSONencoder = JSONbuffer.createObject();
    JSONencoder["name"] = product;
    JSONencoder["product_id"] = ref;
    JSONencoder["price"] = price;
    JSONencoder["expiration"] = expiration;
    JSONencoder["quantity"] = quantity;
    JSONencoder["discount"] = discount;
    JSONencoder["description"] = description;
    char JSONmessageBuffer[300];
    JSONencoder.printTo(JSONmessageBuffer, sizeof(JSONmessageBuffer));
    return JSONmessageBuffer;
}

char* Json::writeJsonMqtt(const char * product, int quantity){
    StaticJsonBuffer<300> JSONbuffer;
    JsonObject& JSONencoder = JSONbuffer.createObject();
    JSONencoder["name"] = product;
    JSONencoder["quantity"] = quantity;
    char JSONmessageBuffer[100];
    JSONencoder.printTo(JSONmessageBuffer, sizeof(JSONmessageBuffer));
    return JSONmessageBuffer;
}