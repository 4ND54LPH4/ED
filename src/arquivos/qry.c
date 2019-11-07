#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "qry.h"
#include "../util/util.h"


void processarComandosQry(char *pQry,char *localEntrada) {
    char linhaArquivo[500];
    char *temp = NULL;
    /*FILE *arquivoEntrada = NULL;

    // Abre arquivo de pesquisa
    if(localEntrada == NULL || ((localEntrada != NULL) && (pQry[0] == '/'))) {
        arquivoEntrada = fopen(pQry,"r");
    } else {
        temp = concatenarLocalArquivo(localEntrada,pQry);
        arquivoEntrada = fopen(temp,"r");
        free(temp);
    }

    if(arquivoEntrada == NULL) {
        printf("Erro ao abrir o arquivo qry\n");
        exit(0);
    }

    // Lê e executa comandos
    while(fgets(linhaArquivo,500,arquivoEntrada)!=NULL) {
        printf("%s",linhaArquivo);
    }

    // Fecha arquivo de leitura
    fclose(arquivoEntrada);*/
}