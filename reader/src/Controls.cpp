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

    return true;
}

void Controls::DeInit()
{
    bcm2835_close();
}

void* Controls::ReadEntry(void* obj)
{
    ((Controls *) obj)->Read();
    return obj;
}

void Controls::Read()
{
    uint8_t value = 0;
    std::string str;
    while (1)
    {
        // Read some data
        value = bcm2835_gpio_lev(PIN_GREEN_BUTTON);
        if ( 0 == value )
        {
            bcm2835_gpio_write(PIN_RED_LIGHT, LOW);
            bcm2835_gpio_write(PIN_GREEN_LIGHT, HIGH);
       	    mSerPointer->Read(mId);
            ShowId();
            bcm2835_gpio_write(PIN_GREEN_LIGHT, LOW);
            bcm2835_gpio_write(PIN_RED_LIGHT, HIGH);
        }
        // wait a bit
        delay(500);
    }
};

void Controls::ShowId()
{
    std::cout<<mId<<std::endl;
}

