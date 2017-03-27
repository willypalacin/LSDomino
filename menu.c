#include <menu.h>


void mostrarMenu() {
  printf("%s\n", MENU_WELCOME);
  printf("\t%s\n", MENU_OP1);
  printf("%s\n", MENU_OP2);
  printf("%s\n", MENU_OP3 );


}

void seleccionarOpcion (int opcion) {
  switch (opcion) {
    case 1:
      printf("%d\n", opcion);
      break;
    case 2:
      printf("%d\n", opcion);
      break;
    case 3:
      printf("%d\n", opcion);
      break;
    default:
      printf("%s", MENSAJE_ERROR_OPCION);
      break;
  }



}
