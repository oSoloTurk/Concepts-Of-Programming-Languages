all: clean run

clean:
	gcc -I ./include/ -o ./lib/Dosya.o -c ./src/Dosya.c
	gcc -I ./include/ -o ./lib/Kisi.o -c ./src/Kisi.c 
	gcc -I ./include/ -o ./lib/Oyun.o ./lib/Kisi.o ./lib/Dosya.o -c ./src/Oyun.c 
	gcc -I ./include/ -o ./lib/Arayuz.o ./lib/Kisi.o -c ./src/Arayuz.c 
	gcc -I ./include/ -o ./bin/Test ./lib/Dosya.o ./lib/Kisi.o ./lib/Oyun.o ./src/Test.c

run:
	./bin/Test