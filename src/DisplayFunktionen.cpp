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
if (Blink==0)
 {
  if (Auswahl==1)
  {display.setSegments(celsiusInnen);}
  else
  {display.setSegments(celsiusAussen);} 
 }
else
 {
  Blink=0;
  showNumberDecEx(Temperatur,0,false,4, uint8_t pos = 3);
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
if (Blink==0)
 {
  if (Auswahl==1)
  {display.setSegments(HumidityRInnen);}
  else
  {display.setSegments(HumidityRAussen);} 
 }
else
 {
  Blink=0;
  showNumberDecEx(Humidity,0,false,4, uint8_t pos = 3);
 }
}


void DisplayHumidityA(byte Auswahl)
{
 int Humidity;
 float Temperatur;
 int AbsuluteFeuchte;
 
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
if (Blink==0)
 {
  if (Auswahl==1)
  {display.setSegments(HumidityRInnen);}
  else
  {display.setSegments(HumidityRAussen);} 
 }
else
 {
  Blink=0;
  AbsuluteFeuchte = (13,233*Humidity*((10^((7,5*Temperatur)/(237+Temperatur)))/(273,16+Temperatur)))*100 // die 2 letzten Stellen sind Nachkommastellen
  showNumberDecEx(AbsuluteFeuchte,0,false,4, uint8_t pos = 3);
 }
}



void DisplayBetrieb()
{
  if (Blink==0)
 {
  display.setSegments(Betrieb);
 }
else
 {
  Blink=0;
  showNumberDecEx((Betriebstunden/60/60/1000),0,false,4, uint8_t pos = 3);
 }
}
