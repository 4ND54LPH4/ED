#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "texto.h"


typedef struct texto {
    double x,y;
    char texto[500];
} *pTexto;


Texto addTexto(char comandos[500]) {
    double x=0,y=0;
    char texto[500];
    struct texto *temp = (struct texto*)malloc(sizeof(struct texto));

    sscanf(comandos,"t %lf %lf %[^\n]",&x,&y,texto);

    temp->x = x;
    temp->y = y;
    strcpy(temp->texto,texto);

    return (void*)temp;
}

double getTextoX(Texto recebeTexto) {
    struct texto *temp = (struct texto*) recebeTexto;
    return temp->x;
}

double getTextoY(Texto recebeTexto) {
    struct texto *temp = (struct texto*) recebeTexto;
    return temp->y;
}

char *getTextoTexto(Texto recebeTexto) {
    struct texto *temp = (struct texto*) recebeTexto;
    return temp->texto;
}

void removeTexto(Texto recebeTexto) {
    struct texto *temp = (struct texto*) recebeTexto;
    free(temp);
}

int comparaTexto(Texto recebeTexto1,Texto recebeTexto2) {
    struct texto *temp1 = (struct texto*) recebeTexto1;
    struct texto *temp2 = (struct texto*) recebeTexto2;

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
