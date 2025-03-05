#include <SPI.h>
#include <Wire.h>
#include <Adafruit_SHT31.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <SdFat.h>

#define TCAADDR 0x70

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

Adafruit_SHT31 sht31 = Adafruit_SHT31();

#define SD_CS_PIN 23

#define FILE_BASE_NAME "Data"

SdFat SD;
SdFile file;
const uint8_t BASE_NAME_SIZE = sizeof(FILE_BASE_NAME) - 1;
char fileName[13] = FILE_BASE_NAME "00.csv";

SdSpiConfig config(SD_CS_PIN, DEDICATED_SPI, SD_SCK_MHZ(16), &SPI1);

//            Probe : |  0  |  1  |  2  |  3  |  4  |  5  |  6  |  7  |
bool probeSelect[8] = { true, true,false,false, true, true, true,false};
float probeHumidity[8];
float probeTemp[8];

unsigned long logtime;
unsigned long dispstart;
unsigned long dispnow;
const unsigned long disptime = 5000;
unsigned long writestart;
unsigned long writenow;
const unsigned long writetime = 60*15*1000;

void tcaselect(uint8_t i) {
  if (i > 7) return;
 
  Wire.beginTransmission(TCAADDR);
  Wire.write(1 << i);
  Wire.endTransmission();  
}

void setup(void) 
{

  //Serial.begin(9600);

  display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS);
  display.setRotation(2);
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);

  /* Initialise the 1st sensor */
  tcaselect(0);
  sht31.begin(0x44);
  
  /* Initialise the 2nd sensor */
  tcaselect(1);
  sht31.begin(0x44);

  tcaselect(4);
  sht31.begin(0x44);

  tcaselect(5);
  sht31.begin(0x44);

  tcaselect(6);
  sht31.begin(0x44);

  SD.begin(config);
  while (SD.exists(fileName)) {
    if (fileName[BASE_NAME_SIZE + 1] != '9') {
      fileName[BASE_NAME_SIZE + 1]++;
    } else if (fileName[BASE_NAME_SIZE] != '9') {
      fileName[BASE_NAME_SIZE + 1] = '0';
      fileName[BASE_NAME_SIZE]++;
    }
  }
  file.open(fileName, O_WRONLY | O_CREAT | O_EXCL);
  file.print("Time (s)");
  for (int i = 0; i < 7; i++){
    if (probeSelect[i]){
      file.print(",H");
      file.print(i,DEC);
      file.print("(%)");
      file.print(",T");
      file.print(i,DEC);
      file.print("(deg C)");
    }
  }
  file.println();
  file.close();
  dispstart = millis();
  writestart = millis();
}

void loop(void) 
{
  //DISPLAY CODE HERE
  dispnow = millis();
  if (dispnow - dispstart >= disptime){
    display.clearDisplay();
    display.setTextSize(1);

    if(probeSelect[0]){
      tcaselect(0);
      float h0 = sht31.readHumidity();
      float t0 = sht31.readTemperature();
      probeHumidity[0] = h0;
      probeTemp[0] = t0;
      //Serial.print("Sensor 0: ");
      //Serial.println(h0);
      display.setCursor(4, 5);
      display.print("P0: "); display.print(h0);
    }
    else{
      display.setCursor(4, 5);
      display.print("P0: "); display.print("--");
    }

    if(probeSelect[1]){
      tcaselect(1);
      float h1 = sht31.readHumidity();
      float t1 = sht31.readTemperature();
      probeHumidity[1] = h1;
      probeTemp[1] = t1;
      //Serial.print("Sensor 1: ");
      //Serial.println(h1);
      display.setCursor(SCREEN_WIDTH/2+4, 4);
      display.print("P1: "); display.print(h1);
    }
    else{
      display.setCursor(SCREEN_WIDTH/2+4, 4);
      display.print("P1: "); display.print("--");
    }

    if(probeSelect[2]){
      tcaselect(2);
      float h2 = sht31.readHumidity();
      float t2 = sht31.readTemperature();
      probeHumidity[2] = h2;
      probeTemp[2] = t2;
      //Serial.print("Sensor 2: ");
      //Serial.println(h2);
      display.setCursor(4, 20);
      display.print("P2: "); display.print(h2);
    }
    else{
      display.setCursor(4, 20);
      display.print("P2: "); display.print("--");
    }

    if(probeSelect[3]){
      tcaselect(3);
      float h3 = sht31.readHumidity();
      float t3 = sht31.readTemperature();
      probeHumidity[3] = h3;
      probeTemp[3] = t3;
      //Serial.print("Sensor 3: ");
      //Serial.println(h3);
      display.setCursor(SCREEN_WIDTH/2+4, 20);
      display.print("P3: "); display.print(h3);
    }
    else{
      display.setCursor(SCREEN_WIDTH/2+4, 20);
      display.print("P3: "); display.print("--");
    }

  if(probeSelect[4]){
      tcaselect(4);
      float h4 = sht31.readHumidity();
      float t4 = sht31.readTemperature();
      probeHumidity[4] = h4;
      probeTemp[4] = t4;
      //Serial.print("Sensor 4: ");
      //Serial.println(h4);
      display.setCursor(4, 36);
      display.print("P4: "); display.print(h4);
    }
    else{
      display.setCursor(4, 36);
      display.print("P4: "); display.print("--");
    }

    if(probeSelect[5]){
      tcaselect(5);
      float h5 = sht31.readHumidity();
      float t5 = sht31.readTemperature();
      probeHumidity[5] = h5;
      probeTemp[5] = t5;
      //Serial.print("Sensor 5: ");
      //Serial.println(h5);
      display.setCursor(SCREEN_WIDTH/2+4, 36);
      display.print("P5: "); display.print(h5);
    }
    else{
      display.setCursor(SCREEN_WIDTH/2+4, 36);
      display.print("P5: "); display.print("--");
    }

    if(probeSelect[6]){
      tcaselect(6);
      float h6 = sht31.readHumidity();
      float t6 = sht31.readTemperature();
      probeHumidity[6] = h6;
      probeTemp[6] = t6;
      //Serial.print("Sensor 6: ");
      //Serial.println(h6);
      display.setCursor(4, 52);
      display.print("P6: "); display.print(h6);
    }
    else{
      display.setCursor(4, 52);
      display.print("P6: "); display.print("--");
    }

    if(probeSelect[7]){
      tcaselect(7);
      float h7 = sht31.readHumidity();
      float t7 = sht31.readTemperature();
      probeHumidity[7] = h7;
      probeTemp[7] = t7;
      //Serial.print("Sensor 7: ");
      //Serial.println(h7);
      display.setCursor(SCREEN_WIDTH/2+4, 52);
      display.print("P7: "); display.print(h7);
    }
    else{
      display.setCursor(SCREEN_WIDTH/2+4, 52);
      display.print("P7: "); display.print("--");
    }
    
    display.drawRect(0,0,SCREEN_WIDTH,SCREEN_HEIGHT,SSD1306_WHITE);
    display.drawLine(0,15,SCREEN_WIDTH,15,SSD1306_WHITE);
    display.drawLine(0,30,SCREEN_WIDTH,30,SSD1306_WHITE);
    display.drawLine(0,45,SCREEN_WIDTH,45,SSD1306_WHITE);
    display.drawLine(SCREEN_WIDTH/2,0,SCREEN_WIDTH/2,SCREEN_HEIGHT,SSD1306_WHITE);
    display.display();
    dispstart = millis();
  }

  //SD CODE HERE
  writenow = millis();
  if (writenow-writestart >= writetime){
    display.clearDisplay();
    display.setTextSize(2);
    display.drawRect(0,0,SCREEN_WIDTH,SCREEN_HEIGHT,SSD1306_WHITE);
    for(int j=0; j<12; j++){
      for(int i=0; i<9; i++){
        display.drawLine(2-SCREEN_HEIGHT+i+j*20, 0, 2+i+j*20,SCREEN_HEIGHT,SSD1306_WHITE);
      }
    }
    display.fillRect(SCREEN_WIDTH/2-45, SCREEN_HEIGHT/2-12,SCREEN_WIDTH/2+24,SCREEN_HEIGHT/2-10,SSD1306_BLACK);
    display.drawRect(SCREEN_WIDTH/2-46, SCREEN_HEIGHT/2-13,SCREEN_WIDTH/2+26,SCREEN_HEIGHT/2-9,SSD1306_WHITE);
    display.setTextColor(SSD1306_WHITE);
    display.setTextSize(2);
    display.setCursor(SCREEN_WIDTH/2-42, SCREEN_HEIGHT/2-9);
    display.print("LOGGING");
    display.display();

    file.open(fileName, O_APPEND | O_WRITE);
    logtime = millis();
    float logsecs = logtime/1000;
    int lt = (int)logsecs;
    file.print(lt,DEC);
    for (int i = 0; i < 7; i++){
      if (probeSelect[i]){
        file.print(",");
        file.print(probeHumidity[i],DEC);
        file.print(",");
        file.print(probeTemp[i],DEC);
      }
    }
    file.println();
    file.close();
    writestart = millis();
  }
}