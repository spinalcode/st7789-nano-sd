
#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7789.h> // Hardware-specific library for ST7789
#include <SD.h>                // SD card & FAT filesystem library
#include <SPI.h>             // Arduino SPI library

#define TFT_CS    A3  // define chip select pin
#define TFT_DC    A1  // define data/command pin
#define TFT_RST   A2  // define reset pin, or set to -1 and connect to Arduino RESET pin
#define SD_CS   4 // SD card select pin
 
// Initialize Adafruit ST7789 TFT library
Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);

// defines variables
bool c=false;

void setup() {

  pinMode(TFT_CS,OUTPUT);
  pinMode(SD_CS,OUTPUT);
  
    Serial.begin(9600);
    while (!Serial);

    Serial.print("Initializing SD card...");
    if (!SD.begin(SD_CS)) {
        Serial.println("initialization failed!");
        while (1); // <- this is how you should block execution, not with returns
    }
    Serial.println("initialization done.");

  // if the display has CS pin try with SPI_MODE0
  tft.init(240, 240, SPI_MODE0);    // Init ST7789 display 240x240 pixel
 
  // if the screen is flipped, remove this command
  tft.setRotation(2);
 
  Serial.println(F("Initialized"));
 
  tft.fillScreen(ST77XX_GREEN);

    File bmpImage = SD.open("/1.raw", FILE_READ);
    if(bmpImage){
      Serial.println("bmp open");
      uint8_t r[240],g[240],b[240];
      for(uint8_t y=0; y<240; y++){
        Serial.print("Line:");
        Serial.println(y);
        for(uint8_t x = 0; x < 240; x++) {
          r[x] = bmpImage.read();
          g[x] = bmpImage.read();
          b[x] = bmpImage.read();
         }
        //tft.startWrite();
        //tft.setAddrWindow(0, y, 240, 240);
        for(int x = 0; x < 240; x++) {
          uint16_t col = ((r[x]>>3)<<11)|((g[x]>>2)<<5)|(b[x]>>3);
          Serial.println(col);
          tft.pushColor(col);
        }
        //tft.endWrite();
      }      
      bmpImage.close();
    }else{
      Serial.println("bmp fail");
    }
}

void loop() {

}
