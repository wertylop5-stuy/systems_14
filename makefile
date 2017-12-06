sem: main.o
	gcc -o sem main.o
	make clean

main.o: main.c
	gcc -c main.c

clean:
	rm *.o

run:
	./sem
