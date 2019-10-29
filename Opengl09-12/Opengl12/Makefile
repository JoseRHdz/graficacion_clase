OBJS = $(LIB)ProgramShader.o $(LIB)ShaderException.o Geometry.o Window.o Texture.o Loader.o main.o

INCLUDES = *.h 
LIBS = -std=c++14 -lglfw -lGL -lGLEW -lassimp
CXX = g++
CXXFLAGS = -c -g -O2 -Wall

BIN = bin/
LIB = ../lib/

%.o: %.cpp	
	$(CXX) $(CXXFLAGS) $< -o $@

TARGET = geometry

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(LIBS) -o $@ $(OBJS)

clean:
	rm *.o ../lib/*.o geometry
