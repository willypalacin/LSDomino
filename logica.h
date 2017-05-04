#ifndef _LOGICA_H_
#define _LOGICA_H_

#include "ListaPDI.h"
#include "jugadores.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct {
  int inserida;
  Ficha f;

} Ficha_inserir;

void LOGICA_generarFichas(ListaPDI * l);
void LOGICA_fichasRandom(ListaPDI * l);
void LOGICA_desordenarFichas(Ficha_inserir fichas[28]);
void LOGICA_anadirFichasALista (ListaPDI * l, Ficha_inserir fichas[28]);
void LOGICA_robarFicha(ListaPDI * l, ListaPDI * lista_jugadores, int i);
void LOGICA_pintarTablero(ListaPDI * l);
void LOGICA_dinamicaJuego(ListaPDI* l, ListaPDI * lista_jugadores, Player * players, int num_players);
void LOGICA_mostrarFichasJugador(ListaPDI * lista_jugadores, ListaPDI * l ,int i);
int LOGICA_sePuedeColocarFicha(ListaPDI * l, Ficha f);
void LOGICA_llevarOpcionATablero(ListaPDI * l,ListaPDI * lista_jugadores, int opcion, int i, int j);

#endif
