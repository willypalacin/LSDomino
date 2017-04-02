#include "ranking.h"


void mostrarRanking (){
  FILE * fichero;
  int num_jugadores;

  fichero = fopen ("ranking.bin", "rb");
  if (fichero == NULL){
    printf("%s\n", ERROR_FICHERO);
  }
  else {
    fread (&num_jugadores, sizeof(int), 1, fichero);
    muestraJugadores (fichero, num_jugadores);
    fclose (fichero);
  }
}

void mostrarJugadores (FILE * fichero, int num_jugadores){
  Jugador * jugadores;
  int i;

  jugadores = (Jugador *) malloc (sizeof (Jugador) * (num_jugadores - 1));
  if (jugadores == NULL){
    printf("%s\n", ERROR_MEMORIA);
  }
  else {
    for (i = 0; = < num_jugadores; i++){
      fread (jugadores[i], sizeof(Jugador), 1, f);
      printarDatos (jugadores[i]);
    }
  }

}

void printarDatos (Jugador j){
  printf ("Jugador: %s\n", j.nombre);
  printf ("P.Ganadas: %d\n", j.p_ganadas);
  printf ("P.perdidas: %d\n", j.p_perdidas);
  printf ("P.Totales: %d\n", j.p_totales);
  printf ("Win Rate: %f\n", j.win_rate);

}
