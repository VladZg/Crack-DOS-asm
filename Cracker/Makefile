all: compile link run

compile:
	@mkdir ./Obj
	@g++ -c app.cpp -I/usr/include/ -o ./Obj/app.o
	@g++ -c ./Source/AppUtils.cpp	-o ./Obj/AppUtils.o
	@g++ -c ./Source/CrackUtils.cpp	-o ./Obj/CrackUtils.o

link:
	@g++ ./Obj/app.o ./Obj/AppUtils.o ./Obj/CrackUtils.o -o app -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system

run:
	@./app

clean:
	@rm -r -f ./Obj
