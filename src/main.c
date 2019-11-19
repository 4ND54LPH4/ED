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
    // Variáveis das trees das figures
    struct tree *circulo;
    struct tree *retangulo;
    struct tree *texto;
    struct tree *hidrante;
    struct tree *quadra;
    struct tree *semaforo;
    struct tree *radio;
    struct tree *muro;
    struct tree *predio;
    struct tree *pessoa;
    struct tree *morador;
    struct tree *tipoEstabelecimento;
    struct tree *estabelecimento;
    // Variáveis das hash das figuras
    struct tabelaHash *hashCirc;
    struct tabelaHash *hashRet;
    struct tabelaHash *hashHid;
    struct tabelaHash *hashQuad;
    struct tabelaHash *hashSem;
    struct tabelaHash *hashRad;
    struct tabelaHash *hashPrd;
    struct tabelaHash *hashMur;
    struct tabelaHash *hashPes;
    struct tabelaHash *hashMor;
    struct tabelaHash *hashTipEst;
    struct tabelaHash *hashEst;
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
    processarComandosGeo(pGeo,localEntrada,localSaida,quantidadeFiguras,&circulo,&retangulo,&texto,&hidrante,&quadra,&semaforo,&radio,&muro,&predio,(tabelaHash)&hashCirc,(tabelaHash)&hashRet,(tabelaHash)&hashHid,(tabelaHash)&hashQuad,(tabelaHash)&hashSem,(tabelaHash)&hashRad,(tabelaHash)&hashPrd,(tabelaHash)&hashMur);

    // Comandos do arquivo .pm (caso exista)
    if(pessoas != NULL) {
        processarComandosPm(pessoas,localEntrada,localSaida,quantidadeFiguras, &pessoa, &morador, (tabelaHash)&hashPes, (tabelaHash)&hashMor);
    }

    // Comandos do arquivo .ec (caso exista)
    if(estabComercial != NULL) {
        processarComandosEc(estabComercial,localEntrada,localSaida,quantidadeFiguras, &tipoEstabelecimento, &estabelecimento, (tabelaHash)&hashTipEst, (tabelaHash)&hashEst, (tabelaHash)&hashPes);
    }

    // Comandos do arquivo .qry (caso exista)
    if(pQry != NULL) {
        processarComandosQry(pGeo,pQry,localEntrada,localSaida,quantidadeFiguras,&circulo,&retangulo,&texto,&hidrante,&quadra,&semaforo,&radio,&muro,&predio,&tipoEstabelecimento,&estabelecimento,&pessoa,&morador,(tabelaHash)&hashCirc,(tabelaHash)&hashRet,(tabelaHash)&hashHid,(tabelaHash)&hashQuad,(tabelaHash)&hashSem,(tabelaHash)&hashRad,(tabelaHash)&hashPrd,(tabelaHash)&hashMur,(tabelaHash)&hashTipEst,(tabelaHash)&hashEst,(tabelaHash)&hashPes,(tabelaHash)&hashMor);
    }

    // Entra no modo interativo (caso seja solicitado)
    if(modoInterativo) {
        processarInterativo(pGeo,pQry,localEntrada,localSaida,quantidadeFiguras,&circulo,&retangulo,&texto,&hidrante,&quadra,&semaforo,&radio,&muro,&predio,&tipoEstabelecimento,&estabelecimento,&pessoa,&morador,(tabelaHash)&hashCirc,(tabelaHash)&hashRet,(tabelaHash)&hashHid,(tabelaHash)&hashQuad,(tabelaHash)&hashSem,(tabelaHash)&hashRad,(tabelaHash)&hashPrd,(tabelaHash)&hashMur,(tabelaHash)&hashTipEst,(tabelaHash)&hashEst,(tabelaHash)&hashPes,(tabelaHash)&hashMor);
    }

    // Desalocar variáveis
    destruirTabelaHash(hashCirc);
    destruirTabelaHash(hashRet);
    destruirTabelaHash(hashPrd);
    destruirTabelaHash(hashMur);
    destruirTabelaHash(hashQuad);
    destruirTabelaHash(hashHid);
    destruirTabelaHash(hashSem);
    destruirTabelaHash(hashRad);

    deleteTree(predio);
    deleteTree(quadra);
    deleteTree(hidrante);
    deleteTree(semaforo);
    deleteTree(radio);
    deleteTree(muro);
    deleteTree(circulo);
    deleteTree(retangulo);
    deleteTree(texto);

    if(estabComercial != NULL) {
        destruirTabelaHash(hashTipEst);
        destruirTabelaHash(hashEst);
        deleteTree(tipoEstabelecimento);
        deleteTree(estabelecimento);
    }

    if(pessoas != NULL) {
        destruirTabelaHash(hashPes);
        destruirTabelaHash(hashMor);
        deleteTree(pessoa);
        deleteTree(morador);
    }

    free(pGeo);
    free(pQry);
    free(localEntrada);
    free(localSaida);
    free(estabComercial);
    free(pessoas);
    free(quantidadeFiguras);
    return 0;
}
