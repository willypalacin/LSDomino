#include <stdio.h>
#include "menu.h"
#include <conio.h>
#include <string.h>

typedef struct {
  char * nombre;
  int p_ganadas;
  int p_perdidas;
} Jugador;

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
    num_jugadores = 1;
    fwrite (&num_jugadores, sizeof(int), 1, fichero);
    jugador.nombre = "Pepe";
    jugador.p_perdidas = 2;
    jugador.p_ganadas = 4;

    fwrite (&jugador, sizeof(Jugador),1,fichero);

    fclose (fichero);
}
}

int main () {
  int opcion;
  crearFichero ();

  do {
    mostrarMenu();
    fflushnou();
    scanf("%d", &opcion);
    seleccionarOpcion(opcion);
  } while (opcion != 3);

return 0;
}
