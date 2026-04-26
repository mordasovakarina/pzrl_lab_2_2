CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2
OBJECTS = Stack.o
LIB = libstack.a
TEST_LIB = libStackTest.a
TARGET = run_tests

all: $(TARGET)

$(LIB): $(OBJECTS)
	ar rcs $(LIB) $(OBJECTS)

Stack.o: Stack.cpp Stack.h StackImplementation.h
	$(CXX) $(CXXFLAGS) -c Stack.cpp -o Stack.o

$(TARGET): $(LIB)
	ar x $(TEST_LIB)
	$(CXX) $(CXXFLAGS) -o $(TARGET) *.o -L. -lstack

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(OBJECTS) $(LIB) $(TARGET) *.o

.PHONY: all clean run
