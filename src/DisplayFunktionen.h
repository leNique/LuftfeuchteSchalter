#ifndef DISPLAYFUNKTIONEN_H
	#define DISPLAYFUNKTIONEN_H
 
	void DisplayTemp(byte);
        void DisplayHumidityR(byte);
        void DisplayHumidityA(byte);
        void DisplayBetrieb(void);
 



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
const uint8_t Betrieb[] = {
  SEG_C | SEG_D | SEG_E | SEG_F | SEG_G,         // b
  SEG_A | SEG_D | SEG_E | SEG_F | SEG_G,         // E
  SEG_D | SEG_E | SEG_F | SEG_G,                 // t
  SEG_E | SEG_G                                  // r
};



#endif
