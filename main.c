#include <stdio.h>
#include <menu.h>
#include <string.h>


void main () {
  int opcion;

  mostrarMenu();
  scanf("%d\n", &opcion);
  fflush(stdin);

  seleccionarOpcion(opcion);



}
