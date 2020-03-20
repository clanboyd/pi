CC=g++
INCLUDES=-Iinclude 
CFLAGS=-c -Wall -DLINUX -Wno-deprecated -pthread -g
LDFLAGS=-lm -lpthread
TARGET=reader
LIB=/usr/local/lib64/libbcm2835.a
SOURCES= src/MySerial.cpp \
         src/Controls.cpp \
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

