#include <stdio.h>
#include "menu.h"
#include <conio.h>
#include <string.h>


void main () {
  int opcion;
  do {
    mostrarMenu();
    fflushnou();
    scanf("%d", &opcion);
    seleccionarOpcion(opcion);
  } while (opcion != 3);


}
