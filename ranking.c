#include "ranking.h"


void mostrarRanking () {
  FILE * fichero;
  int num_jugadores;

  fichero = fopen ("ranking.bin", "rb");
  if (fichero == NULL){
    printf ("%s\n", ERROR_FICHERO);
  }
  else {
    fread (&num_jugadores, sizeof(int), 1, fichero);
    mostrarJugadores (fichero, num_jugadores);
    fclose (fichero);
  }
}

void mostrarJugadores (FILE * fichero, int num_jugadores){
  Jugador * jugadores;
  int i;
  Extra_info * extra_info;

  jugadores = (Jugador *) malloc (sizeof (Jugador) * num_jugadores);
  if (jugadores == NULL){
    printf("%s\n", ERROR_MEMORIA);
  }
  else {
    extra_info = (Extra_info *) malloc ( sizeof(Extra_info) * num_jugadores);
    if (extra_info == NULL){
      printf("%s\n", ERROR_MEMORIA);
    }
    else {
      for (i = 0; i < num_jugadores; i++){
        fread (jugadores[i], sizeof(Jugador), 1, fichero);
        extra_info[i].p_totales = jugadores[i].p_ganadas + jugadores[i].p_perdidas;
        extra_info[i].win_rate = (jugadores[i].p_ganadas / extra_info[i].p_totales) * 100;
        printarDatos (jugadores[i], extra_info[i]);
      }
    }
  }
}


void printarDatos (Jugador j, Extra_info extra){
  printf ("Jugador: %s\n", j.nombre);
  printf ("P.Ganadas: %d\n", j.p_ganadas);
  printf ("P.perdidas: %d\n", j.p_perdidas);
  printf ("P.Totales: %d\n", extra.p_totales);
  printf ("Win Rate: %2.f%%\n", extra.win_rate);

}
