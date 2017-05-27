#ifndef _LOGICA_H_
#define _LOGICA_H_

#include "ListaPDI.h"
#include "jugadores.h"
#include "ranking.h"
#include <stdio.h>
#include <time.h>
#include <conio.h>
#include <stdlib.h>

#define NO_SE_PUEDE_FICHA "\nTal y como esta indicado, no es posible pasar esta ficha. \nSe pasa roba por defecto\n"
#define ROBAR_FICHA "\nSe roba ficha\n"
#define PASAR_TURNO "\nSe pasa turno\n"
#define ERROR_OPCION_MAXIMO_PERMITIDO "Error, esta seleccionando una opcion que no esta entre las posibilidades"
#define MENU_IZQ_DCHA "Desea colocarla a la izquierda o derecha\n\t1. Izquierda\n\t2. Derecha\n\t Opcion: "
#define ERROR_OPCION_FICHA_VALIDA "La opcion seleccionada no es valida para colocarse"
#define SE_HA_ROBADO_FICHA_X "Se ha robado la ficha [%d|%d]\n\n -Pulsa una tecla para continuar-\n"
#define EMPATE "Hay empate a la hora de pasar turno en el jugador %d\n"

typedef struct {
  int inserida;
  Ficha f;

} Ficha_inserir;

void LOGICA_generarFichas(ListaPDI * l);
void LOGICA_fichasRandom(ListaPDI * l);
void LOGICA_desordenarFichas(Ficha_inserir fichas[28]);
void LOGICA_anadirFichasALista (ListaPDI * l, Ficha_inserir fichas[28]);
void LOGICA_robarFicha(ListaPDI * l, ListaPDI * lista_jugadores, int i);
void LOGICA_robarFichaYMostrarla(ListaPDI * l, ListaPDI * lista_jugadores, int i);
void LOGICA_pintarTablero(ListaPDI * l);
void LOGICA_dinamicaJuego(ListaPDI * l, ListaPDI * lista_jugadores, ListaPDI * tablero , Player * players, int num_players, Jugador * jugadores, int num_jugs_ranking, char ** argv);
int LOGICA_sePuedeColocarFicha(ListaPDI * l, Ficha f);
int LOGICA_comprobarEmpate(int sumatorio_fichas[4], int jugs_empate[4], int num_players, int u);
int LOGICA_asignarGanador(ListaPDI* lista_jugadores, Player * players ,int num_players, Jugador * jugadores, int num_jugs_ranking, char ** argv);
void LOGICA_mostrarFichasJugador(ListaPDI * lista_jugadores ,ListaPDI * l, ListaPDI * tablero ,int i, int * pasar_turno);
void LOGICA_llevarOpcionATablero(ListaPDI * l, ListaPDI * lista_jugadores, ListaPDI * tablero,int opcion, int i, int j, int contador_flecha, int * pasar_turno);
void LOGICA_inserirIzq(ListaPDI * tablero, ListaPDI * lista_jugadores, Ficha f, int i);
int LOGICA_hayGanador(ListaPDI * lista_jugadores, Player * players, Jugador * jugadores ,int num_players, int pasar_turno, int num_jugs_ranking,char ** argv);
void LOGICA_inserirDcha(ListaPDI * tablero, ListaPDI * lista_jugadores, Ficha f, int i);
void LOGICA_preguntarOpcion(int * opcion, const texto[30]);
void LOGICA_insertarLugarCorrespondiente(ListaPDI * tablero, ListaPDI* lista_jugadores, ListaPDI * l, Ficha f, int ok ,int i, int j, int * pasar_turno);

#endif
