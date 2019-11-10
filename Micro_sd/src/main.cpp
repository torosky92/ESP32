#include <Arduino.h>
#include <Json.h>
#include <MicroSD.h>

MicroSD Memory = MicroSD();
String imagen;
Json Read_Inf = Json();

void setup() {
  Serial.begin(9600);
  Memory.setupSD(5);
  String value = Read_Inf.writeJson("Leche",24565,2000,"11/11/19",10,0,"Cerveza");
  Memory.writeFile(SD, "data", value);
  delay(500);
  
}

void loop() {
  String data = Memory.readFile(SD, "data");
  String inf = Read_Inf.readJson(data,2);
  Serial.println(inf);
  delay(5000);
}