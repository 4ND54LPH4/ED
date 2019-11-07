#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "retangulo.h"


typedef struct retangulo {
    double rw;
    double x,y,w,h;
    char cor1[50],cor2[50],id[20];
} *pRetangulo;


Retangulo addRetangulo(char comandos[500],double rw) {
    double x,y,w,h;
    char cor1[50]={},cor2[50]={},id[20]={};
    struct retangulo *temp = (struct retangulo*)calloc(1,sizeof(struct retangulo));

    sscanf(comandos,"r %s %lf %lf %lf %lf %s %s",id,&w,&h,&x,&y,cor1,cor2);

    strcpy(temp->id,id);
    temp->x = x;
    temp->y = y;
    temp->w = w;
    temp->h = h;
    temp->rw = rw;
    strcpy(temp->cor1,cor1);
    strcpy(temp->cor2,cor2);

    return (void*)temp;
}

char* getRetanguloID(Retangulo recebeRetangulo) {
    struct retangulo *temp = (struct retangulo*) recebeRetangulo;
    return temp->id;
}

double getRetanguloX(Retangulo recebeRetangulo) {
    struct retangulo *temp = (struct retangulo*) recebeRetangulo;
    return temp->x;
}

double getRetanguloY(Retangulo recebeRetangulo) {
    struct retangulo *temp = (struct retangulo*) recebeRetangulo;
    return temp->y;
}

char *getRetanguloCfill(Retangulo recebeRetangulo) {
    struct retangulo *temp = (struct retangulo*) recebeRetangulo;
    return temp->cor1;
}

char *getRetanguloCstrk(Retangulo recebeRetangulo) {
    struct retangulo *temp = (struct retangulo*) recebeRetangulo;
    return temp->cor2;
}

double getRetanguloRw(Retangulo recebeRetangulo) {
    struct retangulo *temp = (struct retangulo*) recebeRetangulo;
    return temp->rw;
}

void setRetanguloX(Retangulo recebeRetangulo,double nX) {
    struct retangulo *temp = (struct retangulo*) recebeRetangulo;
    temp->x = nX;
}

void setRetanguloY(Retangulo recebeRetangulo,double nY) {
    struct retangulo *temp = (struct retangulo*) recebeRetangulo;
    temp->y = nY;
}

double getRetanguloAltura(Retangulo recebeRetangulo) {
    struct retangulo *temp = (struct retangulo*) recebeRetangulo;
    return temp->h;
}

double getRetanguloLargura(Retangulo recebeRetangulo) {
    struct retangulo *temp = (struct retangulo*) recebeRetangulo;
    return temp->w;
}

void removeRetangulo(Retangulo recebeRetangulo) {
    struct retangulo *temp = (struct retangulo*) recebeRetangulo;
    free(temp);
}

int comparaRetangulo(Retangulo recebeRetangulo1,Retangulo recebeRetangulo2) {
    struct retangulo *temp1 = (struct retangulo*) recebeRetangulo1;
    struct retangulo *temp2 = (struct retangulo*) recebeRetangulo2;

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

int comparaIdRetangulo(Retangulo recebeRetangulo1,Retangulo recebeRetangulo2) {
    struct retangulo *temp1 = (struct retangulo*) recebeRetangulo1;
    struct retangulo *temp2 = (struct retangulo*) recebeRetangulo2;

    return strcmp(temp1->id, temp2->id);
}

int comparaKeyRetangulo(Retangulo recebeRetangulo, char* key) {
    struct retangulo *temp = (struct retangulo*) recebeRetangulo;

    return strcmp(temp->id, key);
}
