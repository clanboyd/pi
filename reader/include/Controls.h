#ifndef CONTROLS_H
#define CONTROLS_H

#include "Definitions.h"

class Controls
{
    public:

    // Constructor
    Controls();
    // Destructor
    ~Controls(){};
   
    bool Init(); 
    void DeInit(); 
    static void* ReadEntry(void* obj);
    void Read(); 
    void ShowId(); 

protected:

private:
    MySerial *mSerPointer;
    std::string mId;
};

#endif // CONTROLS_H

