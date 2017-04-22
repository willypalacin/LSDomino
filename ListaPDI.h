#ifndef _LISTAPDI_H_
#define _LISTAPDI_H_

#define ELEMENTO_INDEFINIDO "Error, la lista esta vacia"

typdef struct {
    int cara1;
    int cara2;
} Ficha;

typdef struct _Nodo {
    Ficha f;
    struct _Nodo * sig;
} Nodo;

typdef struct {
  Nodo * pri;
  Nodo * ant;
} ListaPDI;

ListaPDI LISTAPDI_crea();
void LISTAPDI_inserir (ListaPDI * l, Ficha f);
void LISTAPDI_borrar (ListaPDI * l);
Ficha LISTAPDI_consultar (ListaPDI l);
int LISTAPDI_estaVacia (ListaPDI l);
void LISTAPDI_irInicio (ListaPDI * l);
void LISTAPDI_avanzar (ListaPDI * l);
void LISTAPDI_final (ListaPDI l);
void LISTAPDI_destruye (ListaPDI * l);

#endif
