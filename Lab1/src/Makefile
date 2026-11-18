CXX ?= g++
CXXFLAGS := -std=c++20 -Wall -Wextra -Wpedantic -Werror -pedantic-errors -I.
LDFLAGS ?=
RM := del /Q

TARGET := town_sim

SOURCES := main.cpp
OBJECTS := $(SOURCES:.cpp=.o)
TEST_SOURCES := tests/tests.cpp
TEST_OBJECTS := $(TEST_SOURCES:.cpp=.o)

.PHONY: all clean run test

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

run: $(TARGET)
	./$(TARGET)

test:
	@echo "No runnable tests configured for Lab1."

tests/%.o: tests/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	-$(RM) $(OBJECTS) $(TARGET) $(TARGET).exe
	-$(RM) tests\tests.o
