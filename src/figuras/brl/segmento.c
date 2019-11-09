#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"segmento.h"
#include"vertice.h"

typedef struct {
    Vertice v1;
    Vertice v2;
    int tipo;
    int ativo;
}Segmentoimpl;


Segmento criaSegmento(Vertice v1,Vertice v2,int tipo,int ativo){
    Segmentoimpl *s = malloc(sizeof(Segmentoimpl));
    s->v1=v1;
    s->v2=v2;
    s->tipo=tipo;
    s->ativo=ativo;
    return s;
}

Vertice getV1Segmento(Segmento M){
    Segmentoimpl *s = M;
    return s->v1;
}

Vertice getV2Segmento(Segmento M){
    Segmentoimpl *s = M;
    return s->v2;
}

int getTipoSegmento(Segmento M){
    Segmentoimpl *s = M;
    return s->tipo;
}

int isSegmentoAtivo(Segmento M){
    Segmentoimpl *s = M;
    return s->ativo;
}

void ativaSegmento(Segmento M){
    Segmentoimpl *s = M;
    s->ativo=1;
}

void desativaSegmento(Segmento M){
    Segmentoimpl *s = M;
    s->ativo=0;
}

void swapVertices(Segmento M){
    Segmentoimpl *s = M;
    Vertice aux = s->v1;
    s->v1=s->v2;
    s->v2=aux;
}
