#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"ponto.h"

typedef struct {
    double x,y;
} Pontoimpl;


Ponto criaPonto(double x,double y){
    Pontoimpl *m = malloc(sizeof(Pontoimpl));
    m->x=x;
    m->y=y;
    return m;
}

double getXPonto(Ponto M){
    Pontoimpl *m = M;
    return m->x;
}

double getYPonto(Ponto M){
    Pontoimpl *m = M;
    return m->y;
}
