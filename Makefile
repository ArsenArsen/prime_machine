CXX= g++
LIBS= -pthread -std=c++11
OUTPUT= primer
DEBUG=
OPTIMIZATION=-O2

all:
	$(CXX) $(DEBUG) $(OPTIMIZATION) $(LIBS) main.cpp -o $(OUTPUT)

