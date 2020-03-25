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
unsigned long TimerBlink=0;

unsigned long Betriebstunden=0;
unsigned long BetriebstundenEinMerker=0;


byte DisplayStatus=0;
bool TasterMerker=0;
byte Blink=0;
bool IstEin=0;


int absulutInnen=0;
int absulutAussen=0;


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
const uint8_t celsiusInnen[] = {
  SEG_A | SEG_B | SEG_F | SEG_G,  // Circle
  SEG_A | SEG_D | SEG_E | SEG_F,  // C
  SEG_B | SEG_C,                  // I
  SEG_C | SEG_E | SEG_G           // n
};
const uint8_t celsiusAussen[] = {
  SEG_A | SEG_B | SEG_F | SEG_G,  // Circle
  SEG_A | SEG_D | SEG_E | SEG_F,  // C
  SEG_A | SEG_B | SEG_C | SEG_E | SEG_F | SEG_G,                  // A
  SEG_C | SEG_D | SEG_E           // u
};
// Create relativ Humidity symbol:
const uint8_t HumidityRInnen[] = {
  SEG_B | SEG_C | SEG_E | SEG_F | SEG_G,  // H
  SEG_E | SEG_G,                          // r
  SEG_B | SEG_C,                          // I
  SEG_C | SEG_E | SEG_G                   // n
};
const uint8_t HumidityRAussen[] = {
  SEG_B | SEG_C | SEG_E | SEG_F | SEG_G,         // H
  SEG_A | SEG_B | SEG_C | SEG_E | SEG_F | SEG_G, // A
  SEG_A | SEG_B | SEG_C | SEG_E | SEG_F | SEG_G, // A
  SEG_C | SEG_D | SEG_E                          // u
};
// Create absulute Humidity symbol:
const uint8_t HumidityAInnen[] = {
  SEG_B | SEG_C | SEG_E | SEG_F | SEG_G,  // H
  SEG_E | SEG_G,                          // A
  SEG_B | SEG_C,                          // I
  SEG_C | SEG_E | SEG_G                   // n
};
const uint8_t HumidityAAussen[] = {
  SEG_B | SEG_C | SEG_E | SEG_F | SEG_G,         // H
  SEG_A | SEG_B | SEG_C | SEG_E | SEG_F | SEG_G, // A
  SEG_A | SEG_B | SEG_C | SEG_E | SEG_F | SEG_G, // A
  SEG_C | SEG_D | SEG_E                          // u
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
if (millis()<TimerBlink)
 {TimerBlink=millis();}  
 
  // Blinker
    if (TimerBlink+1000<millis())
  {
   //Blinker um 1 erhöhen 
   Blink++;
   TimerBlink=millis();
  }  
  
  // 1. Mal pro Minute ausführen
  if (TimerSensor+60000<millis())
  {
   //SensorenLesen 
   sensorInnen.Read();
   sensorAussen.Read();
    
   // Absulute Feuchten berechnen und Relais Schalten
    // die letzten 2 Stellen sind Nachkommastellen
    absulutInnen = (13,233*sensorInnen.h*((10^((7,5*sensorInnen.t)/(237+sensorInnen.t)))/(273,16+sensorAussen.t)))*100;
    absulutAussen = (13,233*sensorAussen.h*((10^((7,5*sensorAussen.t)/(237+sensorAussen.t)))/(273,16+sensorInnen.t)))*100;
    
    if (absulutInnen-50>absulutAussen && IstEin==0) 
     { //Einschalten
      
      BetriebstundenEinMerker=millis();
      IstEin=1;
     } 
    if (absulutInnen-10<absulutAussen && IstEin==1)
     { //Ausschalten
      
      if (millis()>BetriebstundenEinMerker) // Wenn millis() überläuft wird diese Betriebszeit einfach ignoriert
       {Betriebstunden=Betriebstunden+(millis()-BetriebstundenEinMerker);}
      if (Betriebstunden>35996400000‬) // Wenn die Betriebsstunden 9999 Stunden überschreiten werden Sie auf 0 gesetzt
       {Betriebstunden=0;}
      IstEin=0;
     } 
      
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
