#ifndef _MENU_H_
#define _MENU_H_


#include "ranking.h"
#include "jugadores.h"
#include <stdio.h>

#define MENU_WELCOME "Bienvenido al Domino La Salle !"
#define MENU_OP1 "1. Nueva Partida"
#define MENU_OP2 "2. Mostrar Ranking"
#define MENU_OP3 "3. Salir"
#define SALIR 3

void MENU_mostrarMenu ();
void MENU_seleccionarOpcion (int opcion);


#endif
