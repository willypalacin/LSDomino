#include <stdio.h>
#include "menu.h"
#include <conio.h>
#include <string.h>


void crearFichero (){
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

int main () {
  int opcion;
  crearFichero ();

  do {
    MENU_mostrarMenu();
    fflushnou();
    scanf("%d", &opcion);
    MENU_seleccionarOpcion(opcion);
  } while (opcion != 3);

return 0;
}
