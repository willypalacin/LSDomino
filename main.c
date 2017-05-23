#include <stdio.h>
#include "menu.h"
#include <conio.h>
#include <string.h>

#define ERROR_ARGC "Error, el formato introducido es incorrecto. Debe anadir los dos ficheros."
#define CREAR_RANKING "No existe el fichero Ranking... Creando ranking.bin"
#define ERROR_NOMBRE_FICHERO_PLAYERS "Error al abrir el fichero de jugadores. Recuerde que debe llamarse player.txt"




int main (int argc, char* *argv) {
  FILE * f;
  char opcion[20];
  int opc;


  if (argc != 3) {
    printf("%s\n", ERROR_ARGC );

  }
  else {
    f = fopen(argv[1], "r");
    if(fopen(argv[2], "r") == NULL) {
      printf("NO SE ENCONTRO EL FICHERO DE JUGADORES\n");


    }
    else {
      if (f == NULL) {
        printf("%s\n", CREAR_RANKING );
        f = fopen("ranking.bin", "wb");

      }
      fclose(f);
      do {
        MENU_mostrarMenu();
        fflushnou();
        gets(opcion);
        opc = opcion[0] - '0';
        MENU_seleccionarOpcion(opc);
      } while (opc != 3);
    }
  }

  //crearFichero();



return 0;
}
