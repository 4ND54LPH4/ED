#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"lista.h"

typedef struct{
    Elem elemento;
    int anterior;
    int proximo;
}ITEM;

typedef struct{
    ITEM* item;
    int prim;
    int livre;
    int ult;
    int size;
    int qItens;
}ListaImpl;

Lista criaLista(int tamanho){
    ListaImpl *new =malloc(sizeof(ListaImpl));
    new->item = malloc(sizeof(ITEM)*tamanho);
    new->prim=-1;
    new->ult=-1;
    new->livre=0;
    new->size=tamanho;
    new->qItens=0;
    for (int i = 0; i <tamanho-1; i++){
        new->item[i].proximo=i+1;
    }
    new->item[tamanho-1].proximo=-1;
    return new;
}

int getLivre(ListaImpl* Limp){
  int iLivre = Limp->livre;
  Limp->livre = Limp->item[Limp->livre].proximo;

  return iLivre;
}

int removeElem(Lista L,Elem e){
    ListaImpl *list =L;
    int pos=getFirst(L);
    while(pos!=-1){
        if(e==list->item[pos].elemento){
            break;
        }
        pos=getNext(L,pos);
    }
    int anterior=list->item[pos].anterior;
    int prox=list->item[pos].proximo;

    if(pos==list->prim){
        list->item[prox].anterior=-1;

        list->item[pos].proximo=list->livre;
        list->item[pos].anterior=0;

        list->prim=prox;

        list->livre=pos;
    }else if(pos==list->ult){

        list->item[anterior].proximo=-1;

        list->item[pos].anterior=0;
        list->item[pos].proximo=list->livre;

        list->ult=anterior;

        list->livre=pos;
    }else{

        list->item[anterior].proximo=prox;

        list->item[prox].anterior=anterior;

        list->item[pos].anterior=0;
        list->item[pos].proximo=list->livre;


        list->livre=pos;

    }
    list->qItens--;
    return 1;
}

void desalocarlista(Lista L){
    ListaImpl *list =L;
    int pos=getFirst(L);
    while(pos!=-1){
        free(list->item[pos].elemento);
        pos=getNext(L,pos);
    }
    free(list->item);
    free(list);
}

int remover(Lista L, int pos){
    ListaImpl *list = L;

    int anterior=list->item[pos].anterior;
    int prox=list->item[pos].proximo;

    if(pos==list->prim){
        list->item[prox].anterior=-1;

        list->item[pos].proximo=list->livre;
        list->item[pos].anterior=0;

        list->prim=prox;

        list->livre=pos;
    }else if(pos==list->ult){

        list->item[anterior].proximo=-1;

        list->item[pos].anterior=0;
        list->item[pos].proximo=list->livre;

        list->ult=anterior;

        list->livre=pos;
    }else{

        list->item[anterior].proximo=prox;

        list->item[prox].anterior=anterior;

        list->item[pos].anterior=0;
        list->item[pos].proximo=list->livre;


        list->livre=pos;

    }
    free(list->item[pos].elemento);
    list->qItens--;
    return 1;
}

int getFirst(Lista L){
    ListaImpl *list=L;
    return list->prim;
}

int getLast(Lista L){
    ListaImpl *list=L;
    return list->ult;
}

int getNext(Lista L,int posicao){
    ListaImpl *list=L;
    int i=posicao;
    if(posicao==-1){
        return -1;
    }else
        return list->item[i].proximo;
}

int getPrevious(Lista L,int posicao){
    ListaImpl *list=L;
    int i=posicao;
    return list->item[i].anterior;
}

Lista insert(Lista L,Elem e){
    ListaImpl *list = L;
    if(length(L)-1==list->qItens){
        return NULL;
    }else{
        int livre = getLivre(list);

        list->item[livre].elemento=e;

        list->item[livre].anterior=list->ult;
        list->item[livre].proximo=-1;


        if(list->prim!=-1){
            list->item[list->ult].proximo=livre;
        }else{
            list->prim=livre;
        }

        list->ult=livre;

        list->qItens++;

        return list;
    }
}

Lista insertAfter(Lista L,Elem e,int pos){
    ListaImpl *list = L;
    if(length(L)-1==list->qItens){
        return NULL;
    }else{
        int livre = getLivre(list);

        list->item[livre].elemento=e;

        list->item[livre].anterior=pos;
        list->item[livre].proximo=list->item[pos].proximo;

        list->item[list->item[pos].proximo].anterior=pos;

        list->item[pos].proximo=livre;


        list->qItens++;

        return list;
    }
}

Lista insertBefore(Lista L,Elem e,int pos){
    ListaImpl *list = L;
    if(length(L)-1==list->qItens){
        return NULL;
    }else{
        int livre = getLivre(list);

        list->item[livre].elemento=e;

        list->item[livre].anterior=list->item[pos].anterior;
        list->item[livre].proximo= pos;

        list->item[list->item[pos].anterior].proximo=livre;

        list->item[pos].anterior=livre;


        list->qItens++;

        return list;
    }
}

int length(Lista L){
    ListaImpl *list = L;
    return list->qItens;
}

Elem get(Lista L,int pos){
    ListaImpl *list=(ListaImpl *) L;
    return list->item[pos].elemento;
}
