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
    void InitMessages();
    void PulseEnable();
    void Lcd_Byte(char bits);
    void SendCmd(char cmd);
    void SendData(char* s, char inLine);
    void SendDataNoArrow(char* s);
    void SendSpecChar(char bits);
    void ClearBits();
    void ClearDisplay();
	void InitialDisplay();
	void ArrowUp();
	void ArrowDown();
	char GetArrowLoc() { return mArrowLoc; }
	void CheckInOut(char s);

protected:

private:
	std::vector<std::string> mInitMessage;
	std::vector<std::string> mCheckOutMessage;
	char mArrowLoc;

};

#endif // LCD_H

