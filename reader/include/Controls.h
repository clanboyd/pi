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
    static void* Start(void* obj);
    void Start(); 
    static void* CheckUpButton(void* obj);
    void CheckUpButton(); 
    static void* CheckDownButton(void* obj);
    void CheckDownButton(); 
    static void* GreenLedBlink(void* obj);
    void GreenLedBlink(); 
    void ShowId(); 
    void PerformAction(); 
    void PerformCheckOut(); 
    void PerformCheckIn(); 
    void Read(); 

protected:

private:
    MySerial *mSerPointer;
    Lcd *mLcd;
    std::string mId;
	enum Stage{ STARTUP, CHECKOUT, CHECKIN, READNAME, READMOVIE, UNKNOWN};
	std::stack<Stage> mStageStack;
};

#endif // CONTROLS_H

