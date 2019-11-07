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
    struct texto *temp = (struct texto*)calloc(1,sizeof(struct texto));
    
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
