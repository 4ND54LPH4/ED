#include <stdio.h>
#include <stdlib.h>
#include "main.h"

int main(int argc,char *argv[]) {
    // Variáveis para armazenar os parâmetros ("-f","-q","-e","-o","-ec","-pm","-i")
    char *pGeo = NULL;
    char *pQry = NULL;
    char *localEntrada = NULL;
    char *localSaida = NULL;
    char *estabComercial = NULL;
    char *pessoas = NULL;
    int modoInterativo = 0;
    // Variável para armazenar o número máximo de figuras
    nx *quantidadeFiguras;
    quantidadeFiguras = criaNx();

    // Pega os parâmetros
    getParametros(argc,argv,&pGeo,&pQry,&localEntrada,&localSaida,&estabComercial,&pessoas,&modoInterativo);

    // Formata parâmetros para um padrão
    tratarParametros(&pGeo,&pQry,&localEntrada,&localSaida,&estabComercial,&pessoas);

    // Pega a quantidade de figuras do comando NX do arquivo
    quantidadeFiguras = getNx(quantidadeFiguras,localEntrada,pGeo);
    if(getINx(quantidadeFiguras) == -1) {
        quantidadeFiguras = iniciaNx(quantidadeFiguras);
    }

    // Comandos do arquivo .geo
    processarComandosGeo(pGeo,localEntrada,localSaida,quantidadeFiguras);

    // Comandos do arquivo .ec (caso exista)
    if(estabComercial != NULL) {
        processarComandosEc(estabComercial,localEntrada,localSaida,quantidadeFiguras);
    }

    // Comandos do arquivo .pm (caso exista)
    if(pessoas != NULL) {
        processarComandosPm(pessoas,localEntrada,localSaida,quantidadeFiguras);
    }
    
    // Comandos do arquivo .qry (caso exista)
    if(pQry != NULL) {
        processarComandosQry(pQry,localEntrada);
    }

    // Entra no modo interativo (caso seja solicitado)
    if(modoInterativo) {
        printf("Mexe agora corno\n");
        getchar();
    }

    // PRINTANDO AS VARIÁVEIS P TESTA ESSA MERDA
    printf("\n\nGeo: %s\nQry: %s\nlocalEntrada: %s\nlocalSaida: %s\nestab: %s\npessoas: %s\nmodoI: %d\n\n",pGeo,pQry,localEntrada,localSaida,estabComercial,pessoas,modoInterativo);

    // Desalocar variáveis
    free(pGeo);
    free(pQry);
    free(localEntrada);
    free(localSaida);
    free(estabComercial);
    free(pessoas);
    free(quantidadeFiguras);
    return 0;
}