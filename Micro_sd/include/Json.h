#include <Arduino.h>
#include <ArduinoJson.h>

class Json {
    public:
        Json();
        String readJson(String message, int which);
        String writeJson(const char * product, int ref, float price, const char * expiration, int quantity, float discount, const char * description);
    private:
};

Json::Json(){
}

String Json::readJson(String message, int which){
    StaticJsonBuffer<500> JSONBuffer;                     //Memory pool
    JsonObject& parsed = JSONBuffer.parseObject(message); //Parse message
    
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