CXX= g++
LIBS= -pthread -std=c++11
OUTPUT= primer
DEBUG=
WARN=-W -Wall -Wextra -Werror
OPTIMIZATION=-O2

primer: main.cpp
	$(CXX) $(DEBUG) $(OPTIMIZATION) $(WARN) $(LIBS) main.cpp -o $(OUTPUT)

