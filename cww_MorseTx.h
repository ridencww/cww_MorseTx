#ifndef cww_MorseTx_h
#define cww_MorseTx_h

class cww_MorseTx {
  public:
    cww_MorseTx(byte keypin, byte speed, bool invert = false);
    cww_MorseTx(byte keypin, byte speed, byte sndpin, int freq = 1000, bool invert = false);
    void send(char c);
    void send(char* str);
  private:
    void dot();
    void dash();
};

#endif
