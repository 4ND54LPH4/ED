#ifndef ___SEGMENTO_H
#define ___SEGMENTO_H
#include"vertice.h"

typedef void* Segmento;

// cria uma "instancia" de Segmento
Segmento criaSegmento(Vertice v1,Vertice v2,int tipo,int ativo);
// retorna o vertice v1(Inicio) do segmento
Vertice getV1Segmento(Segmento M);
// retorna o vertice v2(Fim) do segmento
Vertice getV2Segmento(Segmento M);
// inverte os segmentos v1 e v2
void swapVertices(Segmento M);
// retorna o tipo de segmento (Artificial,Natural)
int getTipoSegmento(Segmento M);
// retorna o estado do segmento (Ativo ou Desativo)
int  isSegmentoAtivo(Segmento M);
// ativa o segmento
void ativaSegmento(Segmento M);
// desativa o segmento
void desativaSegmento(Segmento M);

#endif
