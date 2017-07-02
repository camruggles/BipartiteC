Driver: Structs.cpp Driver.cpp
	g++ -o a.out -Wall -Werror Structs.cpp Driver.cpp Algorithms.cpp
	git add *.h *.cpp *.txt
	git commit -m "make"
	git push -u origin master

clean: a.out
	rm a.out
