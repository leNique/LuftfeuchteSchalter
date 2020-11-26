#include <Arduino.h>
#include <TM1637Display.h>

#include <SoftwareWire.h>
#include "AM2320.h"



//Temp_LuftfSenor - AM2320
AM2320 sensorInnen(6,7); // AM2320 sensor attached SDA to digital PIN 6 and SCL to digital PIN 7
AM2320 sensorAussen(9,10); // AM2320 sensor attached SDA to digital PIN 9 and SCL to digital PIN 10


#define CLK 11
#define DIO 12
#define PinSchalter 5
#define PinRelay 3
TM1637Display display = TM1637Display(CLK, DIO);

#define EinSchaltSchwelle 70
#define AusSchaltSchwelle 30

unsigned long TimerSensor=0;
unsigned long TimerBlink=0;
unsigned long TimerDisplayReset=0;

int BetriebstundenMin=0;
int EinAusZaehler=0;

byte DisplayStatus=0;
bool TasterMerker=0;
byte Blink=0;
bool IstEin=0;


int absolutInnen=0;
int absolutAussen=0;


void DisplayTemp(byte);
void DisplayHumidityR(byte);
void DisplayHumidityA(byte);
void DisplayBetrieb(byte);




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
  SEG_A | SEG_B | SEG_F | SEG_G,                  // Circle
  SEG_A | SEG_D | SEG_E | SEG_F,                  // C
  SEG_A | SEG_B | SEG_C | SEG_E | SEG_F | SEG_G,  // A
  SEG_C | SEG_D | SEG_E                           // u
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
  SEG_E | SEG_G,                                 // r
  SEG_A | SEG_B | SEG_C | SEG_E | SEG_F | SEG_G, // A
  SEG_C | SEG_D | SEG_E                          // u
};
// Create absolute Humidity symbol:
const uint8_t HumidityAInnen[] = {
  SEG_B | SEG_C | SEG_E | SEG_F | SEG_G,         // H
  SEG_A | SEG_B | SEG_C | SEG_E | SEG_F | SEG_G, // A
  SEG_B | SEG_C,                                 // I
  SEG_C | SEG_E | SEG_G                          // n
};
const uint8_t HumidityAAussen[] = {
  SEG_B | SEG_C | SEG_E | SEG_F | SEG_G,         // H
  SEG_A | SEG_B | SEG_C | SEG_E | SEG_F | SEG_G, // A
  SEG_A | SEG_B | SEG_C | SEG_E | SEG_F | SEG_G, // A
  SEG_C | SEG_D | SEG_E                          // u
};
const uint8_t Betrieb[] = {
  SEG_C | SEG_D | SEG_E | SEG_F | SEG_G,         // b
  SEG_A | SEG_D | SEG_E | SEG_F | SEG_G,         // E
  SEG_D | SEG_E | SEG_F | SEG_G,                 // t
  SEG_E | SEG_G                                  // r
};
const uint8_t EinAus[] = {
  SEG_A | SEG_D | SEG_E | SEG_F | SEG_G,         // E
  SEG_B | SEG_C,                                 // I
  SEG_C | SEG_E | SEG_G,                         // n
  SEG_A | SEG_B | SEG_C | SEG_E | SEG_F | SEG_G  // A
};



void setup() {
  pinMode(PinSchalter, INPUT);
  pinMode(PinRelay, OUTPUT);
  digitalWrite(PinRelay, HIGH);

  // Clear the display:
  display.clear();
  delay(500);
  display.setBrightness(7);
  display.setSegments(data);
  delay(1000);

  sensorInnen.Read();
  sensorAussen.Read();
  Serial.begin(9600);
}

void loop() {

  //Timer nach Überlauf setzen
  if (millis()<TimerSensor)
  {TimerSensor=millis();}
  if (millis()<TimerBlink)
  {TimerBlink=millis();}
  if (millis()<TimerDisplayReset)
  {TimerDisplayReset=millis();}

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
    // absolute Feuchten berechnen und Relais Schalten
    // die letzten 2 Stellen sind Nachkommastellen
    absolutInnen = (13.233*sensorInnen.h*((pow(10,((7.5*sensorInnen.t)/(237+sensorInnen.t))))/(273.16+sensorAussen.t)))*100;
    absolutAussen = (13.233*sensorAussen.h*((pow(10,((7.5*sensorAussen.t)/(237+sensorAussen.t))))/(273.16+sensorInnen.t)))*100;

    if (IstEin==1)
    {BetriebstundenMin++;}
    if (BetriebstundenMin/60>=9999)
    {BetriebstundenMin=0;}
    if (EinAusZaehler>=9999)
    {EinAusZaehler=0;}

    if (absolutInnen-EinSchaltSchwelle>absolutAussen && IstEin==0 && sensorInnen.h > 35 && sensorInnen.t > 9)
    { //Einschalten
      digitalWrite(PinRelay, LOW);
      IstEin=1;
      EinAusZaehler++;
    }
    if ((absolutInnen-AusSchaltSchwelle<absolutAussen || sensorInnen.h <= 30 || sensorInnen.t <= 7) && IstEin==1)
    { //Ausschalten
      digitalWrite(PinRelay, HIGH);
      IstEin=0;
      EinAusZaehler++;
    }
    
    TimerSensor=millis();
  }


  // Taster lesen und DisplayStatus anpassen
  if (digitalRead(5) && TasterMerker==0)
  {
    DisplayStatus++;
    if (DisplayStatus>8)
    {DisplayStatus=0;}
    TasterMerker=1;
    TimerDisplayReset=millis();
  }
  if (!digitalRead(5))
  {
    TasterMerker=0;
  }


  // DisplayStatus - Reset nach 30 Sekunden inaktivität
  if (TimerDisplayReset+30000<millis())
  {
    DisplayStatus=0;
  }
  
  
  

  // ----- Display ------

  switch (DisplayStatus) {
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
    DisplayHumidityA(2);
    break;
    case 7:
    DisplayBetrieb(1);
    break;
    case 8:
    DisplayBetrieb(2);
    break;
  }



}









void DisplayTemp(byte Auswahl)
{
  int Temperatur;

  switch (Auswahl)
  {
    case 1:
    Temperatur=sensorInnen.t*10; // die letzte Stelle ist die Nachkommastelle
    break;
    case 2:
    Temperatur=sensorAussen.t*10; // die letzte Stelle ist die Nachkommastelle
    break;
  }
  if (Blink==1)
  {
    if (Auswahl==1)
    {display.setSegments(celsiusInnen);}
    else
    {display.setSegments(celsiusAussen);}
  }
  if (Blink>1)
  {
    Blink=0;
    display.showNumberDecEx(Temperatur,0,false,4,0);
  }

}


void DisplayHumidityR(byte Auswahl)
{
  int Humidity;

  switch (Auswahl)
  {
    case 1:
    Humidity=sensorInnen.h;
    break;
    case 2:
    Humidity=sensorAussen.h;
    break;
  }
  if (Blink==1)
  {
    if (Auswahl==1)
    {display.setSegments(HumidityRInnen);}
    else
    {display.setSegments(HumidityRAussen);}
  }
  if (Blink>1)
  {
    Blink=0;
    display.showNumberDecEx(Humidity,0,false,4, 0);
  }
}


void DisplayHumidityA(byte Auswahl)
{
  int Humidity;
  float Temperatur;
  int absoluteFeuchte;

  switch (Auswahl)
  {
    case 1:
    Humidity=sensorInnen.h;
    Temperatur=sensorInnen.t;
    break;
    case 2:
    Humidity=sensorAussen.h;
    Temperatur=sensorAussen.t;
    break;
  }
  if (Blink==1)
  {
    if (Auswahl==1)
    {display.setSegments(HumidityAInnen);}
    else
    {display.setSegments(HumidityAAussen);}
  }
  if (Blink>1)
  {
    Blink=0;
    absoluteFeuchte = (13.233*Humidity*((pow(10,((7.5*Temperatur)/(237+Temperatur))))/(273.16+Temperatur)))*100; // die 2 letzten Stellen sind Nachkommastellen
    display.showNumberDecEx(absoluteFeuchte,0,false,4,0);
  }
}



void DisplayBetrieb(byte Auswahl)
{
  if (Blink==1)
  {
    if (Auswahl==1)
    {display.setSegments(Betrieb);}
    if (Auswahl==2)
    {display.setSegments(EinAus);}
  }
  if (Blink>1)
  {
    Blink=0;
    if (Auswahl==1)
    {display.showNumberDecEx((BetriebstundenMin/60),0,false,4,0);}
    if (Auswahl==2)
    {display.showNumberDecEx(EinAusZaehler,0,false,4,0);}
  }
}
