#include <stdio.h>
#include <stdlib.h>




void ordenarArray (char letras[8]) {
  int i, j;
  char tmp;
  for (i = 0; i < 8; i++) {
    for (j = 7; j >= i; j--) {
      if (letras[j] < letras[j-1]) {
        tmp = letras[j];
        letras[j] = letras [j - 1];
        letras[j - 1] = tmp;

      }

    }

  }

}

void almacenFichero (FILE* f_vocal, FILE* f_consonante, char letras[8]) {
  int i;
  for (i = 0; i < 8; i++) {
    if (letras[i] == 'a' || letras[i] == 'e' || letras[i] == 'i' || letras[i] == 'o' || letras[i] == 'u') {
      fwrite(&letras[i], sizeof(char), 1, f_vocal);

    }
    else {
      fwrite(&letras[i], sizeof(char), 1, f_consonante);

    }

  }


}


void main() {
  int no_error = 0;
  FILE* f_vocal;
  FILE* f_consonante;
  char letras[8] = {'a', 'z', 'g' , 'f' , 'o' , 'u' , 'e', 'l'};

  f_vocal = fopen("vocales.bin", "wb");
  if (f_vocal == NULL) {
    printf("Error\n");
  }
  else {
    f_consonante = fopen("consonantes.bin", "wb");
    if (f_consonante == NULL) {
      printf("Error\n");
      fclose(f_vocal);

    }
    else {
      ordenarArray(letras);
      almacenFichero(f_vocal, f_consonante ,letras);
      fclose(f_vocal);
      fclose(f_consonante);

    }
  }

}
