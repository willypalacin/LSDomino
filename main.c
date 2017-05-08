#include <stdio.h>
#include "menu.h"
#include <conio.h>
#include <string.h>

#define ERROR_ARGC "Error, el formato introducido es incorrecto. Debe anadir los dos ficheros."
#define CREAR_RANKING "No existe el fichero Ranking... Creando ranking.bin"
#define ERROR_NOMBRE_FICHERO_PLAYERS "Error al abrir el fichero de jugadores. Recuerde que debe llamarse player.txt"


/*void crearFichero (){
  FILE * fichero;
  int num_jugadores;
  Jugador jugador;

  fichero = fopen ("ranking.bin", "wb");
  if (fichero == NULL){
    fflush(stdout);
    printf ("%s\n", "No se puede abrir el fichero");
  }
  else {
    num_jugadores = 3;
    fwrite (&num_jugadores, sizeof(int), 1, fichero);
    jugador.nombre = "Pepe";
    jugador.p_perdidas = 2;
    jugador.p_ganadas = 4;

    fwrite (&jugador, sizeof(Jugador),1,fichero);

    jugador.nombre = "Josemi";
    jugador.p_perdidas = 3;
    jugador.p_ganadas = 5;

    fwrite (&jugador, sizeof(Jugador),1,fichero);

    jugador.nombre = "AlbertTRIAS";
    jugador.p_perdidas = 3;
    jugador.p_ganadas = 43;
    fwrite (&jugador, sizeof(Jugador),1,fichero);

    fclose (fichero);
}
}
*/

int main (int argc, char* *argv) {
  FILE * f;
  int opcion;

  if (argc != 3) {
    printf("%s\n", ERROR_ARGC );

  }
  else {
    f = fopen(argv[1], "r");
    if(strcmp(argv[2], "player.txt") != 0) {
      printf("%s\n", ERROR_NOMBRE_FICHERO_PLAYERS);


    }
    else {
      if (f == NULL) {
        printf("%s\n", CREAR_RANKING );
        f = fopen("ranking.bin", "wb");

      }
      fclose(f);
      do {
        MENU_mostrarMenu();
        fflushnou();
        scanf("%d", &opcion);
        MENU_seleccionarOpcion(opcion);
      } while (opcion != 3);
    }
  }

  //crearFichero();



return 0;
}
