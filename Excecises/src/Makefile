CXX ?= g++
CXXFLAGS := -std=c++20 -Wall -Wextra -pedantic -I.
LDFLAGS ?=

TARGET := town_sim

SOURCES := main.cpp \
    CarPark/CarPark.cpp \
    Garage/Garage.cpp \
    Human/Human.cpp \
    Town/Town.cpp \
    MemoryTracker.cpp \
    Vehicles/Car.cpp \
    Vehicles/Truck.cpp \
    Vehicles/Vehicle.cpp

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
