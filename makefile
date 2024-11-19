# Compiler and Flags
CXX = g++
CXXFLAGS = -std=c++11 -Wall -g
LDFLAGS = -lcrypt

# Target
TARGET = proj5.x

# Source Files
SOURCES = proj5.cpp passserver.cpp
HEADERS = passserver.h hashtable.h hashtable.hpp

# Object Files
OBJECTS = $(SOURCES:.cpp=.o)

# Build Target
all: $(TARGET)

# Linking the Target
$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

# Compile Sources
%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $<

# Clean Up
clean:
	rm -f $(OBJECTS) $(TARGET)
