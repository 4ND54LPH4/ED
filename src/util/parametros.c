#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parametros.h"

void getParametros(int argc,char *argv[],char **pGeo,char **pQry,char **localEntrada,char **localSaida,char **estabComercial,char **pessoas,int *modoInterativo) {
    int contadorParametros = 0;
    
    while(contadorParametros < argc) {
        if(!strcmp(argv[contadorParametros],"-f")) {
            *pGeo = (char*)malloc(sizeof(char)*(strlen(argv[contadorParametros+1])+1));
            strcpy(*pGeo,argv[contadorParametros+1]);
        } else if(!strcmp(argv[contadorParametros],"-q")) {
            *pQry = (char*)malloc(sizeof(char)*(strlen(argv[contadorParametros+1])+1));
            strcpy(*pQry,argv[contadorParametros+1]);
        } else if(!strcmp(argv[contadorParametros],"-e")) {
            *localEntrada = (char*)malloc(sizeof(char)*(strlen(argv[contadorParametros+1])+1));
            strcpy(*localEntrada,argv[contadorParametros+1]);
        } else if(!strcmp(argv[contadorParametros],"-o")) {
            *localSaida = (char*)malloc(sizeof(char)*(strlen(argv[contadorParametros+1])+1));
            strcpy(*localSaida,argv[contadorParametros+1]);
        } else if(!strcmp(argv[contadorParametros],"-ec")) {
            *estabComercial = (char*)malloc(sizeof(char)*(strlen(argv[contadorParametros+1])+1));
            strcpy(*estabComercial,argv[contadorParametros+1]);
        } else if(!strcmp(argv[contadorParametros],"-pm")) {
            *pessoas = (char*)malloc(sizeof(char)*(strlen(argv[contadorParametros+1])+1));
            strcpy(*pessoas,argv[contadorParametros+1]);
        } else if(!strcmp(argv[contadorParametros],"-i")) {
            *modoInterativo = 1;
        }


        contadorParametros++;
    }

    if(*pGeo == NULL) {
        printf("Parâmetro \"-f\" necessário!\n");
        free(*pQry);
        free(*localEntrada);
        free(*localSaida);
        exit(0);
    }
    if(*localSaida == NULL) {
        printf("Parâmetro \"-o\" necessário!\n");
        free(*pGeo);
        free(*pQry);
        free(*localEntrada);
        exit(0);
    }
}