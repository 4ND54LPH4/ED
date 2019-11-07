#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "semaforo.h"


typedef struct semaforo {
    char id[MAX];
    double x,y,cs;
    char cfill[MAX],cstrk[MAX];
} *pSemaforo;


Semaforo addSemaforo(char comandos[500],double cs,char cfill[30],char cstrk[30]) {
    char id[MAX];
    double x=0,y=0;
    struct semaforo *temp = (struct semaforo*)calloc(1,sizeof(struct semaforo));

    sscanf(comandos,"s %s %lf %lf",id,&x,&y);

    strcpy(temp->id,id);
    temp->x = x;
    temp->y = y;
    temp->cs = cs;
    strcpy(temp->cfill,cfill);
    strcpy(temp->cstrk,cstrk);

    return (void*)temp;
}

char *getSemaforoId(Semaforo recebeSemaforo) {
    struct semaforo *temp = (struct semaforo*) recebeSemaforo;
    return temp->id;
}

double getSemaforoX(Semaforo recebeSemaforo) {
    struct semaforo *temp = (struct semaforo*) recebeSemaforo;
    return temp->x;
}

double getSemaforoY(Semaforo recebeSemaforo) {
    struct semaforo *temp = (struct semaforo*) recebeSemaforo;
    return temp->y;
}

char *getSemaforoCfill(Semaforo recebeSemaforo) {
    struct semaforo *temp = (struct semaforo*) recebeSemaforo;
    return temp->cfill;
}

char *getSemaforoCstrk(Semaforo recebeSemaforo) {
    struct semaforo *temp = (struct semaforo*) recebeSemaforo;
    return temp->cstrk;
}

double getSemaforoCs(Semaforo recebeSemaforo) {
    struct semaforo *temp = (struct semaforo*) recebeSemaforo;
    return temp->cs;
}

void setSemaforoX(Semaforo recebeSemaforo,double nX) {
    struct semaforo *temp = (struct semaforo*) recebeSemaforo;
    temp->x = nX;
}

void setSemaforoY(Semaforo recebeSemaforo,double nY) {
    struct semaforo *temp = (struct semaforo*) recebeSemaforo;
    temp->y = nY;
}

void removeSemaforo(Semaforo recebeSemaforo) {
    struct semaforo *temp = (struct semaforo*) recebeSemaforo;
    free(temp);
}

char* printValorSemaforo(Semaforo recebeSemaforo, char *dados) {
    struct semaforo *temp = (struct semaforo*) recebeSemaforo;

    sprintf(dados, "id: %s | x: %lf | y: %lf\n",temp->id,temp->x,temp->y);
    return dados;
}

int comparaSemaforo(Semaforo recebeSemaforo1,Semaforo recebeSemaforo2) {
    struct semaforo *temp1 = (struct semaforo*) recebeSemaforo1;
    struct semaforo *temp2 = (struct semaforo*) recebeSemaforo2;

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

int comparaIdSemaforo(Semaforo recebeSemaforo1,Semaforo recebeSemaforo2) {
    struct semaforo *temp1 = (struct semaforo*) recebeSemaforo1;
    struct semaforo *temp2 = (struct semaforo*) recebeSemaforo2;

    if(strcmp(temp1->id,temp2->id)) {
        return 1;
    } else if(strcmp(temp1->id,temp2->id) < 0) {
        return -1;
    }
    return 0;
}

int comparaKeySemaforo(Semaforo recebeSemaforo, char* key) {
    struct semaforo *temp = (struct semaforo*) recebeSemaforo;

    return strcmp(temp->id, key);
}
