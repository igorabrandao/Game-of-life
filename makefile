#
<<<<<<< HEAD
# Makefile build 'Game of Life' using Make
=======
# Makefile build 'game of life' using Make
>>>>>>> a26909338bb9586f56a7907b3c8a31bccd2f7670
#

SOURCES = $(wildcard src/*.cpp)

CC      = g++
<<<<<<< HEAD
CFLAGS  = -c -g -Wall -std=c++11
=======
CFLAGS  = -c -g -Wall -std=c++0x
>>>>>>> a26909338bb9586f56a7907b3c8a31bccd2f7670

INC_DIR = ./include
BIN_DIR = ./bin
APP     = $(BIN_DIR)/life
<<<<<<< HEAD
LIB_DIR = 
LIBS = \
	-lsfml-graphics         \
	-lsfml-audio 	        \
	-lsfml-window           \
	-lsfml-system
=======
>>>>>>> a26909338bb9586f56a7907b3c8a31bccd2f7670

OBJECTS = $(SOURCES:.cpp=.o)

all: $(SOURCES) $(APP)
    
$(APP): $(OBJECTS) 
<<<<<<< HEAD
	$(CC) -o $@ $(OBJECTS) $(LIBS)

.cpp.o:
	$(CC) $< -o $@ $(CFLAGS) -I$(INC_DIR)
=======
	$(CC) -o $@ $(OBJECTS)

.cpp.o:
	$(CC) $< -o $@ $(CFLAGS) -I$(INC_DIR)

exe:
	$(APP)
>>>>>>> a26909338bb9586f56a7907b3c8a31bccd2f7670
