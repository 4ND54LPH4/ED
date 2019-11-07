#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "muro.h"


typedef struct muro {
    int id;
    double x1,x2,y1,y2;
} *pMuro;


Muro addMuro(char comandos[500],int pId) {
    double x1,y1,x2,y2;
    struct muro *temp = (struct muro*)malloc(sizeof(struct muro));
    
    sscanf(comandos,"mur %lf %lf %lf %lf",&x1,&y1,&x2,&y2);

    temp->id = pId;
    temp->x1 = x1;
    temp->y1 = y1;
    temp->x2 = x2;
    temp->y2 = y2;

    return (void*)temp;
}

int getMuroId(Muro recebeMuro) {
    struct muro *temp = (struct muro*) recebeMuro;
    return temp->id;
}

double getMuroX1(Muro recebeMuro) {
    struct muro *temp = (struct muro*) recebeMuro;
    return temp->x1;
}

double getMuroY1(Muro recebeMuro) {
    struct muro *temp = (struct muro*) recebeMuro;
    return temp->y1;
}

double getMuroX2(Muro recebeMuro) {
    struct muro *temp = (struct muro*) recebeMuro;
    return temp->x2;
}

double getMuroY2(Muro recebeMuro) {
    struct muro *temp = (struct muro*) recebeMuro;
    return temp->y2;
}

void removeMuro(Muro recebeMuro) {
    struct muro *temp = (struct muro*) recebeMuro;
    free(temp);
}
