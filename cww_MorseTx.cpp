#include "Arduino.h"

#include "cww_MorseTx.h"

/*
version 1.2.1: Ignore all non-Morse characters, support ESP32 v2.x+ that has tone/noTone 
version 1.2.0: Change speed to float type to support speeds less than 1 word per minute
version 1.1.1: Isolate variables to support multiple instances. Fix divide by zero error when speed = 0
version 1.1.0: ESP32 support. Fixed compiler warning about a constant to char* conversion.
version 1.0.0: Initial release
*/

const byte _morsetable[] = { 
  B01110101, // !
  B01010010, // "
  B00000001, // # (no Morse character)
  B11001000, // $
  B00000001, // % (no Morse character)
  B00100010, // &
  B01011110, // '
  B00101101, // (
  B01101101, // )
  B00000001, // * (no Morse character)
  B00101010, // +
  B01110011, // ,
  B01100001, // -
  B01101010, // .
  B00101001, // /
  B00111111, // 0
  B00111110, // 1
  B00111100, // 2
  B00111000, // 3
  B00110000, // 4
  B00100000, // 5
  B00100001, // 6
  B00100011, // 7
  B00100111, // 8
  B00101111, // 9
  B01000111, // :
  B01010101, // ;
  B00000001, // < (no Morse character)
  B00110001, // =
  B00000001, // > (no Morse character)
  B01001100, // ?
  B01010110, // @
  B00000110, // A
  B00010001, // B
  B00010101, // C
  B00001001, // D
  B00000010, // E
  B00010100, // F
  B00001011, // G
  B00010000, // H
  B00000100, // I
  B00011110, // J
  B00001101, // K
  B00010010, // L
  B00000111, // M
  B00000101, // N
  B00001111, // O
  B00010110, // P
  B00011011, // Q
  B00001010, // R
  B00001000, // S
  B00000011, // T
  B00001100, // U
  B00011000, // V
  B00001110, // W
  B00011001, // X
  B00011101, // Y
  B00010011, // Z
  B00000001, // [ (no Morse character)
  B01000000, // backslash
  B00000001, // ](no Morse character)
  B00000001, // ^ (no Morse character)
  B01101100, // _
  B01011110, // `
};

cww_MorseTx::cww_MorseTx(byte keypin, float speed, bool invert) {
  pinMode(keypin, OUTPUT);
  digitalWrite(keypin, invert ? HIGH : LOW);

  // Avoid divide by zero error
  if (speed == 0.0) {
      speed = 1;
  }

  _dotlen = 1200.0 / speed;
  _dashlen =  3 * _dotlen;
  _keypin = keypin;
  _invert = invert;
  _sndpin = 0;
}

cww_MorseTx::cww_MorseTx(byte keypin, float speed, byte sndpin, int freq, bool invert) : cww_MorseTx(keypin, speed, invert) {
  _sndpin = sndpin;
  _freq = freq;
}

void cww_MorseTx::dot() {
  if (_sndpin !=  0) {
    tone(_sndpin, _freq);	  
  }
  
  digitalWrite(_keypin, _invert ? LOW : HIGH);
  delay(_dotlen);
  digitalWrite(_keypin, _invert ? HIGH : LOW);

  if (_sndpin != 0) {
    noTone(_sndpin);
  }
  
  delay(_dotlen);
}

void cww_MorseTx::dash() {
  if (_sndpin !=  0) {
    tone(_sndpin, _freq);	  
  }
  
  digitalWrite(_keypin, _invert ? LOW : HIGH);
  delay(_dashlen);
  digitalWrite(_keypin, _invert ? HIGH : LOW);

  if (_sndpin != 0) {
    noTone(_sndpin);
  }
  
  delay(_dotlen);
}

void cww_MorseTx::send(char c) {
  byte o;
  byte morseByte;
  byte offset = (byte)c < 97 ? 0 : 32;

  // Send space
  if (c == ' ') {
    delay(7 * _dotlen);
    return;
  }

  // Ignore offsets (non-Morse) characters
  o = ((byte) c) - 33 - offset;
  if (o > 63) {
      o = 2; // a non-Morse character
  }
  
  // Take the ASCII and retrieve the equivalent Morse character
  morseByte = _morsetable[o];

  // Output the CW character by rotating through the data byte
  while (morseByte != 1) {
    if (morseByte & 1)
      dash();
    else
      dot();

    // Rotate to next bit
    morseByte = morseByte / 2;
  }
  
  // Inter-letter space
  delay(2 * _dotlen);
}

void cww_MorseTx::send(const char* str) {
  while (*str) {
    send(*str++);
  }
}

// Only define tone/noTone for ESP32 platform 1.x (ESP_ARDUINO_VERSION_MAJOR added in 2.x)
#ifdef ESP32
#ifndef ESP_ARDUINO_VERSION_MAJOR
void tone(uint8_t pin, unsigned int frequency) {
    if (ledcRead(TONE_CHANNEL)) {
    //    log_e("Tone channel %d is already in use", ledcRead(TONE_CHANNEL));
        return;
    }
    ledcAttachPin(pin, TONE_CHANNEL);
    ledcWriteTone(TONE_CHANNEL, frequency);
}

void noTone(uint8_t pin) {
    ledcDetachPin(pin);
    ledcWrite(TONE_CHANNEL, 0);
}
#endif
#endif
