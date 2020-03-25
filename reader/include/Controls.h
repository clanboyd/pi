#ifndef CONTROLS_H
#define CONTROLS_H

#include "Definitions.h"
#include "Lcd.h"

class Controls
{
    public:

    // Constructor
    Controls();
    // Destructor
    ~Controls(){};
   
    bool Init(); 
    void DeInit(); 
    static void* ReadCard(void* obj);
    void ReadCard(); 
    static void* CheckRedButton(void* obj);
    void CheckRedButton(); 
    static void* GreenLedBlink(void* obj);
    void GreenLedBlink(); 
    void ShowId(); 

protected:

private:
    MySerial *mSerPointer;
    Lcd *mLcd;
    std::string mId;
};

#endif // CONTROLS_H

