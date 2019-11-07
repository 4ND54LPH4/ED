#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "predio.h"
#include "quadra.h"

typedef struct predio {
    char id[MAX], face;
    int num;
    double f, p, mrg;
    tabelaHash* hashQuadra;
} *pPredio;

Predio addPredio(char comandos[500], tabelaHash hashQuadra) {
    char id[MAX], face;
    int num = 0;
    double f = 0, p = 0, mrg = 0;
    struct predio *temp = (struct predio*)malloc(sizeof(struct predio));

    sscanf(comandos, "prd %s %c %d %lf %lf %lf", id, &face, &num, &f, &p, &mrg);

    strcpy(temp->id, id);
    temp->face = face;
    temp->num = num;
    temp->f = f;
    temp->p = p;
    temp->mrg = mrg;
    temp->hashQuadra = hashQuadra;

    return (void*)temp;
}

char *getPredioId(Predio recebePredio) {
    struct predio *temp = (struct predio*) recebePredio;
    return temp->id;
}

char getPredioFace(Predio recebePredio) {
    struct predio *temp = (struct predio*) recebePredio;
    return temp->face;
}

int getPredioNum(Predio recebePredio) {
    struct predio *temp = (struct predio*) recebePredio;
    return temp->num;
}

double getPredioF(Predio recebePredio) {
    struct predio *temp = (struct predio*) recebePredio;
    return temp->f;
}

double getPredioP(Predio recebePredio) {
    struct predio *temp = (struct predio*) recebePredio;
    return temp->p;
}

double getPredioMrg(Predio recebePredio) {
    struct predio *temp = (struct predio*) recebePredio;
    return temp->mrg;
}

double getPredioX(Predio recebePredio) {
    struct predio *temp = (struct predio*) recebePredio;
    Quadra quadra = getObjetoHash(temp->hashQuadra, temp->id);

    if (temp->face == 'N') {
        return getQuadraX(quadra) + temp->num - (temp->f/2);
    } else if (temp->face == 'S') {
        return getQuadraX(quadra) + temp->num - (temp->f/2);
    } else if (temp->face == 'L') {
        return getQuadraX(quadra) + temp->mrg;
    } else if (temp->face == 'O') {
        return getQuadraX(quadra) + getQuadraLargura(quadra) - temp->mrg - temp->p;
    }
}

double getPredioY(Predio recebePredio) {
    struct predio *temp = (struct predio*) recebePredio;
    Quadra quadra = getObjetoHash(temp->hashQuadra, temp->id);

    if (temp->face == 'N') {
        return getQuadraY(quadra) + getQuadraAltura(quadra) - temp->mrg - temp->p;
    } else if (temp->face == 'S') {
        return getQuadraY(quadra) + temp->mrg;
    } else if (temp->face == 'L') {
        return getQuadraY(quadra) + temp->num - (temp->f/2);
    } else if (temp->face == 'O') {
        return getQuadraY(quadra) + temp->num - (temp->f/2);
    }
}

double getPredioTexX(Predio recebePredio) {
    struct predio *temp = (struct predio*) recebePredio;
    Quadra quadra = getObjetoHash(temp->hashQuadra, temp->id);

    if (temp->face == 'N' || temp->face == 'S') {
        return getPredioX(recebePredio) + (temp->f/2);
    } else if (temp->face == 'L') {
        return getPredioX(recebePredio) + 4;
    } else if (temp->face == 'O') {
        return getPredioX(recebePredio) + temp->p - 4;
    }
}

double getPredioTexY(Predio recebePredio) {
    struct predio *temp = (struct predio*) recebePredio;
    Quadra quadra = getObjetoHash(temp->hashQuadra, temp->id);

    if (temp->face == 'N') {
        return getPredioY(recebePredio) + temp->p -2;
    } else if (temp->face == 'S') {
        return getPredioY(recebePredio) + 9;
    } else if (temp->face == 'L' || temp->face == 'O') {
        return getPredioY(recebePredio) + (temp->f/2) + 4;
    }
}

double getPredioAltura(Predio recebePredio) {
    struct predio *temp = (struct predio*) recebePredio;

    if (temp->face == 'N' || temp->face == 'S') {
        return temp->p;
    } else if (temp->face == 'L' || temp->face == 'O') {
        return temp->f;
    }
}

double getPredioLargura(Predio recebePredio) {
    struct predio *temp = (struct predio*) recebePredio;

    if (temp->face == 'N' || temp->face == 'S') {
        return temp->f;
    } else if (temp->face == 'L' || temp->face == 'O') {
        return temp->p;
    }
}

void removePredio(Predio recebePredio) {
    struct predio *temp = (struct predio*) recebePredio;
    free(temp);
}

char* printValorPredio(Predio recebePredio, char *dados) {
    struct predio *temp = (struct predio*) recebePredio;

    sprintf(dados, "cep: %s | x: %lf | y: %lf\n",temp->id, getPredioX(recebePredio), getPredioY(recebePredio));
    return dados;
}

int comparaPredio(Predio recebePredio1, Predio recebePredio2) {
    struct predio *temp1 = (struct predio*) recebePredio1;
    struct predio *temp2 = (struct predio*) recebePredio2;

    if (getPredioX(temp1) > getPredioX(temp2)) {
        return 1;
    } else if(getPredioX(temp1) < getPredioX(temp2)) {
        return -1;
    } else if(getPredioY(temp1) > getPredioY(temp2)) {
        return 1;
    } else if(getPredioY(temp1) < getPredioY(temp2)) {
        return -1;
    }
    return 0;
}

int comparaIdPredio(Predio recebePredio1, Predio recebePredio2) {
    struct predio *temp1 = (struct predio*) recebePredio1;
    struct predio *temp2 = (struct predio*) recebePredio2;

    if(strcmp(temp1->id,temp2->id)) {
        return 1;
    } else if(strcmp(temp1->id,temp2->id) < 0) {
        return -1;
    }
    return 0;
}

int comparaKeyPredio(Predio recebePredio, char *key) {
    struct predio *temp = (struct predio*) recebePredio;

    return strcmp(temp->id, key);
}
