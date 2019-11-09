#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functionsQry.h"
#include "../util/util.h"
#include "../svg/svg.h"
#include "../figuras/figuras.h"
#include "../figuras/estrutura/rbtree.h"
#include "../figuras/estrutura/hash.h"
#include <math.h>


// COMANDOS T1

// Comando "o?"
// Com erro
/*
void comandoOverlap(char *linhaArquivo,char *saidaSvg,char *saidaTxt,struct tree **circulo,struct tree **retangulo,tabelaHash **hashCirc,tabelaHash **hashRet) {
    char id1[20],id2[20];
    int overlap = 0;
    // Arquivos de saída
    FILE *arquivoSaidaSvg = NULL;
    FILE *arquivoSaidaTxt = NULL;

    arquivoSaidaSvg = fopen(saidaSvg,"a+");
    arquivoSaidaTxt = fopen(saidaTxt,"a+");

    if(arquivoSaidaSvg == NULL || arquivoSaidaTxt == NULL) {
        printf("Erro ao abrir arquivo\n");
        exit(0);
    }

    sscanf(linhaArquivo,"o? %s %s",id1,id2);

    Circulo c1;
    Circulo c2;
    Retangulo r1;
    Retangulo r2;

    if((c1 = getObjetoHash(*hashCirc,id1)) != NULL) {
        if((c2 = getObjetoHash(*hashCirc,id2)) != NULL) {
            // 2 circulos
        } else {
            r2 = getObjetoHash(*hashRet,id2);
            // Circulo Retangulo

        }
    } else {
        r1 = getObjetoHash(*hashRet,id1);
        if((c2 = getObjetoHash(*hashCirc,id2)) != NULL) {
            // Retangulo Circulo

        } else {
            r2 = getObjetoHash(*hashRet,id2);
            // 2 retangulos

        }
    }

    if(overlap) {

    } else {

    }

    fclose(arquivoSaidaSvg);
    fclose(arquivoSaidaTxt);
}*/

// Comandos "i?"
void comandoInterno(char *linhaArquivo,char *saidaSvg,char *saidaTxt,struct tree **circulo,struct tree **retangulo,tabelaHash **hashCirc,tabelaHash **hashRet) {
    char id[20];
    double x,y;
    double x1Figura,y1Figura,x2Figura,y2Figura,raio;
    double distancia,distAux;
    double dx,dy;

    Circulo c;
    Retangulo r;

    sscanf(linhaArquivo,"i? %s %lf %lf",id,&x,&y);

    if((c = getObjetoHash(*hashCirc,id)) != NULL) {
        x1Figura = getCirculoX(c);
        y1Figura = getCirculoY(c);
        raio = getCirculoRaio(c);
        dx = x-x1Figura;
        dy = y-y1Figura;
        
        distancia = sqrt((dx*dx) + (dy*dy));

        if(distancia >= raio) {
            escreverPontoNaoInterno(x,y,linhaArquivo,saidaTxt,saidaSvg);
        } else if(distancia < raio) {
            escreverPontoInterno(x,y,linhaArquivo,saidaTxt,saidaSvg);
        }

        escreverRetaDistancia(x1Figura,y1Figura,x,y,"black",saidaSvg);
    } else {
        r = getObjetoHash(*hashRet,id);
        x1Figura = getRetanguloX(r);
        y1Figura = getRetanguloY(r) + getRetanguloAltura(r);
        x2Figura = getRetanguloX(r) + getRetanguloLargura(r);
        y2Figura = getRetanguloY(r);

        if(x > x1Figura) {
            if(x < x2Figura) {
                if(y > y1Figura) {
                    if(y < y2Figura) {
                        escreverPontoInterno(x,y,linhaArquivo,saidaTxt,saidaSvg);
                        x1Figura = getRetanguloX(r) + (getRetanguloLargura(r)/2);
                        y1Figura = getRetanguloY(r) + (getRetanguloAltura(r)/2);
                        escreverRetaDistancia(x1Figura,y1Figura,x,y,"black",saidaSvg);
                        return;
                    }
                }
            }
        }

        x1Figura = getRetanguloX(r) + (getRetanguloLargura(r)/2);
        y1Figura = getRetanguloY(r) + (getRetanguloAltura(r)/2);

        escreverPontoNaoInterno(x,y,linhaArquivo,saidaTxt,saidaSvg);
        escreverRetaDistancia(x1Figura,y1Figura,x,y,"black",saidaSvg);
    }

}

// Comando "d?"
void comandoDistancia(char *linhaArquivo,char *saidaSvg,char *saidaTxt,struct tree **circulo,struct tree **retangulo,tabelaHash **hashCirc,tabelaHash **hashRet) {
    char id1[20],id2[20];
    double dx1,dx2,dy1,dy2;
    double distancia;

    Circulo c1;
    Circulo c2;
    Retangulo r1;
    Retangulo r2;

    sscanf(linhaArquivo,"d? %s %s",id1,id2);


    if((c1 = getObjetoHash(*hashCirc,id1)) != NULL) {

        dx1 = getCirculoX(c1);
        dy1 = getCirculoY(c1);
        
        if((c2 = getObjetoHash(*hashCirc,id2)) != NULL) {

            dx2 = getCirculoX(c2);
            dy2 = getCirculoY(c2);
        } else {

            r2 = getObjetoHash(*hashRet,id2);
            dx2 = getRetanguloX(r2) + (getRetanguloLargura(r2)/2);
            dy2 = getRetanguloY(r2) + (getRetanguloAltura(r2)/2);
        }
    } else {

        r1 = getObjetoHash(*hashRet,id1);
        
        dx2 = getRetanguloX(r1) + (getRetanguloLargura(r1)/2);
        
        dy2 = getRetanguloY(r1) + (getRetanguloAltura(r1)/2);


        if((c2 = getObjetoHash(*hashCirc,id2)) != NULL) {

            dx1 = getCirculoX(c2);

            dy1 = getCirculoY(c2);
        } else {
            
            r2 = getObjetoHash(*hashRet,id2);
            dx1 = getRetanguloX(r2) + (getRetanguloLargura(r2)/2);
            
            dy1 = getRetanguloY(r2) + (getRetanguloAltura(r2)/2);
        }
    }

    distancia = (dx2 - dx1)*(dx2 - dx1) + (dy1 - dy2)*(dy1 - dy2);
    distancia = sqrt(distancia);

    escreverRetaDistancia(dx1,dy1,dx2,dy2,"red",saidaSvg);
    escreverDistanciaSvg((dx1+dx2)/2,(dy1+dy2)/2,distancia,saidaSvg);
    escreverDistanciaTxt(linhaArquivo,distancia,saidaTxt);
}

// Comando "bb"
// Com erro
/*
void comandoBB(char *linhaArquivo,char *nomeSaidaSvg,struct tree **circulo,struct tree **retangulo,struct tree **texto) {
    char *nomeArquivo = NULL;
    char *temp = NULL;
    char sufixo[150];
    char cor[50];

    FILE *saidaBB = NULL;

    sscanf(linhaArquivo,"bb %s %s",sufixo,cor);

    nomeArquivo = tiraExtensao(nomeSaidaSvg);
    temp = (char*)calloc(strlen(nomeArquivo)+strlen(sufixo)+6,sizeof(char));
    strcpy(temp,nomeArquivo);
    strcat(temp,"-");
    strcat(temp,sufixo);
    strcat(temp,".svg");

    saidaBB = fopen(temp,"w");
    
    fclose(saidaBB);
    free(nomeArquivo);
    free(temp);
}*/

// COMANDOS T2

// Função para exemplo de consulta nas trees e hash
void comandoDq (char* comandos, char* nomeSvg, char* nomeTxt, struct tree **hidrante, struct tree **semaforo, struct tree **radio, struct tree**quadra, tabelaHash **hashHid, tabelaHash **hashSem, tabelaHash **hashRad, tabelaHash **hashQuad) {
    char metrica[3], id[50];
    double dist1, dist2, x1, y1, x2, y2, w1, h1;
    int tam;
    sscanf(comandos, "dq %s %s %lf", metrica, id, &dist1);

    // Declaração variaveis para cada figura
    Hidrante h;
    Semaforo s;
    Radio r;
    Quadra q;

    // Verifica a qual figura pertence o id dado
    if ((h = getObjetoHash(*hashHid, id)) != NULL) {
        x2 = getHidranteX(h);
        y2 = getHidranteY(h);
    } else if ((s = getObjetoHash(*hashSem, id)) != NULL) {
        x2 = getSemaforoX(s);
        y2 = getSemaforoY(s);
    } else if ((r = getObjetoHash(*hashRad, id)) != NULL) {
        x2 = getRadioX(r);
        y2 = getRadioY(r);
    }

    tam = getTamHash(*hashQuad);

    if (strcmp(metrica, "L1") == 0) {
        // Percorrer a hash de quadra para encontrar qual satisfaz a condicao dada. isso aqui é reutilizavel
        for (int i = 0; i < tam; i++) {
    		listaHash n = getIndiceHash(*hashQuad, i);
    		if (n != NULL) {
    			listaHash aux = n;
    			while (aux != NULL) {
    				n = getProxHash(n);
                    // Daqui pra baixo pode mudar dependendo do que o comando pede
                    q = getObjetoHash2(aux); // Para poder dar os get precisa desse comando antes
                    x1 = getQuadraX(q);
                    y1 = getQuadraY(q);
                    h1 = getQuadraAltura(q);
                    w1 = getQuadraLargura(q);
                    if ((fabs(x2 - x1) + fabs(y2 - y1)) <= dist1 && (fabs(x2 - (x1+w1)) + fabs(y2 - y1)) <= dist1 && (fabs(x2 - x1) + fabs(y2 - (y1+h1))) <= dist1 && (fabs(x2 - (x1+w1)) + fabs(y2 - (y1+h1))) <= dist1) {
                        // Se satisfazer condicao remover primeiro da hash depois da tree (sempre nessa ordem)
                        removerObjetoHash(*hashQuad, getQuadraId(q));
                        // Para excluir da tree precisa antes dar o findtree e salvar na variavel da figura
                        q = findTree(*quadra, q);
                        deleteNodeTree(*quadra, q);
                    }
                    // Isso n muda
    				aux = n;
    			}
    		}
    	}
    } else if (strcmp(metrica, "L2") == 0) {
        for (int i = 0; i < tam; i++) {
    		listaHash n = getIndiceHash(*hashQuad, i);
    		if (n != NULL) {
    			listaHash aux = n;
    			while (aux != NULL) {
    				n = getProxHash(n);
                    // Daqui pra baixo pode mudar dependendo do que o comando pede
                    q = getObjetoHash2(aux); // Para poder dar os get precisa desse comando antes
                    x1 = getQuadraX(q);
                    y1 = getQuadraY(q);
                    h1 = getQuadraAltura(q);
                    w1 = getQuadraLargura(q);
                    if ((sqrt(pow((x2 - x1), 2) + pow((y2 - y1), 2))) <= dist1 && (sqrt(pow((x2 - (x1+w1)), 2) + pow((y2 - y1), 2))) <= dist1 && (sqrt(pow((x2 - x1), 2) + pow((y2 - (y1+h1)), 2))) <= dist1 && (sqrt(pow((x2 - (x1+w1)), 2) + pow((y2 - (y1+h1)), 2))) <= dist1) {
                        // Se satisfazer condicao remover primeiro da hash depois da tree (sempre nessa ordem)
                        removerObjetoHash(*hashQuad, getQuadraId(q));
                        // Para excluir da tree precisa antes dar o findtree e salvar na variavel da figura
                        q = findTree(*quadra, q);
                        deleteNodeTree(*quadra, q);
                    }
                    // Isso n muda
    				aux = n;
    			}
    		}
        }
    }
}

// Com erro
/*
void comandoDel(char *linhaArquivo,char *saidaSvg,char *saidaTxt,struct tree **hidrante, struct tree **semaforo, struct tree **radio, struct tree**quadra, tabelaHash **hashHid, tabelaHash **hashSem, tabelaHash **hashRad, tabelaHash **hashQuad) {
    char id[50];
    // Declaração variaveis para cada figura
    Hidrante h;
    Semaforo s;
    Radio r;
    Quadra q;

    sscanf(linhaArquivo,"del %s",id);

    // Verifica a qual figura pertence o id dado
    if ((h = getObjetoHash(*hashHid, id)) != NULL) {
        deleteNodeTree(*hidrante,h);
    } else if ((s = getObjetoHash(*hashSem, id)) != NULL) {
        deleteNodeTree(*semaforo,s);
    } else if ((r = getObjetoHash(*hashRad, id)) != NULL) {
        deleteNodeTree(*radio,r);
    } else if((q = getObjetoHash(*hashQuad, id)) != NULL) {
        deleteNodeTree(*quadra,r);
    }
}*/

void comandoCbq(char *linhaArquivo,char *saidaSvg,char *saidaTxt,struct tree **quadra,tabelaHash **hashQuad) {

}

int verificaQuadraDentroCirculo(double x,double y,double raio,Quadra q) {
    double xQuadra=0,yQuadra=0,hQuadra=0,wQuadra=0,distancia=0;
    double topLeftX,topRightX,bottomLeftX,bottomRightX,topLeftY,topRightY,bottomLeftY,bottomRightY;
    struct Quadra *tempQuadra = (struct Quadra*) q;

    xQuadra = getQuadraX(tempQuadra);
    yQuadra = getQuadraY(tempQuadra);
    hQuadra = getQuadraAltura(tempQuadra);
    wQuadra = getQuadraLargura(tempQuadra);

    topLeftX = x - xQuadra;
    topRightX = x - (xQuadra + wQuadra);
    bottomLeftX = x - xQuadra;
    bottomRightX = x - (xQuadra + wQuadra);

    topLeftY = y - yQuadra;
    topRightY = y - yQuadra;
    bottomLeftY = y - (yQuadra + hQuadra);
    bottomRightY = y - (yQuadra + hQuadra);

    distancia = sqrt((topLeftX*topLeftX) + (topLeftY*topLeftY));
    if(distancia < raio) {
        distancia = sqrt((topRightX*topRightX) + (topRightY*topRightY));
        if(distancia < raio) {
            distancia = sqrt((bottomLeftX*bottomLeftX) + (bottomLeftY*bottomLeftY));
            if(distancia < raio) {
                distancia = sqrt((bottomRightX*bottomRightX) + (bottomRightY*bottomRightY));
                if(distancia < raio) {
                    return 1;
                }
            }
        }
    }
    return 0;
}

void comandoCrd(char *linhaArquivo,char *saidaTxt,struct tree **hidrante, struct tree **semaforo, struct tree **radio, struct tree**quadra, tabelaHash **hashHid, tabelaHash **hashSem, tabelaHash **hashRad, tabelaHash **hashQuad) {
    char id[50];
    FILE *arquivoSaidaTxt = fopen(saidaTxt,"a+");
    // Declaração variaveis para cada figura
    Hidrante h;
    Semaforo s;
    Radio r;
    Quadra q;

    sscanf(linhaArquivo,"crd? %s",id);

    // Verifica a qual figura pertence o id dado
    if ((h = getObjetoHash(*hashHid, id)) != NULL) {
        fprintf(arquivoSaidaTxt,"%sHIDRANTE | X = %lf | Y = %lf\n",linhaArquivo,getHidranteX(h),getHidranteY(h));
    } else if ((s = getObjetoHash(*hashSem, id)) != NULL) {
        fprintf(arquivoSaidaTxt,"%sSEMAFORO | X = %lf | Y = %lf\n",linhaArquivo,getSemaforoX(s),getSemaforoY(s));
    } else if ((r = getObjetoHash(*hashRad, id)) != NULL) {
        fprintf(arquivoSaidaTxt,"%sRADIO | X = %lf | Y = %lf\n",linhaArquivo,getRadioX(r),getRadioY(r));
    } else if((q = getObjetoHash(*hashQuad, id)) != NULL) {
        fprintf(arquivoSaidaTxt,"%sQUADRA | X = %lf | Y = %lf\n",linhaArquivo,getQuadraX(q),getQuadraY(q));
    } else {
        fprintf(arquivoSaidaTxt,"%sFigura não encontrada\n",linhaArquivo);
    }

}

// COMANDOS T4

void comandoDmprbt(char* comandos, char* localSaida, struct tree **hidrante, struct tree **semaforo, struct tree **radio, struct tree**quadra, struct tree**predio, struct tree**muro) {
    char nomeArq[50], t, *temp1 = NULL;
    Quadra q;
    Hidrante h;
    Semaforo s;
    Radio r;
    Predio p;
    Muro m;
    sscanf(comandos, "dmprbt %c %s", &t, nomeArq);
    strcat(nomeArq, ".svg");
    temp1 = getArquivo(localSaida, nomeArq);

    iniciarSvg(temp1);

    if (t == 'q') {
        printTree(*quadra, temp1, printValorQuadra);
    } else if (t == 'h') {
        printTree(*hidrante, temp1, printValorHidrante);
    } else if (t == 's') {
        printTree(*semaforo, temp1, printValorSemaforo);
    } else if (t == 't') {
        printTree(*radio, temp1, printValorRadio);
    } else if (t == 'p') {
        printTree(*predio, temp1, printValorPredio);
    } else if (t == 'm') {
        printTree(*muro, temp1, printValorMuro);
    }
    finalizarSvg(temp1);

    free(temp1);
}

void comandoMoradores(char* comandos, char* nomeTxt, tabelaHash **hashQuad, tabelaHash **hashMor) {
    char id[50], result[500];
    int verifica = 0, tamQuadra = getTamHash(*hashQuad), tamMorador = getTamHash(*hashMor);
    Morador m;
    Quadra q;
    sscanf(comandos, "m? %s", id);
    escreverTextoTxt(nomeTxt, comandos);

    for (int i = 0; i < tamQuadra; i++) {
        listaHash n = getIndiceHash(*hashQuad, i);
        if (n != NULL) {
            listaHash aux = n;
            while (aux != NULL) {
                n = getProxHash(n);
                q = getObjetoHash2(aux);
                if (!strcmp(getQuadraId(q), id)) {
                    verifica = 1;
                }
                aux = n;
            }
        }
    }

    if (verifica == 1) {
        for (int i = 0; i < tamMorador; i++) {
            listaHash n = getIndiceHash(*hashMor, i);
            if (n != NULL) {
                listaHash aux = n;
                while (aux != NULL) {
                    n = getProxHash(n);
                    m = getObjetoHash2(aux);
                    if (!strcmp(getMoradorCep(m),id)) {
                        sprintf(result, "CPF: %s | Nome Completo: %s %s | Sexo: %s | Nascimento: %s | CEP: %s | Face: %c | Num: %d | Complemento: %s", getMoradorCpf(m), getMoradorNome(m), getMoradorSobrenome(m), getMoradorSexo(m) == 'M' ? "Masculino" : "Feminino", getMoradorNascimento(m), getMoradorCep(m), getMoradorFace(m), getMoradorNum(m), getMoradorCompl(m));
                        escreverTextoTxt(nomeTxt, result);
                        escreverTextoTxt(nomeTxt, "\n");
                    }
                    aux = n;
                }
            }
        }
    } else {
        escreverTextoTxt(nomeTxt, "Quadra não existente!");
        escreverTextoTxt(nomeTxt, "\n");
    }
    escreverTextoTxt(nomeTxt, "\n");
}

void comandoDm(char* comandos, char* nomeTxt, tabelaHash **hashMor) {
    char cpf[15], result[500];
    sscanf(comandos, "dm? %s", cpf);
    escreverTextoTxt(nomeTxt, comandos);
    Morador m = getObjetoHash(*hashMor, cpf);
    sprintf(result, "CPF: %s | Nome Completo: %s %s | Sexo: %s | Nascimento: %s | CEP: %s | Face: %c | Num: %d | Complemento: %s\n", getMoradorCpf(m), getMoradorNome(m), getMoradorSobrenome(m), getMoradorSexo(m) == 'M' ? "Masculino" : "Feminino", getMoradorNascimento(m), getMoradorCep(m), getMoradorFace(m), getMoradorNum(m), getMoradorCompl(m));
    escreverTextoTxt(nomeTxt, result);
    escreverTextoTxt(nomeTxt, "\n");
}

void comandoDe(char* comandos, char* nomeTxt, tabelaHash **hashEst) {
    char cnpj[19], result[500];
    sscanf(comandos, "de? %s", cnpj);
    escreverTextoTxt(nomeTxt, comandos);
    Estabelecimento e = getObjetoHash(*hashEst, cnpj);
    sprintf(result, "CNPJ: %s | Nome: %s | Descrição do tipo: %s | CEP: %s | Face: %c | Proprietario: %s %s| CPF: %s | Sexo: %s | Nascimento: %s\n", getEstabelecimentoCnpj(e), getEstabelecimentoNome(e), getEstabelecimentoDescricao(e), getEstabelecimentoCep(e), getEstabelecimentoFace(e), getEstabelecimentoProprietarioNome(e), getEstabelecimentoProprietarioSobrenome(e), getEstabelecimentoCpf(e), getEstabelecimentoProprietarioSexo(e) == 'M' ? "Masculino" : "Feminino", getEstabelecimentoProprietarioNascimento(e));
    escreverTextoTxt(nomeTxt, result);
    escreverTextoTxt(nomeTxt, "\n");
}

void comandoMud(char* comandos, char* nomeTxt, tabelaHash **hashMor) {
    char cpf[15], cep[50], face, compl[50], result[500];
    int num;
    sscanf(comandos, "mud %s %s %c %d %s", cpf, cep, &face, &num, compl);
    escreverTextoTxt(nomeTxt, comandos);
    Morador m = getObjetoHash(*hashMor, cpf);
    sprintf(result, "CPF: %s | Nome Completo: %s %s | Sexo: %s | Nascimento: %s | CEP Antigo: %s | Face Antiga: %c | Num Antigo: %d | Complemento Antigo: %s | CEP Novo: %s | Face Nova: %c | Num Novo: %d | Complemento Novo: %s", cpf, getMoradorNome(m), getMoradorSobrenome(m), getMoradorSexo(m) == 'M' ? "Masculino" : "Feminino", getMoradorNascimento(m), getMoradorCep(m), getMoradorFace(m), getMoradorNum(m), getMoradorCompl(m), cep, face, num, compl);
    setMoradorCep(m, cep);
    setMoradorFace(m, face);
    setMoradorNum(m, num);
    setMoradorCompl(m, compl);
    escreverTextoTxt(nomeTxt, result);
    escreverTextoTxt(nomeTxt, "\n");
}
