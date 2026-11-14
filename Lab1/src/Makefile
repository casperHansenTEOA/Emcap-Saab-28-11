CXX ?= g++
CXXFLAGS := -std=c++20 -Wall -Wextra -pedantic -I.
LDFLAGS ?=

TARGET := town_sim

SOURCES := main.cpp \

OBJECTS := $(SOURCES:.cpp=.o)

.PHONY: all clean run

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

run: $(TARGET)
	./$(TARGET)

clean:
	-$(RM) $(OBJECTS) $(TARGET) $(TARGET).exe
