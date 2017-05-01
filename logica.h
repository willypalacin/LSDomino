#ifndef _LOGICA_H_
#define _LOGICA_H_

#include "ListaPDI.h"
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


#endif
