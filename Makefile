Driver: Structs.cpp Driver.cpp
	g++  -o a.out -Wall -Werror Structs.cpp Driver.cpp Algorithms.cpp
clean: a.out
	rm a.out

a: Driver
	rm a.out
	git add *.h *.cpp *.txt Makefile
	git commit -m "make"
	git push -u chicken master


