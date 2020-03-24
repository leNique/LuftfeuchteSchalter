#include <Arduino.h>
#include <TM1637Display.h>


#define CLK 11
#define DIO 12
#define PinSchalter 5

TM1637Display display = TM1637Display(CLK, DIO);


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
  // Clear the display:
pinMode(PinSchalter, INPUT_PULLUP);
 display.clear();
 delay(1000);
 display.setBrightness(7);
}

void loop() {

if (digitalRead(5))
   {display.setSegments(done);}
else

    {display.clear();}



}
