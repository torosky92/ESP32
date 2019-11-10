#include <Arduino.h>
#include <ArduinoJson.h>
#include <SD.h>
#include <FS.h>


class MicroSD {
  public:
    MicroSD();
    void setupSD(int SD_CS);
    String readFile(fs::FS &fs, const char * path);
    bool writeFile(fs::FS &fs, const char * path, String message);
  private:
    char caracter;
    String cadena;
    
};

MicroSD::MicroSD(){
}

void MicroSD::setupSD(int SD_CS){
    if(!SD.begin(SD_CS)){ //Card Mount Failed
        return;
    }
    uint8_t cardType = SD.cardType();
    if(cardType == CARD_NONE){ // No SD card attached
        return;
    }
}

// Editar
String MicroSD::readFile(fs::FS &fs, const char * path){
  File file = fs.open(String("/") + path + String(".txt"));
  cadena="";
  while(file.available()){
    caracter = file.read();
    cadena = cadena + caracter; 
  }
 return cadena;
}

bool MicroSD::writeFile(fs::FS &fs, const char * path, String message){
  File file = fs.open(String("/") + path + String(".txt"), FILE_WRITE);
  if(file.print(message)){ //File written
    return true;
  }
  return false;
}

