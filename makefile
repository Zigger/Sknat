TARGET=$(shell basename 'Sknat')
SOURCES=$(wildcard *.cpp)
OBJECTS=$(SOURCES:%.cpp=%.o)
CFLAGS=-lstdc++ -O2 -lSDL2 -lGL -lGLU -lm

all: $(TARGET)

$(OBJECTS): $(SOURCES)

$(TARGET): $(OBJECTS)
	$(CXX) -o $(TARGET) $(OBJECTS) $(CFLAGS)
	$(RM) $(OBJECTS)
clean:
	$(RM) $(OBJECTS) $(TARGET)

.PHONY: all clean
