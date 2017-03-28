#ifndef _MENU_H_
#define _MENU_H_

#include <stdio.h>

#define MENU_WELCOME "Bienvenido al Domino La Salle !"
#define MENU_OP1 "1. Nueva Partida"
#define MENU_OP2 "2. Mostrar Ranking"
#define MENU_OP3 "3. Mostrar Ranking"
#define MENSAJE_ERROR_OPCION "Error, solo se admite un numero del 1 al 3"
#define SALIR 3


void mostrarMenu ();
void seleccionarOpcion (int opcion);


#endif
