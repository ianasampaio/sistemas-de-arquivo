

all:
	gcc -c src/file_system.c -I include/ -o obj/file_system.o
	gcc ./main/main.c ./obj/file_system.o -I ./include -o ./bin/main

run:
	./bin/main

clean:
	rm -rf  ./bin/* ./obj/*