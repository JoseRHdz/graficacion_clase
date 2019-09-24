OBJS = $(LIB)ProgramShader.o $(LIB)ShaderException.o Square.o	Window.o main.o

INCLUDES = *.h 
LIBS = -lglfw -lGL -lGLEW
CC = g++
CFLAGS = -c -g -O2 -Wall

BIN = bin/
LIB = ../lib/

%.o: %.cpp
	$(CC) $(CFLAGS)	$(LIBS) $< -o $@

TARGET = $(BIN)cube

all: $(TARGET)

$(TARGET): $(OBJS)
	@if not test -d $(BIN); \
  	then mkdir $(BIN); \
  fi
	$(CC) $(LIBS) -o $@ $(OBJS)
	@echo ">>>>>>>>>>>>>>>El ejecutable está dentro de bin/<<<<<<<<<<<<<<<"

clean:
	rm *.o ../lib/*.o *~ -r $(BIN)
