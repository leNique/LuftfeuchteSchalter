void DisplayTemp(byte Auswahl)
{
 float Temperatur;

 switch (Auswahl)
 {
  case 1:
  Temperatur=sensorInnen.t;
  break;
  case 2:
  Temperatur=sensorAussen.t;
  break;
 }
if (Blink==0)
 {
  display.setSegments(celsiusInnen);
 }
else
 {
  Blink=0;
  showNumberDecEx(Temperatur,0,false,4, uint8_t pos = 3);
 }

}


void DisplayHumidityR(byte)
{

}


void DisplayHumidityA(byte)
{

}
