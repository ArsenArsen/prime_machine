CXX= g++
LIBS=  -pthread -std=c++11
OUTPUT= primer

all:
	$(CXX) $(LIBS) main.cpp -o $(OUTPUT)

