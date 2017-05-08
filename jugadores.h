
#ifndef _JUGADORES_H_
#define _JUGADORES_H_

#define ERROR_FICHERO_JUGADORES "Ha habido un error al abrir el fichero de jugadores, por favor asegurese que no ha eliminado dicho fichero"
#define ERROR_MEMORIA "Error al generar memoria"
#define ERROR_ESTRUCTURA_JUGADORES "Error al crear la estructura de los jugadores"

#include <stdio.h>
#include <stdlib.h>
#include "conio.h"
#include <string.h>

typedef struct {
  char * nombre;
  int turno;

}Player;

void JUGADORES_leerFichero(Player ** players, int * num_players);
void JUGADORES_asignarCadena(Player ** players, char cadena[20], int w);
void JUGADORES_guardarEnEstructura (FILE * f, Player ** players, int num_players);
void JUGADORES_ordenSegunTurno(Player ** players, int num_players);

#endif
