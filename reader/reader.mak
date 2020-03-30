CC=arm-linux-gnueabihf-g++
INCLUDES=-Iinclude  -I/home/yoda/Documents/computer/development/raspberrypi/bcm2835-1.63/src
CFLAGS=-c -Wall -DLINUX -Wno-deprecated -pthread -g
LDFLAGS=-lm -lpthread
TARGET=reader
LIB=/home/yoda/Documents/computer/development/raspberrypi/bcm2835-1.63/src/libbcm2835.a
SOURCES= src/MySerial.cpp \
         src/Controls.cpp \
         src/Lcd.cpp \
         src/reader.cpp

OBJS=$(SOURCES:.cpp=.o)

all: $(SOURCES) $(TARGET)

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS) $(LDFLAGS) $(LIB)

.cpp.o: 
	$(CC) -c $(CFLAGS) $(INCLUDES) $< -o $@

clean:
	rm -rf $(TARGET)
	rm -rf src/*.o

install:
	scp src/*cpp yoda@raspberrypi:/home/yoda/reader/src
	scp include/*h yoda@raspberrypi:/home/yoda/reader/include
	scp reader yoda@raspberrypi:/home/yoda/reader/
	scp reader.mak yoda@raspberrypi:/home/yoda/reader/
