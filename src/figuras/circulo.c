#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "circulo.h"


typedef struct circulo {
    double x,y,r,cw;
    char cor1[50],cor2[50],id[20];
} *pCirculo;


Circulo addCirculo(char comandos[500],double rw) {
    double x=0,y=0,r=0;
    char cor1[50]={},cor2[50]={},id[20]={};
    struct circulo *temp = (struct circulo*)calloc(1,sizeof(struct circulo));

    sscanf(comandos,"c %s %lf %lf %lf %s %s",id,&r,&x,&y,cor1,cor2);

    strcpy(temp->id,id);
    temp->r = r;
    temp->x = x;
    temp->y = y;
    strcpy(temp->cor1,cor1);
    strcpy(temp->cor2,cor2);

    return (void*)temp;
}

char* getCirculoID(Circulo recebeCirculo) {
    struct circulo *temp = (struct circulo*) recebeCirculo;
    return temp->id;
}

double getCirculoX(Circulo recebeCirculo) {
    struct circulo *temp = (struct circulo*) recebeCirculo;
    return temp->x;
}

double getCirculoY(Circulo recebeCirculo) {
    struct circulo *temp = (struct circulo*) recebeCirculo;
    return temp->y;
}

double getCirculoRaio(Circulo recebeCirculo) {
    struct circulo *temp = (struct circulo*) recebeCirculo;
    return temp->r;
}

char *getCirculoCfill(Circulo recebeCirculo) {
    struct circulo *temp = (struct circulo*) recebeCirculo;
    return temp->cor1;
}

char *getCirculoCstrk(Circulo recebeCirculo) {
    struct circulo *temp = (struct circulo*) recebeCirculo;
    return temp->cor2;
}

double getCirculoCw(Circulo recebeCirculo) {
    struct circulo *temp = (struct circulo*) recebeCirculo;
    return temp->cw;
}

void setCirculoX(Circulo recebeCirculo,double nX) {
    struct circulo *temp = (struct circulo*) recebeCirculo;
    temp->x = nX;
}

void setCirculoY(Circulo recebeCirculo,double nY) {
    struct circulo *temp = (struct circulo*) recebeCirculo;
    temp->y = nY;
}

void removeCirculo(Circulo recebeCirculo) {
    struct circulo *temp = (struct circulo*) recebeCirculo;
    free(temp);
}

int comparaCirculo(Circulo recebeCirculo1,Circulo recebeCirculo2) {
    struct circulo *temp1 = (struct circulo*) recebeCirculo1;
    struct circulo *temp2 = (struct circulo*) recebeCirculo2;

    if(temp1->x > temp2->x) {
        return 1;
    } else if(temp1->x < temp2->x) {
        return -1;
    } else if(temp1->y > temp2->y) {
        return 1;
    } else if(temp1->y < temp2->y) {
        return -1;
    }
    return 0;
}

int comparaIdCirculo(Circulo recebeCirculo1,Circulo recebeCirculo2) {
    struct circulo *temp1 = (struct circulo*) recebeCirculo1;
    struct circulo *temp2 = (struct circulo*) recebeCirculo2;

    return strcmp(temp1->id, temp2->id);
}

int comparaKeyCirculo(Circulo recebeCirculo, char *key) {
    struct circulo *temp = (struct circulo*) recebeCirculo;
    return strcmp(temp->id, key);
}
