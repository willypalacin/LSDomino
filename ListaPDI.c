#include "ListaPDI.h"




ListaPDI LISTAPDI_crea () {
  ListaPDI l;
  l.pri = (Nodo *) malloc (sizeof(Nodo));
  if (l.pri != NULL) {
      l.ant = l.pri;
      l.pri -> sig = NULL;
  }
  return l;
}
void LISTAPDI_inserir (ListaPDI * l, Ficha f) {
  Nodo * n = NULL;
  n = (Nodo *) malloc (sizeof(Nodo));
  if (n != NULL) {
    n -> f = f;
    n -> sig = l -> ant -> sig;
    l -> ant -> sig = n;
    l -> ant = n;
  }
}

void LISTAPDI_borrar (ListaPDI * l) {
  Nodo * n;
  if (l -> ant -> sig != NULL) {
    n = l -> ant -> sig;
    l -> ant -> sig = n -> sig;
    free (n);
  }
}

Ficha LISTAPDI_consultar (ListaPDI l) {
  Ficha ELEMENTO_INDEFINIDO;
  ELEMENTO_INDEFINIDO.cara1 = 7;
  ELEMENTO_INDEFINIDO.cara2 = 7;
  Ficha f;
  if ( l.ant -> sig == NULL) {
    f = ELEMENTO_INDEFINIDO;
  }
  else {
    f = l.ant -> sig -> f;
  }
  return f;
}

int LISTAPDI_estaVacia (ListaPDI l) {
  return l.pri -> sig == NULL;
}

void LISTAPDI_irInicio (ListaPDI * l) {
  l->ant = l -> pri;
}

void LISTAPDI_avanzar (ListaPDI * l) {
  if (l -> ant -> sig != NULL) {
    l -> ant = l -> ant -> sig;
  }
}



int LISTAPDI_final (ListaPDI  l) {
  return (l.ant -> sig == NULL);
}

Ficha LISTAPDI_consultarFinalLista(ListaPDI * l) {
  LISTAPDI_irInicio(l);
  while(LISTAPDI_final(*l) == 0) {
    LISTAPDI_avanzar(l);

  }

  return l->ant->f;
}

void LISTAPDI_destruye (ListaPDI * l) {
  LISTAPDI_irInicio (l);
  while (!LISTAPDI_estaVacia (*l)) {
    LISTAPDI_borrar (l);
  }
  free (l -> pri);
  l -> pri = NULL;
  l -> ant = NULL;
}
