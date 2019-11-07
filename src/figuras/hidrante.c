#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hidrante.h"


typedef struct hidrante {
    char id[MAX];
    double x,y,ch;
    char cfill[MAX],cstrk[MAX];
} *pHidrante;


Hidrante addHidrante(char comandos[500],double ch,char cfill[30],char cstrk[30]) {
    char id[MAX];
    double x=0,y=0;
    struct hidrante *temp = (struct hidrante*)calloc(1,sizeof(struct hidrante));

    sscanf(comandos,"h %s %lf %lf",id,&x,&y);

    strcpy(temp->id,id);
    temp->x = x;
    temp->y = y;
    temp->ch = ch;
    strcpy(temp->cfill,cfill);
    strcpy(temp->cstrk,cstrk);

    return (void*)temp;
}

char *getHidranteId(Hidrante recebeHidrante) {
    struct hidrante *temp = (struct hidrante*) recebeHidrante;
    return temp->id;
}

double getHidranteX(Hidrante recebeHidrante) {
    struct hidrante *temp = (struct hidrante*) recebeHidrante;
    return temp->x;
}

double getHidranteY(Hidrante recebeHidrante) {
    struct hidrante *temp = (struct hidrante*) recebeHidrante;
    return temp->y;
}

char *getHidranteCfill(Hidrante recebeHidrante) {
    struct hidrante *temp = (struct hidrante*) recebeHidrante;
    return temp->cfill;
}

char *getHidranteCstrk(Hidrante recebeHidrante) {
    struct hidrante *temp = (struct hidrante*) recebeHidrante;
    return temp->cstrk;
}

double getHidranteCh(Hidrante recebeHidrante) {
    struct hidrante *temp = (struct hidrante*) recebeHidrante;
    return temp->ch;
}

void setHidranteX(Hidrante recebeHidrante,double nX) {
    struct hidrante *temp = (struct hidrante*) recebeHidrante;
    temp->x = nX;
}

void setHidranteY(Hidrante recebeHidrante,double nY) {
    struct hidrante *temp = (struct hidrante*) recebeHidrante;
    temp->y = nY;
}

void removeHidrante(Hidrante recebeHidrante) {
    struct hidrante *temp = (struct hidrante*) recebeHidrante;
    free(temp);
}

char* printValorHidrante(Hidrante recebeHidrante, char *dados) {
    struct hidrante *temp = (struct hidrante*) recebeHidrante;

    sprintf(dados, "id: %s | x: %lf | y: %lf",temp->id,temp->x,temp->y);
    return dados;
}

int comparaHidrante(Hidrante recebeHidrante1,Hidrante recebeHidrante2) {
    struct hidrante *temp1 = (struct hidrante*) recebeHidrante1;
    struct hidrante *temp2 = (struct hidrante*) recebeHidrante2;

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

int comparaIdHidrante(Hidrante recebeHidrante1,Hidrante recebeHidrante2) {
    struct hidrante *temp1 = (struct hidrante*) recebeHidrante1;
    struct hidrante *temp2 = (struct hidrante*) recebeHidrante2;

    if(strcmp(temp1->id,temp2->id)) {
        return 1;
    } else if(strcmp(temp1->id,temp2->id) < 0) {
        return -1;
    }
    return 0;
}

int comparaKeyHidrante(Hidrante recebeHidrante, char* key) {
    struct hidrante *temp = (struct hidrante*) recebeHidrante;

    return strcmp(temp->id, key);
}
