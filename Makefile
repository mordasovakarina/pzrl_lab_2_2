CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2
OBJECTS = VectorStack.o ListStack.o Stack.o
LIB = libstack.a
TEST_LIB = libStackTest.a
TARGET = run_tests

all: $(TARGET)

$(LIB): $(OBJECTS)
	ar rcs $(LIB) $(OBJECTS)

VectorStack.o: VectorStack.cpp VectorStack.h StackImplementation.h
	$(CXX) $(CXXFLAGS) -c VectorStack.cpp -o VectorStack.o

ListStack.o: ListStack.cpp ListStack.h StackImplementation.h
	$(CXX) $(CXXFLAGS) -c ListStack.cpp -o ListStack.o

Stack.o: Stack.cpp Stack.h VectorStack.h ListStack.h
	$(CXX) $(CXXFLAGS) -c Stack.cpp -o Stack.o

$(TARGET): $(LIB)
	ar x $(TEST_LIB)
	$(CXX) $(CXXFLAGS) -o $(TARGET) *.o -L. -lstack

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(OBJECTS) $(LIB) $(TARGET) *.o

.PHONY: all clean run
