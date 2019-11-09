#ifndef ___VERTICE_H
#define ___VERTICE_H
#include "ponto.h"

typedef void* Vertice;

// cria uma instancia de vertice
Vertice criaVertice(Ponto p,int InicioOuFim, double Angulo);
// retorna x do vertice
double getXVertice(Vertice v);
// retorna y do vertice
double getYVertice(Vertice v);
// retorna angulo do vertice
double getAnguloVertice(Vertice v);
// retorna ponto do vertice
Ponto getPonto(Vertice v);
// set inicio ou fim do vertice
void setInicioFim(Vertice v,int op);
// verifica inicio ou fim do vertice
int isInicioOuFim(Vertice v);
// seta o ponteiro do segmento no vertice
void setSegmento(Vertice V,void* s);
// retorna o segmento do vertice
void* getSegmento(Vertice V);

#endif
