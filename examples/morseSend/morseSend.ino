/*
 Example use of the cww_MorseTx library. The program loops waiting for a button on I/O pin 4  
 to be brought LOW. When that happens, the string "CQ DE W1AW" will be sent in Morse Code. The
 LED pin will be pulsed and a 1000 Hz audio tone will be present on I/O pin 3.

 If a character or string is received from the Serial input port, that too will be sent in 
 Morse Code.
*/

// The next three lines are optional and are used to change the tone channel from the default of channel 0.
//#ifdef ESP32
//#define TONE_CHANNEL 15
//#endif

#include <cww_MorseTx.h>

#define CW_SPEED 15

#ifdef ESP32
#define PIN_LED 2
#define PIN_SND 16
#define PIN_BTN 4
#else
#define PIN_LED 2
#define PIN_SND 3
#define PIN_BTN 4
#endif

#define TONE_FREQ 1000

cww_MorseTx morse(PIN_LED, CW_SPEED, PIN_SND, TONE_FREQ);

void setup() {
  Serial.begin(9600);
  pinMode(PIN_BTN, INPUT_PULLUP);
}

void loop() {
  // Wait for switch closure and debounce
  if (digitalRead(PIN_BTN) == LOW) {
    delay(50);
    if (digitalRead(PIN_BTN) == LOW) {
      morse.send("CQ DE W1AW");
    }
  }

  // If a character was received on the serial port, send it
  if (Serial.available() > 0) {
    morse.send(Serial.read());
  }
}
