all: P3

main.o: main.c menu.h menu.c
	gcc main.c -c -Wall -Wextra

menu.o: menu.c menu.h ranking.h jugadores.h ListaPDI.h logica.h
	gcc menu.c -c -Wall -Wextra

ranking.o: ranking.c ranking.h jugadores.h
	gcc ranking.c -c -Wall -Wextra

ListaPDI.o: ListaPDI.h
	gcc ListaPDI.c -c -Wall -Wextra

jugadores.o: jugadores.h
		gcc jugadores.c -c -Wall -Wextra

logica.o: logica.h ListaPDI.h
	gcc logica.c -c -Wall -Wextra

P3: main.o menu.o ranking.o jugadores.o ListaPDI.o logica.o
	gcc main.o menu.o ranking.o jugadores.o logica.o ListaPDI.o -o P3.exe -Wall -Wextra

clean:
	rm *.o P3.exe

tar:
	tar -cvzf p3.tar.gz *.c *.h makefile
