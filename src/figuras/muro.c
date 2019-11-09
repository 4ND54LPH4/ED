#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "muro.h"


typedef struct muro {
    char id[50];
    float x1,x2,y1,y2;
} *pMuro;


Muro addMuro(char comandos[500],char* pId) {
    float x1,y1,x2,y2;
    struct muro *temp = (struct muro*)malloc(sizeof(struct muro));

    sscanf(comandos,"mur %f %f %f %f",&x1,&y1,&x2,&y2);

    strcpy(temp->id, pId);
    temp->x1 = x1;
    temp->y1 = y1;
    temp->x2 = x2;
    temp->y2 = y2;

    return (void*)temp;
}

char* getMuroId(Muro recebeMuro) {
    struct muro *temp = (struct muro*) recebeMuro;
    return temp->id;
}

float getMuroX1(Muro recebeMuro) {
    struct muro *temp = (struct muro*) recebeMuro;
    return temp->x1;
}

float getMuroY1(Muro recebeMuro) {
    struct muro *temp = (struct muro*) recebeMuro;
    return temp->y1;
}

float getMuroX2(Muro recebeMuro) {
    struct muro *temp = (struct muro*) recebeMuro;
    return temp->x2;
}

float getMuroY2(Muro recebeMuro) {
    struct muro *temp = (struct muro*) recebeMuro;
    return temp->y2;
}

void removeMuro(Muro recebeMuro) {
    struct muro *temp = (struct muro*) recebeMuro;
    free(temp);
}

char* printValorMuro(Muro recebeMuro, char *dados) {
    struct muro *temp = (struct muro*) recebeMuro;

    sprintf(dados, "id: %s | x1: %lf | y1: %lf | x2: %lf | y2: %lf\n",temp->id, temp->x1,temp->y1, temp->x2, temp->y2);
    return dados;
}

int comparaMuro(Muro recebeMuro1,Muro recebeMuro2) {
    struct muro *temp1 = (struct muro*) recebeMuro1;
    struct muro *temp2 = (struct muro*) recebeMuro2;

    if(temp1->x1 > temp2->x1) {
        return 1;
    } else if(temp1->x1 < temp2->x1) {
        return -1;
    } else if(temp1->y1 > temp2->y1) {
        return 1;
    } else if(temp1->y1 < temp2->y1) {
        return -1;
    } else if(temp1->x2 > temp2->x2) {
        return 1;
    } else if(temp1->x2 < temp2->x2) {
        return -1;
    } else if(temp1->y2 > temp2->y2) {
        return 1;
    } else if(temp1->y2 < temp2->y2) {
        return -1;
    }
    return 0;
}

int comparaKeyMuro(Muro recebeMuro,char *key) {
    struct muro *temp = (struct muro*) recebeMuro;

    return strcmp(temp->id, key);
}
