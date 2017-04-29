#include "jugadores.h"


void JUGADORES_leerFichero(Player ** players, int * num_players) {

  FILE * f_players;
  f_players = fopen("player.txt","r");
  if (f_players == NULL) {
    printf("%s\n", ERROR_FICHERO_JUGADORES);

  }
  else {
    fscanf(f_players,"%d", num_players);
    JUGADORES_guardarEnEstructura(f_players, players, *num_players);
  }

}

void JUGADORES_asignarCadena(char * nombre, int * turno, char cadena[20]) {

  int u = 0;
  int i = 0;
  while(cadena[i]!= '/') {
    i++;

  }
  nombre = (char *) malloc((i+1)* sizeof(char));
  if(nombre == NULL) {
    printf("%s\n", ERROR_MEMORIA );

  }
  else {
    while(u <= i) {
      nombre[u] = cadena[u];
      u++;
    }
    *turno = (int) (cadena[u+2] - '0');
  }
  printf("nombre %s\n", nombre);
  cadena = " ";
}

void JUGADORES_guardarEnEstructura (FILE * f_players, Player ** players, int  num_players) {
  int i = 0;
  char cadena[20];

  *players = (Player *) malloc (sizeof(Player) * num_players);

  if (*players == NULL) {
    printf("%s\n", ERROR_MEMORIA );
  }
  else {

    fgets(cadena, 20 , f_players);
    JUGADORES_asignarCadena((*players)[i].nombre, &((*players)[i].turno) ,cadena);
    i = 0;
    while (!feof(f_players)) {
      fgets(cadena, 20 , f_players);
      JUGADORES_asignarCadena((*players)[i].nombre, &((*players)[i].turno) ,cadena);
      i++;
      if(i != num_players) {
        fgets(cadena, 20 , f_players);
        JUGADORES_asignarCadena( (*players)[i].nombre, &((*players)[i].turno) ,cadena);
      }
      else {
        fgets(cadena, 20 , f_players);
      }
    }
  }

  printf("Prueba a Introducir Nombre %d\n", num_players);
  for (i = 0; i < num_players; i++) {
    printf("El nombre del jugador %d es %s y tiene el turno %d\n", i+1 ,(*players)[i].nombre, ((*players)[i].turno));

  }


}
