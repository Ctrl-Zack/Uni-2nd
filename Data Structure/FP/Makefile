# .exe name
TARGET = menu_app

# Compiler and flags
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -Iheader

# source and header
SRC = $(wildcard source/*.cpp)
OBJ = $(SRC:source/%.cpp=%.o)

# Build rules
all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: source/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean rule
clean:
	del /Q *.o *.exe 2>nul || rm -f *.o $(TARGET)

# Phony targets
.PHONY: all clean