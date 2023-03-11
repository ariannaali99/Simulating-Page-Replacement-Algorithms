#Memory Simulation Makefile by Jhun-Thomas Calahatian and Arianna Ali

#C++ Compiler
CC = g++

#Compiler Flags
CFLAGS = -g

#Target Executable
memsim: memsim.o dataStructures.o policies.o
	$(CC) $(CFLAGS) -o memsim memsim.o dataStructures.o policies.o

memsim.o: memsim.cpp utility.hpp dataStructures.hpp policies.hpp
	$(CC) $(CFLAGS) -c memsim.cpp
	
dataStructures.o: dataStructures.hpp
	$(CC) $(CFLAGS) -c -x c++ dataStructures.hpp

policies.o: policies.cpp policies.hpp dataStructures.hpp
	$(CC) $(CFLAGS) -c policies.cpp
	
clean:
	rm memsim memsim.o dataStructures.o policies.o