#include <Arduino.h>

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

//#include <message.h>

class DisplayHandler : public Adafruit_SSD1306 {
    public:
        DisplayHandler(int rst): Adafruit_SSD1306(rst) {

        }
        void base(bool clear, int color);
        void Conection(bool IfConect);
        void template1(String Product, float Price, String expiration);
        void template2(String Product, int quantity, int ref);
        void template3(String Product, float discount, String description);
    private:
};

void DisplayHandler::base(bool clear=false, int color=WHITE){
    if(!clear){
        this->clearDisplay();
        this->setTextColor(WHITE);
        this->setCursor(0, 0);
        this->setTextSize(2); // Draw 2X-scale text
        this->print("Setting");
        this->setCursor(0, 15);
        this->setTextSize(1); // Draw 2X-scale text
        this->print("Initialize...");
        this->display();      // Show initial text
    }
}

void DisplayHandler::Conection(bool IfConect){
    this->clearDisplay();
    this->setTextColor(WHITE);
    this->setCursor(0, 0);
    this->setTextSize(2); // Draw 2X-scale text
    this->print("PROCESS:");
    this->setCursor(0, 15);
    this->setTextSize(1); // Draw 2X-scale text
    if(IfConect){
        this->print("Connected");
    }
    else{
        this->print("Connecting to WiFi..");
    }
    this->display();      // Show initial text
}

void DisplayHandler::template1(String Product, float Price, String expiration){
    this->clearDisplay();
    this->setTextColor(WHITE);
    this->setCursor(0, 0);
    this->setTextSize(2); // Draw 2X-scale text
    this->print("PROD:");
    this->setCursor(0, 15);
    this->setTextSize(1); // Draw 2X-scale text
    this->print("Price:");
    this->setCursor(0, 25);
    this->setTextSize(1); // Draw 2X-scale text
    this->print("Exp:");
    this->setCursor(60, 5);
    this->setTextSize(1); // Draw 2X-scale text
    this->print(Product);
    this->setCursor(40, 15);
    this->setTextSize(1); // Draw 2X-scale text
    this->print(String(Price));
    this->setCursor(30, 25);
    this->setTextSize(1); // Draw 2X-scale text
    this->print(expiration);
    this->display();      // Show initial text
}

void DisplayHandler::template2(String Product, int quantity, int ref){
    this->clearDisplay();
    this->setTextColor(WHITE);
    this->setCursor(0, 0);
    this->setTextSize(2); // Draw 2X-scale text
    this->print("PROD:");
    this->setCursor(0, 15);
    this->setTextSize(1); // Draw 2X-scale text
    this->print("Cant:");
    this->setCursor(0, 25);
    this->setTextSize(1); // Draw 2X-scale text
    this->print("Code:");
    this->setCursor(60, 5);
    this->setTextSize(1); // Draw 2X-scale text
    this->print(Product);
    this->setCursor(40, 15);
    this->setTextSize(1); // Draw 2X-scale text
    this->print(String(quantity));
    this->setCursor(40, 25);
    this->setTextSize(1); // Draw 2X-scale text
    this->print(String(ref));
    this->display();      // Show initial text
}

void DisplayHandler::template3(String Product, float discount, String description){
    this->clearDisplay();
    this->setTextColor(WHITE);
    this->setCursor(0, 0);
    this->setTextSize(2); // Draw 2X-scale text
    this->print("PROD:");
    this->setCursor(0, 15);
    this->setTextSize(1); // Draw 2X-scale text
    this->print("Disc:");
    this->setCursor(0, 25);
    this->setTextSize(1); // Draw 2X-scale text
    this->print("Desc:");
    this->setCursor(60, 5);
    this->setTextSize(1); // Draw 2X-scale text
    this->print(Product);
    this->setCursor(40, 15);
    this->setTextSize(1); // Draw 2X-scale text
    this->print(String(discount));
    this->setCursor(40, 25);
    this->setTextSize(1); // Draw 2X-scale text
    this->print(description);
    this->display();      // Show initial text
}