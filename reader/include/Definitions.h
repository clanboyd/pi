#ifndef DEFINITIONS_H
#define DEFINITIONS_H

#define PIN_RED_LIGHT RPI_GPIO_P1_16
#define PIN_RED_BUTTON RPI_GPIO_P1_22
#define PIN_GREEN_LIGHT RPI_GPIO_P1_12
#define PIN_GREEN_BUTTON RPI_GPIO_P1_15

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <termios.h>
#include <fcntl.h>
#include <unistd.h>
#include <cstring>
#include <string>
#include <bcm2835.h>
#include <pthread.h>
#include "MySerial.h"


#endif // DEFINITIONS_H

