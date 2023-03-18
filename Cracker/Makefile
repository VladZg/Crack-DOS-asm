all: compile link run

compile:
	mkdir ./Obj
	g++ -c main.cpp -I/usr/include/ -o ./Obj/main.o
	g++ -c ./Source/AppUtils.cpp	-o ./Obj/AppUtils.o
	g++ -c ./Source/CrackUtils.cpp	-o ./Obj/CrackUtils.o

link:
	g++ ./Obj/main.o ./Obj/AppUtils.o ./Obj/CrackUtils.o -o sfml-app -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system

run:
	./sfml-app

clear:
	rm -r -f ./Obj
