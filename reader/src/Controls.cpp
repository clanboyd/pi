#include "Controls.h"

Controls::Controls()
{
    // Get Serial Pointer
    mSerPointer = mSerPointer->GetMySerial();
}

bool Controls::Init()
{
    if ( !bcm2835_init() )
    {
        return false;
    }

    // Set Green LED
    bcm2835_gpio_fsel(PIN_GREEN_LIGHT, BCM2835_GPIO_FSEL_OUTP);
    // Set Green Button
    bcm2835_gpio_fsel(PIN_GREEN_BUTTON, BCM2835_GPIO_FSEL_INPT);
    //  Set Green button as pullup
    bcm2835_gpio_set_pud(PIN_GREEN_BUTTON, BCM2835_GPIO_PUD_UP);
    //  Set Green button OFF
    bcm2835_gpio_write(PIN_GREEN_LIGHT, LOW);

    // Set Red LED
    bcm2835_gpio_fsel(PIN_RED_LIGHT, BCM2835_GPIO_FSEL_OUTP);
    // Set Red Button
    bcm2835_gpio_fsel(PIN_RED_BUTTON, BCM2835_GPIO_FSEL_INPT);
    //  Set Red button as pullup
    bcm2835_gpio_set_pud(PIN_RED_BUTTON, BCM2835_GPIO_PUD_UP);
    //  Set Red button OFF
    bcm2835_gpio_write(PIN_RED_LIGHT, LOW);

    mLcd = new Lcd();
    mLcd->Init();
    mLcd->SendData((char*)"hello world!");

    return true;
}

void Controls::DeInit()
{
    bcm2835_close();
    delete mLcd;
}

void* Controls::ReadCard(void* obj)
{
    ((Controls *) obj)->ReadCard();
    return obj;
}

void Controls::ReadCard()
{
    pthread_t GreenLedBlink;
    uint8_t value = 0;
    std::string str;
    bool secondRead=true;
    while (1)
    {
        secondRead=true;
        // Read some data
        value = bcm2835_gpio_lev(PIN_GREEN_BUTTON);
        if ( 0 == value )
        {
            bcm2835_gpio_write(PIN_GREEN_LIGHT, HIGH);
       	    if ( true == mSerPointer->Read(mId) )
            {
                ShowId();
                pthread_create(&GreenLedBlink, NULL, Controls::GreenLedBlink, this);
                while (secondRead == true )
                {
       	            if ( true == mSerPointer->Read(mId) )
                    {
                        ShowId();
                        secondRead=false;
                    }
                }
                pthread_cancel(GreenLedBlink);
            }
            bcm2835_gpio_write(PIN_GREEN_LIGHT, LOW);
        }
        // wait a bit
        delay(500);
    }
};

void* Controls::CheckRedButton(void* obj)
{
    ((Controls *) obj)->CheckRedButton();
    return obj;
}

void Controls::CheckRedButton()
{
    uint8_t value = 0;
    while (1)
    {
        // Read some data
        value = bcm2835_gpio_lev(PIN_RED_BUTTON);
        if ( 0 == value )
        {
            bcm2835_gpio_write(PIN_RED_LIGHT, HIGH);
        }
        // wait a bit
        delay(500);
    }
};

void* Controls::GreenLedBlink(void* obj)
{
    ((Controls *) obj)->GreenLedBlink();
    return obj;
}

void Controls::GreenLedBlink()
{
    while (1)
    {
        delay(500);
        bcm2835_gpio_write(PIN_GREEN_LIGHT, HIGH);
        delay(500);
        bcm2835_gpio_write(PIN_GREEN_LIGHT, LOW);
    }
};
void Controls::ShowId()
{
    std::cout<<mId<<std::endl;
}

