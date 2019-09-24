OBJS = Window.o 
LIBS = -lglfw -lGL -lGLEW
CC = g++
CFLAGS = -c -g -O2 -Wall

BIN = bin/

%.o: %.cpp
	$(CC) $(CFLAGS)	$(LIBS) $< -o $@

TARGET = $(BIN)window

all: $(TARGET)

$(TARGET): $(OBJS)
	@if not test -d $(BIN); \
  	then mkdir $(BIN); \
  fi
	$(CC) $(LIBS) -o $@ $(OBJS)
	@echo ">>>>>>>>>>>>>>>El ejecutable está dentro de bin/<<<<<<<<<<<<<<<"

clean:
	rm *.o ../lib/*.o *~ -r $(BIN)
