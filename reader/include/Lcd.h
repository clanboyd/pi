#ifndef LCD_H
#define LCD_H

#include "Definitions.h"

class Lcd
{
    public:

    // Constructor
    Lcd(){};
    // Destructor
    ~Lcd(){};

    void Init();
    void PulseEnable();
    void Lcd_Byte(char bits);
    void SendCmd( char cmd);
    void SendData( char* s);
    short CheckBusyFlag();

protected:

private:

};

#endif // LCD_H

