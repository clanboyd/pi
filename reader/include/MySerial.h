#ifndef MYSERIAL_H
#define MYSERIAL_H

#include "Definitions.h"

class MySerial
{
    public:

    // Constructor
    MySerial();
    // Destructor
    ~MySerial();

    static MySerial *GetMySerial();
    static void RelMySerial();
    void SetSocket(int* sock);
    int* GetSocket();
    bool Open();
    bool Close();
    bool Read( std::string &rResult );

protected:
    int *mFd;

private:
    static MySerial *mSerial;
};

#endif // MYSERIAL_H

