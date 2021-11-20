render.o: render.cpp render.h
	g++ -c render.cpp
library.o: library.cpp library.h
	g++ -c library.cpp
main.o:	render.h library.h main.cpp
	g++ -c main.cpp
main: render.o library.o main.o
	g++ -pedantic-errors -std=c++11 render.o library.o main.o -o main
clean:
	rm -f main main.o render.o library.o
