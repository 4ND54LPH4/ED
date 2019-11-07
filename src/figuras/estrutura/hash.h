#ifndef ___TABELAHASH_H_
#define ___TABELAHASH_H_

#include "rbtree.h"

typedef void* listaHash;
typedef void* tabelaHash;

int calcularPrimo(int v);
tabelaHash criarTabelaHash(int tam, int(*cmpHash)(void* objeto, char* chave), char* (*getChaveHash)(void* objeto));
int hash(tabelaHash t, char *key);
void inserirHash(tabelaHash t, struct node* objeto);
struct node* getObjetoHash(tabelaHash t, char* key);
void removerObjetoHash(tabelaHash t, char* key);
void destruirTabelaHash(tabelaHash t);
void printTabela(tabelaHash t, char *key);

int getTamHash(tabelaHash t);
listaHash getIndiceHash(tabelaHash t, int i);
listaHash getProxHash(listaHash n);
struct node* getObjetoHash2(listaHash n);

#endif
