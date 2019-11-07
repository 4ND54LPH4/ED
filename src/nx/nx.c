#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "nx.h"
#include "../util/util.h"

struct nx {
    int i, nq, nh, ns, nr, np, nm;
};

nx criaNx() {
    struct nx *novoNx = (struct nx*)malloc(sizeof(struct nx));
    novoNx->i = -1;
    novoNx->nq = -1;
    novoNx->nh = -1;
    novoNx->ns = -1;
    novoNx->nr = -1;
    novoNx->np = -1;
    novoNx->nm = -1;
    return (void*)novoNx;
}

nx getNx(nx recebeNx,char *localEntrada,char *fileGeo) {
    struct nx *tempNx = (struct nx*)recebeNx;
    int contador=0;
    int espaco=0;
    int i=-1,nq=-1,nh=-1,ns=-1,nr=-1,np=-1,nm=-1;
    char comandos[500];
    char *local=NULL;
    FILE *arquivo=NULL;

    local = getArquivo(localEntrada,fileGeo);
    arquivo = fopen(local,"r");
    
    espaco = contadorEspacosNx(localEntrada,fileGeo);

    if(espaco==1) {
        while(contador < 9) {
            fgets(comandos,500,arquivo);
            if(comandos[0]=='n' && comandos[1]=='x') {
                sscanf(comandos,"nx %d",&i);
                break;
            }
        }
        tempNx->i = i;
    } else if(espaco==5) {
        while(contador < 9) {
            fgets(comandos,500,arquivo);
            if(comandos[0]=='n' && comandos[1]=='x') {
                sscanf(comandos,"nx %d %d %d %d %d",&i,&nq,&nh,&ns,&nr);
                break;
            } 
        }
        tempNx->i = i;
        tempNx->nq = nq;
        tempNx->nh = nh;
        tempNx->ns = ns;
        tempNx->nr = nr;
    } else if(espaco==7) {
        while(contador < 9) {
            fgets(comandos,500,arquivo);
            if(comandos[0]=='n' && comandos[1]=='x') {
                sscanf(comandos,"nx %d %d %d %d %d %d %d",&i,&nq,&nh,&ns,&nr,&np,&nm);
                break;
            } 
        }
        tempNx->i = i;
        tempNx->nq = nq;
        tempNx->nh = nh;
        tempNx->ns = ns;
        tempNx->nr = nr;
        tempNx->np = np;
        tempNx->nm = nm;
    }


    free(local);
    fclose(arquivo);
    return (void*)tempNx;
}

nx iniciaNx(nx recebeNx) {
    struct nx *tempNx = (struct nx*)recebeNx;

    tempNx->i = 1000;
    tempNx->nq = 1000;
    tempNx->nh = 1000;
    tempNx->ns = 1000;
    tempNx->nr = 1000;
    tempNx->np = 1000;
    tempNx->nm = 1000;

    return (void*)tempNx;
}

int contadorEspacosNx(char *localEntrada,char *fileGeo) {
    int espaco=0;
    int contador=0;
    char comandos[500];
    char *local=NULL;
    FILE *arquivo=NULL;

    local = getArquivo(localEntrada,fileGeo);
    arquivo = fopen(local,"r");

    while(contador < 9) {
        fgets(comandos,500,arquivo);
        if(comandos[0]=='n' && comandos[1]=='x') {
            for(int i=0;i<strlen(comandos);i++) {
                if(comandos[i]==' ')
                    espaco++;
            }
            break;
        } 
        contador++;
    }
    
    fclose(arquivo);
    free(local);
    return espaco;
}

int getINx(nx recebeNx) {
    struct nx *tempNx = (struct nx*)recebeNx;
    return tempNx->i;
}

int getNqNx(nx recebeNx) {
    struct nx *tempNx = (struct nx*)recebeNx;
    return tempNx->nq;
}

int getNhNx(nx recebeNx) {
    struct nx *tempNx = (struct nx*)recebeNx;
    return tempNx->nh;
}

int getNsNx(nx recebeNx) {
    struct nx *tempNx = (struct nx*)recebeNx;
    return tempNx->ns;
}

int getNrNx(nx recebeNx) {
    struct nx *tempNx = (struct nx*)recebeNx;
    return tempNx->nr;
}

int getNpNx(nx recebeNx) {
    struct nx *tempNx = (struct nx*)recebeNx;
    return tempNx->np;
}

int getNmNx(nx recebeNx) {
    struct nx *tempNx = (struct nx*)recebeNx;
    return tempNx->nm;
}