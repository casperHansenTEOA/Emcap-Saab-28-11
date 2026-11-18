CXX ?= g++
CXXFLAGS := -std=c++20 -Wall -Wextra -Wpedantic -Werror -pedantic-errors -I.
LDFLAGS ?=
RM := del /Q

TARGET := town_sim

SOURCES := main.cpp
OBJECTS := $(SOURCES:.cpp=.o)

.PHONY: all clean run test

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

run: $(TARGET)
	./$(TARGET)

test:
	@echo "No tests configured for Lab2."

clean:
	-$(RM) $(OBJECTS) $(TARGET) $(TARGET).exe
