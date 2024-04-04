#include "SDCARD.h"
#define SD_CS 5

SDCARD SD_CARD;
String Datalogger;

void writeFile(fs::FS &fs, const char * path, const char * message){
  Serial.printf("Writing file: %s\n", path);

  File file = fs.open(path, FILE_WRITE);
  if(!file){
      Serial.println("Failed to open file for writing");
      return;
  }
  if(file.print(message)){
      Serial.println("File written");
  } else {
      Serial.println("Write failed");
  }
  file.close();
}
void appendFile(fs::FS &fs, const char * path, const char * message) {
  Serial.printf("Appending to file: %s\n", path);

  File file = fs.open(path, FILE_APPEND);
  if(!file) {
    Serial.println("Failed to open file for appending");
    return;
  }
  if(file.print(message)) {
    Serial.println("Message appended");
  } else {
    Serial.println("Append failed");
  }
  file.close();
}

void deleteFile(fs::FS &fs, const char * path){
  Serial.printf("Deleting file: %s\n", path);
  if(fs.remove(path)){
      Serial.println("File deleted");
  } else {
      Serial.println("Delete failed");
  }
}

void readFile(fs::FS &fs, const char * path){
    Serial.printf("Reading file: %s\n", path);

    File file = fs.open(path);
    if(!file){
        Serial.println("Failed to open file for reading");
        return;
    }

    Serial.print("Read from file: ");
    while(file.available()){
        Serial.println(file.readString());
    }
    file.close();
}

void SDCARD::SetupSD()
{
    RTC_TIME.DATA_RTC();
    SD.begin(SD_CS);
    if (!SD.begin(SD_CS)) {
        Serial.println("Gagal Memuat Kartu SD");
        return;
    }
    uint8_t cardType = SD.cardType();
    if (cardType == CARD_NONE) {
        Serial.println("Tidak Ada Kartu SD");
        return;
    }
    Serial.println("Menginisialisasi kartu SD...");
    File file = SD.open(name.c_str());
    if(!file) {
        Serial.println("File doens't exist");
        Serial.println("Creating file...");
        writeFile(SD, name.c_str(),"Time,V1,V2,V3,A1,A2,A3,LUX\r\n");
    }
    else {
        Serial.println("File already exists");
        appendFile(SD, name.c_str(),"DEVICE HAS BEEN RESET PREVIOUSLY\r\n");  
    }
    file.close();
}

void SDCARD::Get_data(SensorsHandler_Value& value)
{
    RTC_TIME.DATA_RTC();
    Datalogger = waktu+","+(value.VOLT1)+","+String(value.VOLT2)+","+String(value.VOLT3)+","+String(value.AMP1)+","+String(value.AMP2)+","+String(value.AMP3)+","+String(value.LIGHT)+"\r\n";
}

void SDCARD::Append_data()
{
    RTC_TIME.DATA_RTC();
    String Data = Datalogger;
    Serial.println(Data);
    appendFile(SD, name.c_str(), Data.c_str());
}

void SDCARD::Read_data()
{
    RTC_TIME.DATA_RTC();
    readFile(SD, name.c_str());
}

void SDCARD::Reset_data()
{
    RTC_TIME.DATA_RTC();
    deleteFile(SD, name.c_str());
    writeFile(SD, name.c_str(),"LOGGER HAS BEEN RESET PREVIOUSLY\r\n");
    appendFile(SD, name.c_str(),"Time,V1,V2,V3,A1,A2,A3,LUX\r\n");
}


