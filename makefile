#
# Makefile build 'game of life' using Make
#

SOURCES = $(wildcard src/*.cpp)

CC      = g++
CFLAGS  = -c -g -Wall -std=c++11

INC_DIR = ./include
BIN_DIR = ./bin
APP     = $(BIN_DIR)/life

OBJECTS = $(SOURCES:.cpp=.o)

all: $(SOURCES) $(APP)
    
$(APP): $(OBJECTS) 
	$(CC) -o $@ $(OBJECTS)

.cpp.o:
	$(CC) $< -o $@ $(CFLAGS) -I$(INC_DIR)

exe:
	$(APP)