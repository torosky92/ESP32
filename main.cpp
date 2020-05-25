#include <Arduino.h>

#include <Json.h>
#include <MicroSD.h>
#include <pinout.h>
#include <display.h>


#include <WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>

DisplayHandler display(OLED_RESET);
MicroSD Memory = MicroSD();
Json Read_Inf = Json();

WiFiClient espClient;
PubSubClient client(espClient);

void callback(char* topic, byte* message, unsigned int length) {

  StaticJsonBuffer<500> JSONBuffer;                     //Memory pool
  JsonObject& parsed = JSONBuffer.parseObject(message); //Parse message
  
  product = parsed["name"];           
  ref = parsed["product_id"]; 
  price = parsed["price"];
  expiration = parsed["expiration"];
  quantity = parsed["quantity"];
  discount = parsed["discount"];
  description = parsed["description"];
}

void setup() {
  Serial.begin(9600);
  setIO();
  Memory.setupSD(5);
  Wire.begin();
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.base();
  display.Conection(false);
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
  display.Conection(true);
  delay(500);
  tini=millis();
  tini2=millis();
}

void loop() {
  tact=millis();
  trel=tact-tini;
  trel2=tact-tini2;

  data = Memory.readFile(SD, "data");
  Serial.println(data);
  /*
  inf = Read_Inf.readJson(data,0);
  
  inf2 = Read_Inf.readJson(data,1);
  inf3 = Read_Inf.readJson(data,2);
  inf4 = Read_Inf.readJson(data,3);
  inf5 = Read_Inf.readJson(data,4);
  inf6 = Read_Inf.readJson(data,5);
  inf7 = Read_Inf.readJson(data,6);

  idnew = inf2.toInt();
  pricenew = inf3.toFloat();
  quantitynew = inf5.toInt();
  discountsnew = inf6.toFloat();
  */
  if(trel2<10000){
    display.template1(inf,pricenew,inf4);
  }
  else if(trel2<20000 && trel2>=10000){
    display.template2(inf, quantitynew, idnew);
  }
  else if(trel2<30000 && trel2>=20000){
    display.template3(inf, discountsnew, inf7);
  }
  else{
    tini2=millis();
  }
  
  if(trel>=1000){
    StaticJsonBuffer<300> JSONbuffer;
    JsonObject& JSONencoder = JSONbuffer.createObject();

    if(product != memory_Pro){
      memory_Pro=product;
      JSONencoder["name"] = product;
      JSONencoder["quantity"] = quantity;
      value = Read_Inf.writeJson(product,ref,price,expiration,quantity,discount,description);
      //Memory.writeFile(SD, "data", value);
      char JSONmessageBuffer[100];
      JSONencoder.printTo(JSONmessageBuffer, sizeof(JSONmessageBuffer));
      if (client.publish("esp/test", JSONmessageBuffer) == true) {
        Serial.println("Success sending message");
      } else {
        Serial.println("Error sending message");
      }
    }
    else{
      if (quantity != quantitynew){
        value = Read_Inf.writeJson(product,ref,price,expiration,quantitynew,discount,description);
        JSONencoder["quantity"] = quantitynew;
      }
      else{
        JSONencoder["quantity"] = quantity;
        value = Read_Inf.writeJson(product,ref,price,expiration,quantity,discount,description);
      }
      //Memory.writeFile(SD, "data", value);
      
      char JSONmessageBuffer[100];
      JSONencoder.printTo(JSONmessageBuffer, sizeof(JSONmessageBuffer));
      if (client.publish("esp/test", JSONmessageBuffer) == true) {
        Serial.println("Success sending message");
      } else {
        Serial.println("Error sending message");
      }
    }
    client.loop();
    if(digitalRead(SENSOR)==HIGH){
    data = Memory.readFile(SD, "data");
    inf = Read_Inf.readJson(data,4);
    quantitynew = inf.toInt();
    if(quantitynew>0){
      quantitynew=quantitynew-1;
    }
    delay(1000);
    }
    Serial.println("-------------");
    tini=millis();
  }
  
}