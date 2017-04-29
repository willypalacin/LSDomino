
#ifndef _JUGADORES_H_
#define _JUGADORES_H_

#define ERROR_FICHERO_JUGADORES "Ha habido un error al abrir el fichero de jugadores, por favor asegurese que no ha eliminado dicho fichero"
#define ERROR_MEMORIA "Error al generar memoria"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  char * nombre;
  int turno;

}Player;

void JUGADORES_leerFichero(Player ** players, int * num_players);
void JUGADORES_asignarCadenaNombre(char * nombre, int * turno, char cadena[20]);
void JUGADORES_guardarEnEstructura (FILE * f, Player ** players, int num_players);

#endif
