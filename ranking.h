#ifndef _RANKING_H_
#define _RANKING_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "jugadores.h"
#include <conio.h>

#define MOSTRAR_POSIBILIDADES "Elige formato de ordenacion del ranking"
#define ORDEN_ALFABETICO "1. Ordenar por orden alfabetico de jugadores"
#define ORDEN_WIN_RATE "2. Ordenar por Win Rate descendente de jugadores"
#define ERROR_WIN_RATE "Error, solo puede introducir como opciones el 1 o el 2"
#define ERROR_FICHERO "Error, el fichero no puede abrirse o esta vacio"
#define ERROR_MEMORIA "Error al generar memoria"
#define ERROR_MEMORIA_2 "Error al generar memoria"
#define MENSAJE_ERROR_OPCION "Error, solo se admite un numero del 1 al 3"
#define OPCION_PARA_ORDENAR "\nOpcion para ordenar [1/2]: "
#define OPCION_INHABILITADA "\nLo sentimos, esta opcion está inhabilitada por ahora contacte con atrias@salleurl.edu para mas info\n"
#define FICHERO_VACIO "El fichero no tiene jugadores, no se puede mostrar ranking"


typedef struct {
  char * nombre;
  int p_ganadas;
  int p_perdidas;
} Jugador;

typedef struct {
  int p_totales;
  float win_rate;
} Extra_info;

typedef struct {
  char nombre[20];
  int p_g;
  int p_p;
}J;

void RANKING_abrirFichero(char ** argv);
void RANKING_crearEstructura (FILE * fichero, int num_jugadores);
int RANKING_elegirOrden ();
void RANKING_jugadoresAEstructura(Player * players, Jugador * jugadores,int  num_players, int num_jugs_ranking, int u, char ** argv);
void RANKING_ordenarAlfabetico (Jugador * jugadores, Extra_info * extra_info ,int n);
void RANKING_escribirEnFichero(Jugador *jugadores,int num_jugadores, char ** argv);
void RANKING_numJugadoresIniciales(int * num_jugs_ranking, char ** argv);
void RANKING_jugadoresEmpate(Player * players,Jugador * jugadores,int num_players, int num_jugs_ranking, int jugs_empate[4], char* *argv);
void RANKING_almacenoJugadores(Jugador* *jugadores, int num_jugs_ranking, char ** argv);
void RANKING_ordenWinRate (Jugador * jugadores, Extra_info * extra_info ,int n);
void RANKING_printarDatos (Jugador * j, Extra_info * extra, int num_jugadores);


#endif
