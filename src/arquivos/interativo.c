#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "interativo.h"
#include "../util/util.h"
#include "../svg/svg.h"
#include "../figuras/figuras.h"
#include "../figuras/estrutura/rbtree.h"
#include "qry.h"

void processarInterativo(char *pGeo,char *pQry,char *localEntrada,char *localSaida,nx qtdFiguras,
    struct tree **circulo,struct tree **retangulo,struct tree **texto,struct tree **hidrante,
    struct tree **quadra,struct tree **semaforo,struct tree **radio,struct tree **muro,struct tree **predio,
    struct tree **tipoEstabelecimento, struct tree **estabelecimento,struct tree **pessoa,struct tree**morador,
    tabelaHash **hashCirc,tabelaHash **hashRet,tabelaHash **hashHid,
    tabelaHash **hashQuad,tabelaHash **hashSem,tabelaHash **hashRad,
    tabelaHash **hashPrd,tabelaHash **hashMur,tabelaHash **hashTipEst,
    tabelaHash **hashEst,tabelaHash **hashPes,tabelaHash **hashMor) {

    char linhaComando[100], instrucao[10], comandoNav[100], instrucaoNav[10];
    while (1) {
        printf("MODO INTERATIVO\n");
        printf("Comando: ");
        fgets(linhaComando, 100, stdin);
        sscanf(linhaComando, "%s", instrucao);

        if (!strcmp(instrucao, "sai")) {
            break;
        } else if (!strcmp(instrucao, "q")) {
            char novoQry[50];
            sscanf(linhaComando, "q %s", novoQry);
            processarComandosQry(pGeo, novoQry, localEntrada, localSaida, qtdFiguras,circulo,retangulo,texto,hidrante,quadra,semaforo,radio,muro,predio,tipoEstabelecimento,estabelecimento,pessoa,morador,(tabelaHash)hashCirc,(tabelaHash)hashRet,(tabelaHash)hashHid,(tabelaHash)hashQuad,(tabelaHash)hashSem,(tabelaHash)hashRad,(tabelaHash)hashPrd,(tabelaHash)hashMur,(tabelaHash)hashTipEst,(tabelaHash)hashEst,(tabelaHash)hashPes,(tabelaHash)hashMor);
        } else if (!strcmp(instrucao, "dmprbt")) {
            char t, *nomeArq;
            sscanf(linhaComando, "dmprbt %c %s", &t, nomeArq);
            // chamar função comando dmprbt
        } else if (!strcmp(instrucao, "nav")) {
            char t, consulta[150], result[150];
            struct node* node;
            struct tree* tree;
            char*(*getDadosObjeto)(void* objeto, char* dados);
            sscanf(linhaComando, "nav %c", &t);
            if (t == 'q') {
                tree = *quadra;
                node = getRaizArvore(tree);
                getDadosObjeto = printValorQuadra;
            } else if (t == 'h') {
                tree = *hidrante;
                node = getRaizArvore(tree);
                getDadosObjeto = printValorHidrante;
            } else if (t == 's') {
                tree = *semaforo;
                node = getRaizArvore(tree);
                getDadosObjeto = printValorSemaforo;
            } else if (t == 't') {
                tree = *radio;
                node = getRaizArvore(tree);
                getDadosObjeto = printValorRadio;
            } else if (t == 'p') {
                tree = *predio;
                node = getRaizArvore(tree);
                getDadosObjeto = printValorPredio;
            } else if (t == 'm') {
                tree = *muro;
                node = getRaizArvore(tree);
                getDadosObjeto = printValorMuro;
            }

            while(1) {
                printf("Navegar na arvore\n");
                printf("Comando: ");
                fgets(comandoNav, 100, stdin);
                sscanf(comandoNav, "%s", instrucaoNav);

                if (!strcmp(instrucaoNav, "x")) {
                    break;
                } else if (!strcmp(instrucaoNav, "e")) {
                    if (getLeftNode(node) != getNilArvore(tree)) {
                        node = getLeftNode(node);
                    } else {
                        printf("NULL\n");
                        continue;
                    }
                } else if (!strcmp(instrucaoNav, "d")) {
                    if (getRightNode(node) != getNilArvore(tree)) {
                        node = getRightNode(node);
                    } else {
                        printf("NULL\n");
                        continue;
                    }
                } else if (!strcmp(instrucaoNav, "p")) {
                    if (getPaiNode(node) != getNilArvore(tree)) {
                        node = getPaiNode(node);
                    } else {
                        printf("NULL\n");
                        continue;
                    }
                }

                if (node == getNilArvore(tree)) {
                    printf("NULL\n");
                    continue;
                }
                printf("\nDados: %s\nCor: %s\n", getDadosObjeto(getObjetoNode(node), consulta), getCorNode(node));
            }
        }
    }
}
