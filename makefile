# Compiler and flags
CXX := g++
CXXFLAGS := -Wall -Wextra -std=c++11 -Iincludes

# Source files
SRCS := src/main.cpp src/Accounts.cpp src/AccountsManger.cpp src/LibraryManager.cpp

# Object files
OBJS := $(SRCS:.cpp=.o)

TARGET := main

# Default target
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $(TARGET)

# Rule to compile .cpp files into .o files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up build files
clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean
