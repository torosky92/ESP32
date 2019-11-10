#include <Arduino.h>

#include <pinout.h>
#include <display.h>

DisplayHandler display(OLED_RESET);


void setup() {
  Serial.begin(9600);
  setIO();
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.base();
  display.Conection(false);
  delay(5000);
  display.Conection(true);
  display.template1("Aguila",2000,"10/11/19");
  delay(500);
}

void loop() {
  if(digitalRead(SENSOR)==HIGH){
    display.template2("Aguila", 10, 3423455);
  }
  else{
    display.template1("Aguila",2000,"10/11/19");
  }
}