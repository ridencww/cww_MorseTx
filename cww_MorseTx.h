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
  public:
    cww_MorseTx(byte keypin, byte speed, bool invert = false);
    cww_MorseTx(byte keypin, byte speed, byte sndpin, int freq = 1000, bool invert = false);
    void send(char c);
    void send(const char* str);
  private:
    void dot();
    void dash();
};

#endif
