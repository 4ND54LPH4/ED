#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "quadra.h"

typedef struct quadra {
    char id[MAX];
    double x,y,w,h,cq;
    char cfill[MAX],cstrk[MAX];
} *pQuadra;


Quadra addQuadra(char comandos[500],double cq,char cfill[MAX],char cstrk[MAX]) {
    char id[MAX];
    double x=0,y=0,w=0,h=0;
    struct quadra *temp = (struct quadra*)calloc(1,sizeof(struct quadra));
    
    sscanf(comandos,"q %s %lf %lf %lf %lf",id,&x,&y,&w,&h);

    strcpy(temp->id,id);
    temp->x = x;
    temp->y = y;
    temp->w = w;
    temp->h = h;
    temp->cq = cq;
    strcpy(temp->cfill,cfill);
    strcpy(temp->cstrk,cstrk);

    return (void*)temp;
}

char *getQuadraId(Quadra recebeQuadra) {
    struct quadra *temp = (struct quadra*) recebeQuadra;
    return temp->id;
}

double getQuadraX(Quadra recebeQuadra) {
    struct quadra *temp = (struct quadra*) recebeQuadra;
    return temp->x;
}

double getQuadraY(Quadra recebeQuadra) {
    struct quadra *temp = (struct quadra*) recebeQuadra;
    return temp->y;
}

double getQuadraLargura(Quadra recebeQuadra) {
    struct quadra *temp = (struct quadra*) recebeQuadra;
    return temp->w;
}

double getQuadraAltura(Quadra recebeQuadra) {
    struct quadra *temp = (struct quadra*) recebeQuadra;
    return temp->h;
}

char *getQuadraCfill(Quadra recebeQuadra) {
    struct quadra *temp = (struct quadra*) recebeQuadra;
    return temp->cfill;
}

char *getQuadraCstrk(Quadra recebeQuadra) {
    struct quadra *temp = (struct quadra*) recebeQuadra;
    return temp->cstrk;
}

double getQuadraCq(Quadra recebeQuadra) {
    struct quadra *temp = (struct quadra*) recebeQuadra;
    return temp->cq;
}

void setQuadraX(Quadra recebeQuadra,double nX) {
    struct quadra *temp = (struct quadra*) recebeQuadra;
    temp->x = nX;
}

void setQuadraY(Quadra recebeQuadra,double nY) {
    struct quadra *temp = (struct quadra*) recebeQuadra;
    temp->y = nY;
}

void setQuadracfill(Quadra recebeQuadra,char cfill[MAX]) {
    struct quadra *temp = (struct quadra*) recebeQuadra;
    strcpy(temp->cfill,cfill);
}

void setQuadracstrk(Quadra recebeQuadra,char cfill[MAX]) {
    struct quadra *temp = (struct quadra*) recebeQuadra;
    strcpy(temp->cfill,cfill);
}

void removeQuadra(Quadra recebeQuadra) {
    struct quadra *temp = (struct quadra*) recebeQuadra;
    free(temp);
}

void printValorQuadra(Quadra recebeQuadra) {
    struct quadra *temp = (struct quadra*) recebeQuadra;
    printf("id: %s | x: %lf | y: %lf\n",temp->id,temp->x,temp->y);
}

int comparaQuadra(Quadra recebeQuadra1,Quadra recebeQuadra2) {
    struct quadra *temp1 = (struct quadra*) recebeQuadra1;
    struct quadra *temp2 = (struct quadra*) recebeQuadra2;

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

int comparaIdQuadra(Quadra recebeQuadra1,Quadra recebeQuadra2) {
    struct quadra *temp1 = (struct quadra*) recebeQuadra1;
    struct quadra *temp2 = (struct quadra*) recebeQuadra2;

    if(strcmp(temp1->id,temp2->id)) {
        return 1;
    } else if(strcmp(temp1->id,temp2->id) < 0) {
        return -1;
    } 
    return 0;
}