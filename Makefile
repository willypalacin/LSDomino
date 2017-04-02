all: P3

main.o: main.c menu.h menu.c
	gcc main.c -c -Wall -Wextra

menu.o: menu.c menu.h ranking.h
	gcc menu.c -c -Wall -Wextra

ranking.o: ranking.c ranking.h
	gcc ranking.c -c -Wall -Wextra

P3: main.o menu.o ranking.o
	gcc main.o menu.o -o P3.exe -Wall -Wextra

clean:
	rm *.o P3.exe

tar:
	tar -cvzf p3.tar.gz *.c *.h makefile
