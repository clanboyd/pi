#include "Controls.h"
#include "Definitions.h"

int main()
{
	int sock = 0, valread; 
    struct sockaddr_in serv_addr; 
    char *hello = "Hello from client"; 
    char buffer[1024] = {0}; 
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
    { 
        printf("\n Socket creation error \n"); 
        return -1; 
    } 
   
    serv_addr.sin_family = AF_INET; 
    serv_addr.sin_port = htons(50001); 
       
    // Convert IPv4 and IPv6 addresses from text to binary form 
    if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0)  
    { 
        printf("\nInvalid address/ Address not supported \n"); 
        return -1; 
    } 
   
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) 
    { 
        printf("\nConnection Failed \n"); 
        return -1; 
    } 
    send(sock , hello , strlen(hello) , 0 ); 
    printf("Hello message sent\n"); 
    valread = read( sock , buffer, 1024); 
    printf("%s\n",buffer ); 



    std::string readString;
    Controls *myControls = new Controls();
    if ( false == myControls->Init() )
    {
        delete myControls;
        return 1;
    }
    pthread_t StartThread;
    pthread_t UpButtonThread;
    pthread_t DownButtonThread;
    pthread_create(&StartThread, NULL, Controls::Start, myControls); 
    pthread_create(&UpButtonThread, NULL, Controls::CheckUpButton, myControls); 
    pthread_create(&DownButtonThread, NULL, Controls::CheckDownButton, myControls); 
    pthread_join(StartThread,NULL);
    pthread_join(UpButtonThread,NULL);
    pthread_join(DownButtonThread,NULL);

    myControls->DeInit();
    delete myControls;
    return 0;
};
