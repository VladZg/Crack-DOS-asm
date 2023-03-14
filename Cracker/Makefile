all: compile link run

compile:
	g++ -c main.cpp -I/usr/include/

link:
	g++ main.o -o sfml-app -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system

run:
	./sfml-app

clear:
	rm -f main.o
