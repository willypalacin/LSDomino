#ifndef _RANKING_H_
#define _RANKING_H_

#include <stdio.h>
#include <stdlib.h>

#define MOSTRAR_POSIBILIDADES "Elige formato de ordenacion del ranking"
#define ORDEN_ALFABETICO "1. Ordenar por orden alfabetico de jugadores"
#define ORDEN_WIN_RATE "2. Ordenar por Win Rate descendente de jugadores"
#define ERROR_FICHERO "Error, el fichero no puede abrirse o esta vacio"
#define ERROR_MEMORIA "Error al generar memoria"
#define ERROR_MEMORIA_2 "Error al generar memoria"
#define MENSAJE_ERROR_OPCION "Error, solo se admite un numero del 1 al 3"


typedef struct {
  char * nombre;
  int p_ganadas;
  int p_perdidas;
} Jugador;

typedef struct {
  int p_totales;
  float win_rate;
} Extra_info;

void abrirFichero ();
void crearEstructura (FILE * fichero, int num_jugadores);
//int elegirOrden ();
/*void ordenAlfabetico (extra_info, jugadores);
void ordenWinRate (extra_info, jugadores);*/
void printarDatos (Jugador j, Extra_info extra);


#endif
