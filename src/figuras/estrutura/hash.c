#include "hash.h"
#include "rbtree.h"

#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <math.h>

int vet[10000];

typedef struct list {
	struct node* objetoHash;
	struct list* prox;
} *pList;

typedef struct TabelaHash {
	pList *hash;
	int tam;
    int (*cmpHash)(void* objeto, char* chave);
    char* (*getChaveHash)(void* objeto);
} *pTabelaHash;

int calcularPrimo(int v) {
	int n = 2;
	int numPrimo = 2;
	int index = 0;
	while (n <= v) {
		int divisores = 0;
		for(int i = 1; i <= sqrt(n); i++) {
			if (n%i==0) divisores++;
		}
		if (divisores != 1) n++;
		else {
			vet[index++] = n;
			numPrimo = n;
			n++;
		}
	}
	return numPrimo;
}

tabelaHash criarTabelaHash(int tam, int(*cmpHash)(void* objeto, char* chave), char* (*getChaveHash)(void* objeto)) {
    pTabelaHash tabelaHash = malloc(sizeof(struct TabelaHash));

	tabelaHash->hash = malloc(tam*sizeof(struct list));
	tabelaHash->tam = calcularPrimo(tam);
    tabelaHash->cmpHash = cmpHash;
    tabelaHash->getChaveHash = getChaveHash;

    for(int i = 0; i < tam; i++) {
        tabelaHash->hash[i] = NULL;
    }

	return tabelaHash;
}

int hash(tabelaHash t, char *key) {
    pTabelaHash tabelaHash = (pTabelaHash) t;
    unsigned int hash = 0, i = 0;

    while(key && key[i]) {
        hash = (hash + key[i]) % tabelaHash->tam;
        i++;
    }

    return(hash);
}

void inserirHash(tabelaHash t, struct node* objeto) {
    pTabelaHash tabelaHash = (pTabelaHash) t;
    pList novo = malloc(sizeof(struct list));
	novo->objetoHash = objeto;
	novo->prox = NULL;

    int key = hash(t, tabelaHash->getChaveHash(objeto));

    if (tabelaHash->hash[key] == NULL) {
		tabelaHash->hash[key] = novo;
	} else {
		pList aux = tabelaHash->hash[key];
		while(1) {
			if(aux->prox == NULL) {
				aux->prox = novo;
				break;
			}
			aux = aux->prox;
		}
	}
}

struct node* getObjetoHash(tabelaHash t, char* key) {
    pTabelaHash tabelaHash = (pTabelaHash) t;
    int i = hash(t, key);
    pList n = tabelaHash->hash[i];

    /*if(tabelaHash == NULL) return NULL;
    while(n != NULL) {
        if (tabelaHash->cmpHash(n->objeto, key) == 0) {
            break;
        }
        n = n->prox;
    }
    if (n == NULL) return NULL;
    return n->objeto;*/

	if (n == NULL) return NULL;

	if(n->prox == NULL && tabelaHash->cmpHash(n->objetoHash, key) == 0) {
		//tabelaHash->destruirObjeto(objeto);
	 	return n->objetoHash;
	} else {
	 	pList aux = n;
		while(aux != NULL) {
			if(tabelaHash->cmpHash(aux->objetoHash, key) == 0) {
				//tabelaHash->destruirObjeto(objeto);
				return aux->objetoHash;
			}
	 		aux = aux->prox;
		}
	}
	//tabelaHash->destruirObjeto(objeto);
	return NULL;
}

void removerObjetoHash(tabelaHash t, char* key) {
    pTabelaHash tabelaHash = (pTabelaHash) t;
    int i = hash(t, key);
	pList n = tabelaHash->hash[i];
	if(n->prox == NULL  && tabelaHash->cmpHash(n->objetoHash, key) == 0) {
        //free(n); //apagar
		tabelaHash->hash[i] = NULL;
		free(n);
	} else {
		pList aux = n;

		while(aux != NULL) {
			n = n->prox;
			if(tabelaHash->cmpHash(aux->objetoHash, key) == 0) {
				//free(aux);
				aux = NULL;
			}
			aux = n;
			/*
				//aux = NULL;
				aux = NULL;
				break;
			}*/

		}
		//tabelaHash->hash[i] = NULL;
		free(n);
        //free(aux); //apagar
	}
}

void destruir(pList inicio) {
	pList aux = (pList) inicio;

	while (aux != NULL) {
		inicio = inicio->prox;
		free(aux);
		aux = inicio;
	}
}

void destruirTabelaHash(tabelaHash t) {
    pTabelaHash tabelaHash = (pTabelaHash) t;
	for(int i = 0; i < tabelaHash->tam; i++) {
		pList n = tabelaHash->hash[i];
		if(n != NULL) {
			destruir(n);
		}
	}
	free(tabelaHash->hash);
	free(tabelaHash);
}

// Função teste - Elementos com nome igual fica no mesmo indice do vetor
void printTabela(tabelaHash t, char *key) {
	pTabelaHash tabelaHash = (pTabelaHash) t;
	int c = 0;
	for (int i = 0; i < tabelaHash->tam; i++) {
		pList n = tabelaHash->hash[i];
		if (n != NULL) {
			pList aux = n;
			while (aux != NULL) {
				n = n->prox;
				//if(tabelaHash->cmpHash(aux->objetoHash, key) == 0) {
					printf("c : %d\n", c);
					printf("i: %d\n", i);
					c++;
				//}
				aux = n;
			}
		}
	}
}

int getTamHash(tabelaHash t) {
	pTabelaHash tabelaHash = (pTabelaHash) t;
	return tabelaHash->tam;
}

listaHash getIndiceHash(tabelaHash t, int i) {
	pTabelaHash tabelaHash = (pTabelaHash) t;

	if (tabelaHash->hash[i] != NULL) {
		return tabelaHash->hash[i];
	} else {
		return NULL;
	}
}

listaHash getProxHash(listaHash n) {
	pList node = (pList) n;

	if (node->prox != NULL) {
		return node->prox;
	} else {
		return NULL;
	}
}

struct node* getObjetoHash2(listaHash n) {
	pList node = (pList) n;
	return node->objetoHash;
}
