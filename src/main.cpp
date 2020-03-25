#include <Arduino.h>
#include <TM1637Display.h>

#include <SoftwareWire.h>
#include <AM2320.h>

//Temp_LuftfSenor - AM2320
AM2320 sensorInnen(5,6); // AM2320 sensor attached SDA to digital PIN 5 and SCL to digital PIN 6
AM2320 sensorAussen(9,10); // AM2320 sensor attached SDA to digital PIN 9 and SCL to digital PIN 10


#define CLK 11
#define DIO 12
#define PinSchalter 5

TM1637Display display = TM1637Display(CLK, DIO);


unsigned long TimerSensor=0;


byte DisplayStatus=0;
bool TasterMerker=0;


// Create array that turns all segments on:
const uint8_t data[] = {0xff, 0xff, 0xff, 0xff};
// Create array that turns all segments off:
const uint8_t blank[] = {0x00, 0x00, 0x00, 0x00};
// You can set the individual segments per digit to spell words or create other symbols:
const uint8_t done[] = {
  SEG_B | SEG_C | SEG_D | SEG_E | SEG_G,           // d
  SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F,   // O
  SEG_C | SEG_E | SEG_G,                           // n
  SEG_A | SEG_D | SEG_E | SEG_F | SEG_G            // E
};
// Create degree Celsius symbol:
const uint8_t celsius[] = {
  SEG_A | SEG_B | SEG_F | SEG_G,  // Circle
  SEG_A | SEG_D | SEG_E | SEG_F   // C
};




void setup() {
pinMode(PinSchalter, INPUT);
  
  // Clear the display:
 display.clear();
 delay(500);
 display.setBrightness(7);
 display.setSegments(data);
 delay(1000);
  
}

void loop() {

  //Timer nach Überlauf setzen
if (millis()<TimerSensor)
 {TimerSensor=millis();}
  
  
  // 1. Mal pro Minute ausführen
  if (TimerSensor+60000<millis())
  {
   //SensorenLesen 
   sensorInnen.Read();
   sensorAussen.Read();
   TimerSensor=millis();
  }  
  
// Taster lesen und DisplayStatus anpassen  
if (digitalRead(5) && TasterMerker==0)
   { 
    DisplayStatus++;
    if (DisplayStatus>6)
     {DisplayStatus=0;}
    TasterMerker=1;
   }
else
    {
     TasterMerker=0;
    }


  
 // ----- Display ------ 
  
  switch (var) {
      case 0:
             display.clear();
      break;
      case 1:
      DisplayTemp(1);
      break;
      case 2:
      DisplayHumidityR(1);
      break;
      case 3:
      DisplayHumidityA(1);
      break;
      case 4:
      DisplayTemp(2);
      break;
      case 5:
      DisplayHumidityR(2);
      break;
      case 6:
      DisplayHumidityR(2);
      break;
  }
  
  

}
