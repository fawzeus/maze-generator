# the compiler: gcc for C program, define as g++ for C++
CC = g++

# compiler flags:
#  -g     - this flag adds debugging information to the executable file
#  -Wall  - this flag is used to turn on most compiler warnings
CFLAGS  = -std=c++11 -Wall

# SFML libraries
SFML_LIBRARIES = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

SOURCE = *.cpp

# The build target
TARGET = maze-generator

all: $(TARGET)
	@echo "\n Build completed successfully! Run ./$(TARGET) to execute your program !"

$(TARGET): $(SOURCE)
	$(CC) -o $(TARGET) $(SOURCE) $(CFLAGS) $(SFML_INCLUDE) $(SFML_LIBRARIES)

clean:
	rm -f $(TARGET)
