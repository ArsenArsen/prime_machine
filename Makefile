CXX= g++
LIBS= -pthread -std=c++11
OUTPUT= primer
DEBUG=

all:
	$(CXX) $(DEBUG) $(LIBS) main.cpp -o $(OUTPUT)

