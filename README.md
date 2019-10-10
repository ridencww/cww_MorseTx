# CWW Morse Code Transmit Library 

An Arduino library for sending Morse code with an optional audio sidetone to accompany the output. 

The output pins for code and generated audio can be specified as well as the Morse Code speed in words per minute and 
whether or not the output (key down) is active high or active low.

An example of the library's usage is included. 


```c++
#include <cww_MorseTx.h>

#define CW_SPEED 15
#define PIN_LED 2
#define PIN_SND 3
#define TONE_FREQ 1000

// Construct a cww_MorseTx instance that will send Morse Code at 15 words
// per minute on I/O pin 2. Output is active HIGH.
cww_MorseTx morse(PIN_LED, CW_SPEED);

// Construct a cww_MorseTx instance that will send Morse Code at 15 words
// per minute on I/O pin 2. Output is active LOW.
cww_MorseTx morseInverted(PIN_LED, CW_SPEED, true);

// Construct a cww_MorseTx instance that will send Morse Code at 15 words
// per minute on I/O pin 2 with a 1000 Hz sidetone on I/O pin 3. Output
// is active HIGH.
cww_MorseTx morseWithTone(PIN_LED, CW_SPEED, PIN_SND, TONE_FREQ);

// Construct a cww_MorseTx instance that will send Morse Code at 15 words
// per minute on I/O pin 2 with a 1000 Hz sidetone on I/O pin 3. Output
// is active LOW.
cww_MorseTx morseWithToneInverted(PIN_LED, CW_SPEED, PIN_SND, TONE_FREQ, true);

void setup() {
}

void loop() {
  // Send a character in Morse Code
  morse.send('C');

  delay(1000);

  // Send a string in Morse Code
  morse.send("CQ DX DE W1AW");

  delay(5000);
}
```
