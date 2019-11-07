#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pessoa.h"

typedef struct pessoa {
    char cpf[15], nome[MAX], sobrenome[MAX], sexo, nascimento[11];
} *pPessoa;

Pessoa addPessoa(char comandos[500]) {
    char cpf[15], nome[MAX], sobrenome[MAX], sexo, nascimento[11];
    struct pessoa *temp = (struct pessoa*)calloc(1, sizeof(struct pessoa));

    sscanf(comandos, "p %s %s %s %c %s", cpf, nome, sobrenome, &sexo, nascimento);

    strcpy(temp->cpf, cpf);
    strcpy(temp->nome, nome);
    strcpy(temp->sobrenome, sobrenome);
    temp->sexo = sexo;
    strcpy(temp->nascimento, nascimento);

    return (void*)temp;
}

char *getPessoaCpf(Pessoa recebePessoa) {
    struct pessoa *temp = (struct pessoa*) recebePessoa;
    return temp->cpf;
}

char *getPessoaNome(Pessoa recebePessoa) {
    struct pessoa *temp = (struct pessoa*) recebePessoa;
    return temp->nome;
}

char *getPessoaSobrenome(Pessoa recebePessoa) {
    struct pessoa *temp = (struct pessoa*) recebePessoa;
    return temp->sobrenome;
}

char getPessoaSexo(Pessoa recebePessoa) {
    struct pessoa *temp = (struct pessoa*) recebePessoa;
    return temp->sexo;
}

char *getPessoaNascimento(Pessoa recebePessoa) {
    struct pessoa *temp = (struct pessoa*) recebePessoa;
    return temp->nascimento;
}

void removePessoa(Pessoa recebePessoa) {
    struct pessoa *temp = (struct pessoa*) recebePessoa;
    free(temp);
}

int comparaPessoa(Pessoa recebePessoa1, Pessoa recebePessoa2) {
    struct pessoa *temp1 = (struct pessoa*) recebePessoa1;
    struct pessoa *temp2 = (struct pessoa*) recebePessoa2;

    return strcmp(temp1->cpf, temp2->cpf);
}

int comparaKeyPessoa(Pessoa recebePessoa, char* key) {
    struct pessoa *temp = (struct pessoa*) recebePessoa;

    return strcmp(temp->cpf, key);
}
