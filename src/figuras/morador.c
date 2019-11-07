#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "morador.h"
#include "pessoa.h"

typedef struct morador {
    char cpf[15], cep[MAX], face, compl[MAX];
    int num;
    tabelaHash* hashPessoa;
} *pMorador;

Morador addMorador(char comandos[500], tabelaHash hashPessoa) {
    char cpf[15], cep[MAX], face, compl[MAX];
    int num = 0;
    struct morador *temp = (struct morador*)malloc(sizeof(struct morador));

    sscanf(comandos, "m %s %s %c %d %s", cpf, cep, &face, &num, compl);

    strcpy(temp->cpf, cpf);
    strcpy(temp->cep, cep);
    temp->face = face;
    temp->num = num;
    strcpy(temp->compl, compl);
    temp->hashPessoa = hashPessoa;

    return (void*)temp;
}

char *getMoradorCpf(Morador recebeMorador) {
    struct morador *temp = (struct morador*) recebeMorador;
    return temp->cpf;
}

char *getMoradorCep(Morador recebeMorador) {
    struct morador *temp = (struct morador*) recebeMorador;
    return temp->cep;
}

char getMoradorFace(Morador recebeMorador) {
    struct morador *temp = (struct morador*) recebeMorador;
    return temp->face;
}

int getMoradorNum(Morador recebeMorador) {
    struct morador *temp = (struct morador*) recebeMorador;
    return temp->num;
}

char *getMoradorCompl(Morador recebeMorador) {
    struct morador *temp = (struct morador*) recebeMorador;
    return temp->compl;
}

char *getMoradorNome(Morador recebeMorador) {
    struct morador *temp = (struct morador*) recebeMorador;
    Pessoa pessoa = getObjetoHash(temp->hashPessoa, temp->cpf);
    return getPessoaNome(pessoa);
}

char *getMoradorSobrenome(Morador recebeMorador) {
    struct morador *temp = (struct morador*) recebeMorador;
    Pessoa pessoa = getObjetoHash(temp->hashPessoa, temp->cpf);
    return getPessoaSobrenome(pessoa);
}

char getMoradorSexo(Morador recebeMorador) {
    struct morador *temp = (struct morador*) recebeMorador;
    Pessoa pessoa = getObjetoHash(temp->hashPessoa, temp->cpf);
    return getPessoaSexo(pessoa);
}

char *getMoradorNascimento(Morador recebeMorador) {
    struct morador *temp = (struct morador*) recebeMorador;
    Pessoa pessoa = getObjetoHash(temp->hashPessoa, temp->cpf);
    return getPessoaNascimento(pessoa);
}

void setMoradorCep(Morador recebeMorador, char* pCep) {
    struct morador *temp = (struct morador*) recebeMorador;
    strcpy(temp->cep, pCep);
}

void setMoradorFace(Morador recebeMorador, char pFace) {
    struct morador *temp = (struct morador*) recebeMorador;
    temp->face = pFace;
}

void setMoradorNum(Morador recebeMorador, int pNum) {
    struct morador *temp = (struct morador*) recebeMorador;
    temp->num = pNum;
}

void setMoradorCompl(Morador recebeMorador, char* pCompl) {
    struct morador *temp = (struct morador*) recebeMorador;
    strcpy(temp->compl, pCompl);
}

void removeMorador(Morador recebeMorador) {
    struct morador *temp = (struct morador*) recebeMorador;
    free(temp);
}

int comparaMorador(Morador recebeMorador1, Morador recebeMorador2) {
    struct morador *temp1 = (struct morador*) recebeMorador1;
    struct morador *temp2 = (struct morador*) recebeMorador2;

    return strcmp(temp1->cpf, temp2->cpf);
}

int comparaKeyMorador(Morador recebeMorador, char* key) {
    struct morador *temp = (struct morador*) recebeMorador;

    return strcmp(temp->cpf, key);
}
