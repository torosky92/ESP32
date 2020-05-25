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
  value = Read_Inf.writeJson(product,ref,price,expiration,quantity,discount,description);
  Memory.writeFile(SD, "data", value);
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
    if (client.connect("IOT-ESP32", mqtt_User, mqtt_Password)) {
      Serial.println("conectado");
    }
  }
  client.subscribe("DISPLAY/A");
  data = Memory.readFile(SD, "data");
  StaticJsonBuffer<400> JSONBuffer2;                     //Memory pool
  JsonObject& parsed = JSONBuffer2.parseObject(data); //Parse message
  quantity = parsed["quantity"];
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

  StaticJsonBuffer<400> JSONBuffer2;                     //Memory pool
  JsonObject& parsed = JSONBuffer2.parseObject(data); //Parse message
  
  const char * memory_Pro = parsed["name"];           //Get sensor type value
  int idnew = parsed["product_id"]; //Get sensor type value
  float pricenew = parsed["price"];
  const char * expirations = parsed["expiration"];
  int quantitynew = parsed["quantity"];
  float discountsnew = parsed["discount"];
  const char * descriptions = parsed["description"];
  
  if(trel2<10000){
    display.template1(memory_Pro,pricenew,expirations);
  }
  else if(trel2<20000 && trel2>=10000){
    display.template2(memory_Pro, quantitynew, idnew);
  }
  else if(trel2<30000 && trel2>=20000){
    display.template3(memory_Pro, discountsnew, descriptions);
  }
  else{
    tini2=millis();
  }
  if(digitalRead(SENSOR)==HIGH){
    if (quantity <= quantitynew){
      if(quantitynew>0){
        quantitynew=quantitynew-1;
      }
      quantity=quantitynew;
      Serial.println(quantitynew);
    }
    else{
      if(quantity>0){
        quantity=quantity-1;
      }
    }
    delay(1000);
  }
  if(trel>=5000){
    StaticJsonBuffer<300> JSONbuffer;
    JsonObject& JSONencoder = JSONbuffer.createObject();
    char JSONmessageBuffer[100];
    JSONencoder["name"] = memory_Pro;
    JSONencoder["quantity"] = quantity;
    value = Read_Inf.writeJson(memory_Pro,idnew,pricenew,expirations,quantity,discountsnew,descriptions);
    Serial.println(value);
    Memory.writeFile(SD, "data", value);
    
    JSONencoder.printTo(JSONmessageBuffer, sizeof(JSONmessageBuffer));
    if (client.publish("esp/test", JSONmessageBuffer) == true) {
      Serial.println("Success sending message");
    } else {
      Serial.println("Error sending message");
    }
    client.loop();
    Serial.println("-------------");
    tini=millis();
  }
  
}