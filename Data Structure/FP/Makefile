# .exe name
TARGET = menu_app

# Compiler and flags
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17

# source and header
SRC = main.cpp inputlogic.cpp renderscreen.cpp databaselogic.cpp
OBJ = $(SRC:.cpp=.o)

# Build rules
all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^
	@echo Deleting object files...
	@del /Q *.o 2>nul || rm -f *.o

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $<

# Clean rule
clean:
	del /Q *.o *.exe 2>nul || rm -f *.o $(TARGET)

# Phony targets
.PHONY: all clean