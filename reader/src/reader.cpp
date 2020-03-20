#include "Controls.h"
#include "Definitions.h"

int main()
{
    std::string readString;
    Controls *myControls = new Controls();
    if ( false == myControls->Init() )
    {
        delete myControls;
        return 1;
    }

    pthread_t GreenThread;
    pthread_create(&GreenThread, NULL, Controls::ReadEntry, myControls); 
    pthread_join(GreenThread,NULL);

    myControls->DeInit();
    delete myControls;
    return 0;
};
