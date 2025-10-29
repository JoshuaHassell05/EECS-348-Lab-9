CXX = g++
CXXFLAGS = -std=c++17 -Wall
TARGET = main
SRCS = main.cpp

$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) $(SRCS) -o $(TARGET)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)