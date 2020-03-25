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
    pthread_t RedButtonThread;
    pthread_create(&GreenThread, NULL, Controls::ReadCard, myControls); 
    pthread_create(&RedButtonThread, NULL, Controls::CheckRedButton, myControls); 
    pthread_join(GreenThread,NULL);
    pthread_join(RedButtonThread,NULL);

    myControls->DeInit();
    delete myControls;
    return 0;
};
