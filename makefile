#
# Specifiy the target
all:	War.exe

# Specify the object files that the target depends on
# Also specify the object files needed to create the executable
War.exe:	PlayingCard.o War.o Program2.o
	g++  PlayingCard.o War.o Program2.o -o War.exe

# Specify how the object files should be created from source files
Program2.o:	Program2.cpp 
	g++ -c -g Program2.cpp
War.o:	War.cpp 
	g++ -c -g War.cpp
PlayingCard.o:	PlayingCard.cpp PlayingCard.h
	g++ -c -g PlayingCard.cpp

# Specify the object files and executables that are generated
# and need to be removed to re-compile the whole thing
clean:
	rm -f *.o War.exe

