#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "radio.h"


typedef struct radio {
    char id[MAX];
    double x,y,cr;
    char cfill[MAX],cstrk[MAX];
} *pRadio;


Radio addRadio(char comandos[500],double cr,char cfill[30],char cstrk[30]) {
    char id[MAX];
    double x=0,y=0;
    struct radio *temp = (struct radio*)calloc(1,sizeof(struct radio));
    
    sscanf(comandos,"rb %s %lf %lf",id,&x,&y);

    strcpy(temp->id,id);
    temp->x = x;
    temp->y = y;
    temp->cr = cr;
    strcpy(temp->cfill,cfill);
    strcpy(temp->cstrk,cstrk);
    
    return (void*)temp;
}

char *getRadioId(Radio recebeRadio) {
    struct radio *temp = (struct radio*) recebeRadio;
    return temp->id;
}

double getRadioX(Radio recebeRadio) {
    struct radio *temp = (struct radio*) recebeRadio;
    return temp->x;
}

double getRadioY(Radio recebeRadio) {
    struct radio *temp = (struct radio*) recebeRadio;
    return temp->y;
}

char *getRadioCfill(Radio recebeRadio) {
    struct radio *temp = (struct radio*) recebeRadio;
    return temp->cfill;
}

char *getRadioCstrk(Radio recebeRadio) {
    struct radio *temp = (struct radio*) recebeRadio;
    return temp->cstrk;
}

double getRadioCr(Radio recebeRadio) {
    struct radio *temp = (struct radio*) recebeRadio;
    return temp->cr;
}

void setRadioX(Radio recebeRadio,double nX) {
    struct radio *temp = (struct radio*) recebeRadio;
    temp->x = nX;
}

void setRadioY(Radio recebeRadio,double nY) {
    struct radio *temp = (struct radio*) recebeRadio;
    temp->y = nY;
}

void removeRadio(Radio recebeRadio) {
    struct radio *temp = (struct radio*) recebeRadio;
    free(temp);
}

void printValorRadio(Radio recebeRadio) {
    struct radio *temp = (struct radio*) recebeRadio;
    printf("id: %s | x: %lf | y: %lf\n",temp->id,temp->x,temp->y);
}

int comparaRadio(Radio recebeRadio1,Radio recebeRadio2) {
    struct radio *temp1 = (struct radio*) recebeRadio1;
    struct radio *temp2 = (struct radio*) recebeRadio2;

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

int comparaIdRadio(Radio recebeRadio1,Radio recebeRadio2) {
    struct radio *temp1 = (struct radio*) recebeRadio1;
    struct radio *temp2 = (struct radio*) recebeRadio2;

    if(strcmp(temp1->id,temp2->id)) {
        return 1;
    } else if(strcmp(temp1->id,temp2->id) < 0) {
        return -1;
    } 
    return 0;
}