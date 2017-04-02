#ifndef _RANKING_H_
#define _RANKING_H_

#include <stdio.h>
#include <stdlib.h>

#define ERROR_FICHERO "Error, el fichero no puede abrirse o esta vacio"
#define ERROR_MEMORIA "Error al generar memoria"

typedef struct {
  char * nombre;
  int p_ganadas;
  int p_perdidas;
} Jugador;

typedef struct {
  int p_totales;
  float win_rate;
} Extra_info;

void mostrarRanking ();
void mostrarJugadores (FILE * fichero, int num_jugadores);
void printarDatos (Jugador j, Extra_info extra);


#endif
