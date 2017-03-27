all: P3

main.o: main.c menu.h
	gcc main.c -c -Wall -Wextra

menu.o: menu.c menu.h
	gcc menu.c -c -Wall -Wextra


P3: main.o menu.o
	gcc main.o menu.o -o P3.exe -Wall -Wextra

clean:
	rm *.o P3.exe

tar:
	tar -cvzf p3.tar.gz *.c *.h makefile
