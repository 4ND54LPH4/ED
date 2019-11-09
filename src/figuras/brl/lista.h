#ifndef ___LISTA_H
#define ___LISTA_H

typedef void* Lista;

typedef void* Elem;

// Cria uma instancia de lista
Lista criaLista(int qtd);
// Retorna tamanho da lista
int length(Lista L);
// Insere um novo item na lista
Lista insert(Lista L,Elem e);
// Insercao depois de um elemento
Lista insertAfter(Lista L,Elem e,int pos);
// Insercao antes de um elemento
Lista insertBefore(Lista L,Elem e,int pos);
// Retorna o elemento na posicao pos
Elem get(Lista L,int pos);
// Retorna a primeira posicao da lista
int getFirst(Lista L);
// Retorna o proximo elemento dada uma posicao
int getNext(Lista L,int posicao);
// Retorna o elemento anterior de uma posicao dada
int getPrevious(Lista L,int posicao);
// Retorna o ultimo elemento de uma lista
int getLast(Lista L);
// Remove um elemento da lista dada uma posicao
int remover(Lista L, int pos);
// Remove um elemento da lista dado um elemento e
int removeElem(Lista L, Elem e);
/* Desaloca todos os elementos da lista e tambem sua propria "instancia" */
void desalocarlista(Lista L);

#endif
