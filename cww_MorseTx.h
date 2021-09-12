#ifndef cww_MorseTx_h
#define cww_MorseTx_h

#ifdef ESP32

#ifndef TONE_CHANNEL
#define TONE_CHANNEL 0
#endif

void tone(uint8_t pin, unsigned int frequency);
void noTone(uint8_t pin);

#endif

class cww_MorseTx {
  private:
    unsigned long _dashlen; // Length of dash
    unsigned long _dotlen;  // Length of dot
    int _freq;              // Tone frequency
    bool _invert;           // true on=low else on=high  
    byte _keypin;           // Pin for output keying
    byte _sndpin;           // Sound pin  
  public:
    cww_MorseTx(byte keypin, float speed, bool invert = false);
    cww_MorseTx(byte keypin, float speed, byte sndpin, int freq = 1000, bool invert = false);
    void send(char c);
    void send(const char* str);
  private:
    void dot();
    void dash();
};

#endif
