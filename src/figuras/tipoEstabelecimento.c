#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tipoEstabelecimento.h"

typedef struct tipoEstabelecimento {
    char codt[10], descricao[MAX];
} *pTipoEstabelecimento;

TipoEstabelecimento addTipoEstabelecimento(char comandos[500]) {
    char codt[10], descricao[MAX];
    struct tipoEstabelecimento *temp = (struct tipoEstabelecimento*)malloc(sizeof(struct tipoEstabelecimento));

    sscanf(comandos, "t %s %s", codt, descricao);

    strcpy(temp->codt, codt);
    strcpy(temp->descricao, descricao);

    return (void*)temp;
}

char *getTipoEstabelecimentoCodt(TipoEstabelecimento recebeTipoEstabelecimento) {
    struct tipoEstabelecimento *temp = (struct tipoEstabelecimento*) recebeTipoEstabelecimento;
    return temp->codt;
}

char *getTipoEstabelecimentoDescricao(TipoEstabelecimento recebeTipoEstabelecimento) {
    struct tipoEstabelecimento *temp = (struct tipoEstabelecimento*) recebeTipoEstabelecimento;
    return temp->descricao;
}

void removeTipoEstabelecimento(TipoEstabelecimento recebeTipoEstabelecimento) {
    struct tipoEstabelecimento *temp = (struct tipoEstabelecimento*) recebeTipoEstabelecimento;
    free(temp);
}

int comparaTipoEstabelecimento(TipoEstabelecimento recebeTipoEstabelecimento1, TipoEstabelecimento recebeTipoEstabelecimento2) {
    struct tipoEstabelecimento *temp1 = (struct tipoEstabelecimento*) recebeTipoEstabelecimento1;
    struct tipoEstabelecimento *temp2 = (struct tipoEstabelecimento*) recebeTipoEstabelecimento2;

    return strcmp(temp1->codt, temp2->codt);
}

int comparaKeyTipoEstabelecimento(TipoEstabelecimento recebeTipoEstabelecimento, char* key) {
    struct tipoEstabelecimento *temp = (struct tipoEstabelecimento*) recebeTipoEstabelecimento;

    return strcmp(temp->codt, key);
}
