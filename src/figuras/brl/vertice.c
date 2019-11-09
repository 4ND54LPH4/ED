#include"stdio.h"
#include"stdlib.h"
#include"vertice.h"
#include"ponto.h"
#include"segmento.h"

typedef struct {
    Ponto p;
    Segmento pSeg;
    double angulo;
    int InicioOuFim;
}Verticeimpl;


Vertice criaVertice(Ponto p,int InicioOuFim, double Angulo){
    Verticeimpl *v = malloc(sizeof(Verticeimpl));
    v->p = p;
    v->InicioOuFim = InicioOuFim;
    v->angulo = Angulo;
    return v;
}

double getXVertice(Vertice V){
    Verticeimpl *v = V;
    return getXPonto(v->p);
}

double getYVertice(Vertice V){
    Verticeimpl *v = V;
    return getYPonto(v->p);
}

double getAnguloVertice(Vertice V){
    Verticeimpl *v = V;
    return v->angulo;
}

int isInicioOuFim(Vertice V){
    Verticeimpl *v = V;
    return v->InicioOuFim;
}
Ponto getPonto(Vertice V){
    Verticeimpl *v = V;
    return v->p;
}

void setSegmento(Vertice V,Segmento s){
    Verticeimpl *v = V;
    v->pSeg=s;
}

Segmento getSegmento(Vertice V){
    Verticeimpl *v = V;
    return v->pSeg;
}

void setInicioFim(Vertice V,int op){
    Verticeimpl *v = V;
    v->InicioOuFim=op;
}
