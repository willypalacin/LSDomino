#ifndef _RANKING_H_
#define _RANKING_H_

#define ERROR_FICHERO "Error, el fichero no puede abrirse o está vacio"
#define ERROR_MEMORIA "Error al generar memoria"

typedef struct {
  char * nombre;
  int p_ganadas;
  int p_perdidas;
  int p_totales;
  float win_rate;
} Jugador

void mostrarRanking ();
void mostrarJugadores (FILE * fichero, int num_jugadores);
void printarDatos (Jugador j);


#endif
