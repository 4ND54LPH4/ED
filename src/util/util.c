#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "util.h"

void tratarParametros(char **pGeo,char **pQry,char **localEntrada,char **localSaida,char **estabComercial,char **pessoas) {
    tratarArquivo(pGeo);
    
    if(*pQry != NULL) {
        tratarArquivo(pQry);
    }

    if(*localEntrada != NULL) {
        tratarLocal(localEntrada);
    } else {
        if(*pGeo[0]!='/') {
            *localEntrada = (char*)malloc(sizeof(char)*3);
            strcpy(*localEntrada,"./");
        }
    }
    
    tratarLocal(localSaida);

    if(*estabComercial != NULL) {
        tratarArquivo(estabComercial);
    }

    if(*pessoas != NULL) {
        tratarArquivo(pessoas);
    }
}

void tratarArquivo(char **file) {
    int size;
    char *temp = NULL;
    size = strlen(*file);
    temp = (char*)malloc(sizeof(char)*size+1);
    strcpy(temp,*file);
    if(temp[0]=='.') {
        for(int i=0;i<size-2;i++) {
            temp[i] = temp[i+2];
        }
        temp[size-2] = '\0';
        strcpy(*file,temp);
    }
    free(temp);
}

void tratarLocal(char **local) {
    int size;
    char *temp=NULL;
    size = strlen(*local);
    temp = (char*)malloc(sizeof(char)*size+2);
    strcpy(temp,*local);
    if(temp[size-1]!='/') {
        *local = (char*)realloc(*local,size+2);
        strcat(*local,"/");
    }
    free(temp);
}

char *getArquivo(char *local,char *arquivo) {
    char *result = NULL;

    result = (char*)malloc(sizeof(char)*(strlen(local)+strlen(arquivo)+2));
    strcpy(result,local);
    strcat(result,arquivo);

    return result;
}

char *getSvgSaida(char *localSaida,char *arquivo) {
    char *nomeArquivo = NULL;
    char *result = NULL;

    nomeArquivo = tiraExtensao(arquivo);

    result = (char*)malloc(sizeof(char)*(strlen(nomeArquivo)+strlen(localSaida)+5));

    strcpy(result,localSaida);
    strcat(result,nomeArquivo);
    strcat(result,".svg");

    free(nomeArquivo);
    return result;
}

char *tiraExtensao(char *arquivo) {
    int size;
	char *temp=NULL;
    char *aux=NULL;
	char *result=NULL;
	temp = strrchr(arquivo,'/');
	if(temp==NULL)
	{
        size = strlen(arquivo);
		if(arquivo[size-1] == 'o' || arquivo[size-1] == 'y') {
            result = (char*)calloc(strlen(arquivo)-3,sizeof(char));
		    strncpy(result,arquivo,strlen(arquivo)-4);
        } else {
            result = (char*)calloc(strlen(arquivo)-2,sizeof(char));
		    strncpy(result,arquivo,strlen(arquivo)-3);
        }
	}
	else
	{
        size = strlen(arquivo);
        if(arquivo[size-1] == 'o' || arquivo[size-1] == 'y') {
            size = strlen(temp) - 4;
            aux = (char*)calloc(size+1,sizeof(char));
            strncpy(aux,temp,size);
            result = tiraBarra(aux);
            free(aux);
        } else {
            size = strlen(temp) - 3;
            aux = (char*)calloc(size+1,sizeof(char));
            strncpy(aux,temp,size);
            result = tiraBarra(aux);
            free(aux);
        }
	}
    return result;
}

char *tiraBarra(char *file) {
    int i,j;
	char *temp1=NULL;
	char *temp2=NULL;
	temp1 = (char*)malloc(sizeof(char)*(strlen(file)+1));
	strcpy(temp1,file);
	i = strlen(file) + 1;
    temp2 = (char*)calloc(strlen(file)+1,sizeof(char));
	//temp2 = (char*)malloc(sizeof(char)*(strlen(file)+1));
	//temp2[0] = '\0';
	for(j=0;j<i-1;j++)
	{
		temp2[j] = temp1[j+1];
	}
	free(temp1);
	return temp2;
}