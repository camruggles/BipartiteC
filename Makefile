Driver: Structs.cpp Driver.cpp
	g++ -o a.out -Wall -Werror Structs.cpp Driver.cpp Algorithms.cpp

clean: a.out
	rm a.out
