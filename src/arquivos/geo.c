#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "geo.h"
#include "../util/util.h"
#include "../svg/svg.h"
#include "../figuras/figuras.h"
#include "../figuras/estrutura/rbtree.h"
#include "../figuras/estrutura/hash.h"


void processarComandosGeo(char *pGeo,char *localEntrada,char *localSaida,nx qtdFiguras,struct tree **circulo,
    struct tree **retangulo,struct tree **texto,struct tree **hidrante,struct tree **quadra,
    struct tree **semaforo,struct tree **radio,struct tree **muro,struct tree **predio,
    tabelaHash **hashCirc,tabelaHash **hashRet, tabelaHash **hashHid,tabelaHash **hashQuad,
    tabelaHash **hashSem,tabelaHash **hashRad,tabelaHash **hashPrd,tabelaHash **hashMur) {

    // Variável para leitura da linha do arquivo
    char linhaArquivo[500];
    // Variáveis auxiliares para abertura do arquivo
    char *temp1 = NULL;
    char *temp2 = NULL;
    // Variáveis para as cores padrões das figuras
    char cor1Semaforo[30]={"green"},cor2Semaforo[30]={"gray"};
    char cor1Hidrante[30]={"red"},cor2Hidrante[30]={"darkred"};
    char cor1Radio[30]={"orange"},cor2Radio[30]={"yellow"};
    char cor1Quadra[30]={"tan"},cor2Quadra[30]={"sandybrown"};
    char cor1Predio[30]={"cyan"},cor2Predio[30]={"midnightblue"};
    // Variáveis para controle da quantidade de figuras
    int totalFeitos = 0;
    int totalFeitosSemaforo = 0;
    int totalFeitosQuadra = 0;
    int totalFeitosHidrante = 0;
    int totalFeitosRadio = 0;
    int totalFeitosPredio = 0;
    int totalFeitosMuro = 0;
    // Variáveis para as bordas padrões das figuras
    double cw=1.5;
    double rw=1.5,cq=1.5,ch=1.5,cr=1.5,cs=1.5,cp=1.5;
    // Variáveis das trees das figuras
    *circulo = criarTree(comparaCirculo, comparaIdCirculo, removeCirculo, desenharCirculo);
    *retangulo = criarTree(comparaRetangulo, comparaIdRetangulo, removeRetangulo, desenharRetangulo);
    *texto = criarTree(comparaTexto, NULL, removeTexto, escreverTexto);
    *hidrante = criarTree(comparaHidrante, comparaIdHidrante, removeHidrante, desenharHidrante);
    *quadra = criarTree(comparaQuadra, comparaIdQuadra, removeQuadra, desenharQuadra);
    *semaforo = criarTree(comparaSemaforo, comparaIdSemaforo, removeSemaforo, desenharSemaforo);
    *radio = criarTree(comparaRadio, comparaIdRadio, removeRadio, desenharRadio);
    *muro = criarTree(comparaMuro, NULL, removeMuro, desenharMuro);
    *predio = criarTree(comparaPredio, comparaIdPredio, removePredio, desenharPredio);
    // Variáveis das hash das figuras
    *hashCirc = criarTabelaHash(getINx(qtdFiguras), comparaKeyCirculo, getCirculoID);
    *hashRet = criarTabelaHash(getINx(qtdFiguras), comparaKeyRetangulo, getRetanguloID);
    *hashHid = criarTabelaHash(getNhNx(qtdFiguras), comparaKeyHidrante, getHidranteId);
    *hashQuad = criarTabelaHash(getNqNx(qtdFiguras), comparaKeyQuadra, getQuadraId);
    *hashSem = criarTabelaHash(getNsNx(qtdFiguras), comparaKeySemaforo, getSemaforoId);
    *hashRad = criarTabelaHash(getNrNx(qtdFiguras), comparaKeyRadio, getRadioId);
    *hashPrd = criarTabelaHash(getNpNx(qtdFiguras), comparaKeyPredio, getPredioId);
    *hashMur = criarTabelaHash(getNmNx(qtdFiguras), comparaKeyMuro, getMuroId);
    // Variáveis dos arquivos de entrada e saída
    FILE *arquivoEntrada = NULL;
    FILE *arquivoSaida = NULL;

    // Abre o arquivo de comandos
    if(localEntrada == NULL) {
        arquivoEntrada = fopen(pGeo,"r");
    } else {
        temp1 = getArquivo(localEntrada,pGeo);
        arquivoEntrada = fopen(temp1,"r");
    }

    // Abre o arquivo svg de saída
    temp2 = getSvgSaida(localSaida,pGeo);
    arquivoSaida = fopen(temp2,"w");

    if(arquivoEntrada == NULL) {
        printf("Erro ao abrir o arquivo geo\n");
        exit(0);
    }

    if(arquivoSaida == NULL) {
        printf("Erro ao criar arquivo\n");
        exit(0);
    }

    // Inicia arquivo SVG
    iniciarSvg(temp2);

    // Lê e executa comandos
    while(fgets(linhaArquivo,500,arquivoEntrada)!=NULL) {
        if(linhaArquivo[0]=='c' && linhaArquivo[1]==' ') {
            // Adiciona Circulo
            if(totalFeitos < getINx(qtdFiguras)) {
                Circulo tempCirculo = addCirculo(linhaArquivo,cw);
                desenharCirculo(temp2,tempCirculo);
                totalFeitos++;
                insertTree(*circulo, tempCirculo);
                inserirHash(*hashCirc, tempCirculo);
            }
        } else if(linhaArquivo[0]=='r' && linhaArquivo[1]==' ') {
            // Adiciona Retangulo
            if(totalFeitos < getINx(qtdFiguras)) {
                Retangulo tempRetangulo = addRetangulo(linhaArquivo,rw);
                desenharRetangulo(temp2,tempRetangulo);
                totalFeitos++;
                insertTree(*retangulo, tempRetangulo);
                inserirHash(*hashRet, tempRetangulo);
            }
        } else if(linhaArquivo[0]=='t' && linhaArquivo[1]==' ') {
            // Adiciona Texto
            Texto tempTexto = addTexto(linhaArquivo);
            escreverTexto(temp2,tempTexto);
            insertTree(*texto, tempTexto);
        } else if(linhaArquivo[0]=='q' && linhaArquivo[1]==' ') {
            // Adiciona Quadra
            if(totalFeitosQuadra < getNqNx(qtdFiguras)) {
                Quadra tempQuadra = addQuadra(linhaArquivo,cq,cor1Quadra,cor2Quadra);
                desenharQuadra(temp2,tempQuadra);
                totalFeitosQuadra++;
                insertTree(*quadra, tempQuadra);
                inserirHash(*hashQuad, tempQuadra);
            }
        } else if(linhaArquivo[0]=='h' && linhaArquivo[1]==' ') {
            // Adiciona Hidrante
            if(totalFeitosHidrante < getNhNx(qtdFiguras)) {
                Hidrante tempHidrante = addHidrante(linhaArquivo,ch,cor1Hidrante,cor2Hidrante);
                desenharHidrante(temp2,tempHidrante);
                totalFeitosHidrante++;
                insertTree(*hidrante, tempHidrante);
                inserirHash(*hashHid, tempHidrante);
            }
        } else if(linhaArquivo[0]=='s' && linhaArquivo[1]==' ') {
            // Adiciona Semaforo
            if(totalFeitosSemaforo < getNsNx(qtdFiguras)) {
                Semaforo tempSemaforo = addSemaforo(linhaArquivo,cs,cor1Semaforo,cor2Semaforo);
                desenharSemaforo(temp2,tempSemaforo);
                totalFeitosSemaforo++;
                insertTree(*semaforo, tempSemaforo);
                inserirHash(*hashSem, tempSemaforo);
            }
        } else if(linhaArquivo[0]=='r' && linhaArquivo[1]=='b') {
            // Adiciona Radio Base
            if(totalFeitosRadio < getNrNx(qtdFiguras)) {
                Radio tempRadio = addRadio(linhaArquivo,cr,cor1Radio,cor2Radio);
                desenharRadio(temp2,tempRadio);
                totalFeitosRadio++;
                insertTree(*radio, tempRadio);
                inserirHash(*hashRad, tempRadio);
            }
        } else if(linhaArquivo[0]=='c' && linhaArquivo[1]=='q') {
            // Muda cores do preenchimento (cfill) e da borda (cstrk) das quadras, espessura da borda
            sscanf(linhaArquivo,"cq %s %s %lf",cor1Quadra,cor2Quadra,&cq);
        } else if(linhaArquivo[0]=='c' && linhaArquivo[1]=='h') {
            // Muda cores do preenchimento (cfill) e da borda (cstrk) dos hidrantes, espessura da borda
            sscanf(linhaArquivo,"ch %s %s %lf",cor1Hidrante,cor2Hidrante,&ch);
        } else if(linhaArquivo[0]=='c' && linhaArquivo[1]=='r') {
            // Muda cores do preenchimento (cfill) e da borda (cstrk) dos radios-base, espessura da borda
            sscanf(linhaArquivo,"cr %s %s %lf",cor1Radio,cor2Radio,&cr);
        } else if(linhaArquivo[0]=='c' && linhaArquivo[1]=='s') {
            // Muda cores do preenchimento (cfill) e da borda (cstrk) dos semaforos, espessura da borda
            sscanf(linhaArquivo,"cs %s %s %lf",cor1Semaforo,cor2Semaforo,&cs);
        } else if(linhaArquivo[0]=='s' && linhaArquivo[1]=='w') {
            // Espessuras das bordas dos circulos e retangulos
            sscanf(linhaArquivo,"sw %lf %lf",&cw,&rw);
        } else if(linhaArquivo[0]=='p' && linhaArquivo[1]=='r') {
            // Adiciona Predio
            if(totalFeitosPredio < getNpNx(qtdFiguras)) {
                Predio tempPredio = addPredio(linhaArquivo, *hashQuad);
                desenharPredio(temp2, tempPredio);
                totalFeitosPredio++;
                insertTree(*predio, tempPredio);
                inserirHash(*hashPrd, tempPredio);
            }
        } else if(linhaArquivo[0]=='m' && linhaArquivo[1]=='u') {
            // Adiciona Muro
            if(totalFeitosMuro < getNmNx(qtdFiguras)) {
                char converte[10];
                sprintf(converte, "%d", totalFeitosMuro);
                Muro tempMuro = addMuro(linhaArquivo,converte);
                desenharMuro(temp2,tempMuro);
                totalFeitosMuro++;
                insertTree(*muro, tempMuro);
                inserirHash(*hashMur, tempMuro);
            }
        }
    }

    /* Percorrer uma hash
    int c = 0;
	for (int i = 0; i < getTamHash(*hashSem); i++) {
		listaHash n = getIndiceHash(*hashSem, i);
		if (n != NULL) {
			listaHash aux = n;
			while (aux != NULL) {
				n = getProxHash(n);
				printf("c : %d\n", c);
				printf("i: %d\n", i);
				c++;
				aux = n;
			}
		}
	}*/

    finalizarSvg(temp2);

    // Fecha arquivos
    fclose(arquivoEntrada);
    fclose(arquivoSaida);
    free(temp1);
    free(temp2);
}
