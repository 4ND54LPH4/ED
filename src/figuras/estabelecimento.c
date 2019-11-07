#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "estabelecimento.h"
#include "pessoa.h"
#include "tipoEstabelecimento.h"

typedef struct estabelecimento {
    char cnpj[19], cpf[15], codt[10], cep[MAX], face, nome[MAX];
    int num;
    tabelaHash* hashPessoa, hashTipo;
} *pEstabelecimento;

Estabelecimento addEstabelecimento(char comandos[500], tabelaHash hashPessoa, tabelaHash hashTipo) {
    char cnpj[19], cpf[15], codt[10], cep[MAX], face, nome[MAX];
    int num;
    struct estabelecimento *temp = (struct estabelecimento*)malloc(sizeof(struct estabelecimento));

    sscanf(comandos, "e %s %s %s %s %c %d %s", cnpj, cpf, codt, cep, &face, &num, nome);

    strcpy(temp->cnpj, cnpj);
    strcpy(temp->cpf, cpf);
    strcpy(temp->codt, codt);
    strcpy(temp->cep, cep);
    temp->face = face;
    temp->num = num;
    strcpy(temp->nome, nome);
    temp->hashPessoa = hashPessoa;
    temp->hashTipo = hashTipo;

    return (void*)temp;
}

char *getEstabelecimentoCnpj(Estabelecimento recebeEstabelecimento) {
    struct estabelecimento *temp = (struct estabelecimento*) recebeEstabelecimento;
    return temp->cnpj;
}

char *getEstabelecimentoCpf(Estabelecimento recebeEstabelecimento) {
    struct estabelecimento *temp = (struct estabelecimento*) recebeEstabelecimento;
    return temp->cpf;
}

char *getEstabelecimentoCodt(Estabelecimento recebeEstabelecimento) {
    struct estabelecimento *temp = (struct estabelecimento*) recebeEstabelecimento;
    return temp->codt;
}

char *getEstabelecimentoCep(Estabelecimento recebeEstabelecimento) {
    struct estabelecimento *temp = (struct estabelecimento*) recebeEstabelecimento;
    return temp->cep;
}

char getEstabelecimentoFace(Estabelecimento recebeEstabelecimento) {
    struct estabelecimento *temp = (struct estabelecimento*) recebeEstabelecimento;
    return temp->face;
}

int getEstabelecimentoNum(Estabelecimento recebeEstabelecimento) {
    struct estabelecimento *temp = (struct estabelecimento*) recebeEstabelecimento;
    return temp->num;
}

char *getEstabelecimentoNome(Estabelecimento recebeEstabelecimento) {
    struct estabelecimento *temp = (struct estabelecimento*) recebeEstabelecimento;
    return temp->nome;
}

char *getEstabelecimentoDescricao(Estabelecimento recebeEstabelecimento) {
    struct estabelecimento *temp = (struct estabelecimento*) recebeEstabelecimento;
    TipoEstabelecimento tipo = getObjetoHash(temp->hashTipo, temp->codt);
    return getTipoEstabelecimentoDescricao(tipo);
}

char *getEstabelecimentoProprietarioNome(Estabelecimento recebeEstabelecimento) {
    struct estabelecimento *temp = (struct estabelecimento*) recebeEstabelecimento;
    Pessoa pessoa = getObjetoHash(temp->hashPessoa, temp->cpf);
    return getPessoaNome(pessoa);
}

char *getEstabelecimentoProprietarioSobrenome(Estabelecimento recebeEstabelecimento) {
    struct estabelecimento *temp = (struct estabelecimento*) recebeEstabelecimento;
    Pessoa pessoa = getObjetoHash(temp->hashPessoa, temp->cpf);
    return getPessoaSobrenome(pessoa);
}

char getEstabelecimentoProprietarioSexo(Estabelecimento recebeEstabelecimento) {
    struct estabelecimento *temp = (struct estabelecimento*) recebeEstabelecimento;
    Pessoa pessoa = getObjetoHash(temp->hashPessoa, temp->cpf);
    return getPessoaSexo(pessoa);
}

char *getEstabelecimentoProprietarioNascimento(Estabelecimento recebeEstabelecimento) {
    struct estabelecimento *temp = (struct estabelecimento*) recebeEstabelecimento;
    Pessoa pessoa = getObjetoHash(temp->hashPessoa, temp->cpf);
    return getPessoaNascimento(pessoa);
}

void removeEstabelecimento(Estabelecimento recebeEstabelecimento) {
    struct estabelecimento *temp = (struct estabelecimento*) recebeEstabelecimento;
    free(temp);
}

int comparaEstabelecimento(Estabelecimento recebeEstabelecimento1, Estabelecimento recebeEstabelecimento2) {
    struct estabelecimento *temp1 = (struct estabelecimento*) recebeEstabelecimento1;
    struct estabelecimento *temp2 = (struct estabelecimento*) recebeEstabelecimento2;

    return strcmp(temp1->cnpj, temp2->cnpj);
}

int comparaKeyEstabelecimento(Estabelecimento recebeEstabelecimento, char* key) {
    struct estabelecimento *temp = (struct estabelecimento*) recebeEstabelecimento;

    return strcmp(temp->cnpj, key);
}
