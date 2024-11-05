build: 
	gcc main.c -o main -lSDL2main -lSDL2

run:
	./main

build-run:
	make build
	make run

install-sdl:
	sudo apt install libsdl2-dev