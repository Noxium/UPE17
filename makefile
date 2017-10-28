CXX = g++
CXXFLAGS = -c -g -std=c++11 -Wall -W -Werror -pedantic
LDFLAGS = 

bjack: bjack.o main.o
	$(CXX) $(LDFLAGS) main.o bjack.o -o bjack

main.o: main.cpp bjack.h

bjack.o: bjack.cpp bjack.h main.cpp
	$(CXX) $(CXXFLAGS) bjack.cpp

clean:
	rm *o bjack
