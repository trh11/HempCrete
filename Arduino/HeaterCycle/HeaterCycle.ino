#include <SPI.h>
#include <Wire.h>
#include <Adafruit_SHT31.h>

#define TCAADDR 0x70
bool enableHeater = true;

Adafruit_SHT31 sht31 = Adafruit_SHT31();

void tcaselect(uint8_t i) {
  if (i > 7) return;
 
  Wire.beginTransmission(TCAADDR);
  Wire.write(1 << i);
  Wire.endTransmission();  
}

void setup() {
  Serial.begin(9600);

  tcaselect(0);
  sht31.begin(0x44);
  sht31.heater(enableHeater);
  Serial.println("heat 0 on");
  delay(30000);
  sht31.heater(!enableHeater);
  Serial.println("heat 0 off");
  
  tcaselect(1);
  sht31.begin(0x44);
  sht31.heater(enableHeater);
  Serial.println("heat 1 on");
  delay(30000);
  sht31.heater(!enableHeater);
  Serial.println("heat 1 off");

  tcaselect(4);
  sht31.begin(0x44);
  sht31.heater(enableHeater);
  Serial.println("heat 4 on");
  delay(30000);
  sht31.heater(!enableHeater);
  Serial.println("heat 4 off");

  tcaselect(5);
  sht31.begin(0x44);
  sht31.heater(enableHeater);
  Serial.println("heat 5 on");
  delay(30000);
  sht31.heater(!enableHeater);
  Serial.println("heat 5 off");

  tcaselect(6);
  sht31.begin(0x44);
  sht31.heater(enableHeater);
  Serial.println("heat 6 on");
  delay(30000);
  sht31.heater(!enableHeater);
  Serial.println("heat 6 ff");

}

void loop() {
  // put your main code here, to run repeatedly:

}
