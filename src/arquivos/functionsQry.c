#include <stdio.h>
#include "../figuras/brl/segmento.h"
#include "../figuras/brl/vertice.h"
#include "../figuras/brl/ponto.h"
#include "../figuras/brl/lista.h"
#include <stdlib.h>
#include <string.h>
#include "functionsQry.h"
#include "../util/util.h"
#include "../svg/svg.h"
#include "../figuras/figuras.h"
#include "../figuras/estrutura/rbtree.h"
#include "../figuras/estrutura/hash.h"
#include <math.h>
#include <stdbool.h>
#define PI 3.1415

float xFoco, yFoco;
Segmento contOeste,contLeste,contSul,contNorte,contOesteB;

struct resultRet {
    float x, y, w, h;
};

// COMANDOS T1

resultRet verificaMaior(float y1m, float y2m, float x1m, float x2m, float y1, float y2, float x1, float x2) {
    float ry1, ry2, rx1, rx2, rh, rw;
    struct resultRet* resultado = (struct resultRet*) malloc(sizeof(struct resultRet));
    if (y1m < y2m) ry1 = y1m;
    else ry1 = y2m;
    if (x1m < x2m) rx1 = x1m;
    else rx1 = x2m;
    if (y1 > y2) ry2 = y1;
    else ry2 = y2;
    if (x1 > x2) rx2 = x1;
    else rx2 = x2;
    rh = ry2 - ry1;
    rw = rx2 - rx1;
    resultado->x = rx1;
    resultado->y = ry1;
    resultado->w = rw;
    resultado->h = rh;
    return (void*) resultado;
}

int sobreTeste(float x1, float x2, float y1, float y2, float w, float h, float r) {
    float distX, distY, dx, dy;
    distX = abs(x1 - x2-w);
    distY = abs(y1 - y2-h);
    if (distX > (w + r)) return 0;
    if (distY > (h + r)) return 0;
    if (distX <= w) return 1;
    if (distY <= h) return 1;
    dx = distX - w;
    dy = distY - h;
    if(dx*dx+dy*dy <= (r*r)) return 1;
    else return 0;
}

void comandoOverlap(char *linhaArquivo,char *saidaSvg,char *saidaTxt,tabelaHash **hashCirc,tabelaHash **hashRet) {
    char id1[20],id2[20];
    int c = 0;
    float x1, x2, y1, y2, raio1, raio2, w1, w2, h1, h2, dist;
    FILE *arquivoSaidaSvg = NULL;

    arquivoSaidaSvg = fopen(saidaSvg,"a+");

    if(arquivoSaidaSvg == NULL) {
        printf("Erro ao abrir arquivo\n");
        exit(0);
    }

    sscanf(linhaArquivo,"o? %s %s",id1,id2);
    escreverTextoTxt(saidaTxt, linhaArquivo);

    Circulo c1;
    Circulo c2;
    Retangulo r1;
    Retangulo r2;
    struct resultRet* resultado = NULL;

    if((c1 = getObjetoHash(*hashCirc,id1)) != NULL) {
        x1 = getCirculoX(c1);
        y1 = getCirculoY(c1);
        raio1 = getCirculoRaio(c1);
        if((c2 = getObjetoHash(*hashCirc,id2)) != NULL) {
            x2 = getCirculoX(c2);
            y2 = getCirculoY(c2);
            raio2 = getCirculoRaio(c2);
            dist = dist = sqrt(pow((x2 - x1), 2) + pow((y2 - y1), 2));
            resultado = (struct resultRet*) verificaMaior(y1-raio1, y2-raio2, x1-raio1, x2-raio2, y1+raio1, y2+raio2, x1+raio1, x2+raio2);
            if (dist > (raio1 + raio2)) c = 0;
            else c = 1;
        } else {
            r2 = getObjetoHash(*hashRet,id2);
            x2 = getRetanguloX(r2);
            y2 = getRetanguloY(r2);
            w2 = getRetanguloLargura(r2)/2;
            h2 = getRetanguloAltura(r2)/2;
            resultado = (struct resultRet*) verificaMaior(y1-raio1, y2, x1-raio1, x2, y1+raio1, y2+h2*2, x1+raio1, x2+w2*2);
            if (sobreTeste(x1, x2, y1, y2, w2, h2, raio1) == 0) c = 0;
            else c = 1;
        }
    } else {
        r1 = getObjetoHash(*hashRet,id1);
        x1 = getRetanguloX(r1);
        y1 = getRetanguloY(r1);
        h1 = getRetanguloAltura(r1)/2;
        w1 = getRetanguloLargura(r1)/2;
        if((c2 = getObjetoHash(*hashCirc,id2)) != NULL) {
            x2 = getCirculoX(c2);
            y2 = getCirculoY(c2);
            raio2 = getCirculoRaio(c2);
            resultado = (struct resultRet*) verificaMaior(y1, y2-raio2, x1, x2-raio2, y1+h1*2, y2+raio2, x1+w1*2, x2+raio2);
            if (sobreTeste(x2, x1, y2, y1, w1, h1, raio2) == 0) c = 0;
            else c = 1;
        } else {
            r2 = getObjetoHash(*hashRet,id2);
            x2 = getRetanguloX(r2);
            y2 = getRetanguloY(r2);
            w2 = getRetanguloLargura(r2)/2;
            h2 = getRetanguloAltura(r2)/2;
            w1 *= 2; h1 *= 2; w2 *= 2; h2 *= 2;
            resultado = (struct resultRet*) verificaMaior(y1, y2, x1, x2, y1+h1, y2+h2, x1+w1, x2+w2);
            if ((x1+w1 >= x2) && (x1<=x2+w2) && (y1+h1 >= y2) && (y1 <= y2+h2)) c = 1;
            else c = 0;
        }
    }

    if (c) {
        escreverTextoTxt(saidaTxt, "SIM\n\n");
        fprintf(arquivoSaidaSvg, "<rect x='%.2lf' y='%.2lf' width='%.2lf' height='%.2lf' stroke-width='1' stroke='red' fill-opacity='0.0' fill='blue' />\n", resultado->x, resultado->y, resultado->w, resultado->h);
        free(resultado);
    } else {
        escreverTextoTxt(saidaTxt, "NAO\n\n");
        fprintf(arquivoSaidaSvg, "<rect x='%.2lf' y='%.2lf' width='%.2lf' height='%.2lf' stroke-dasharray='5,5' stroke-width='1' stroke='red' fill-opacity='0.0' fill='blue' />\n", resultado->x, resultado->y, resultado->w, resultado->h);
        free(resultado);
    }

    fclose(arquivoSaidaSvg);
}

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


void comandoBB(char *linhaArquivo,char *localSaida,char *pGeo,char *pQry, struct tree **circulo, struct tree **retangulo, tabelaHash **hashCirc, tabelaHash **hashRet) {
    char cor[30], sufixo[50], *saidaSvg = NULL;
    int tamCirc = getTamHash(*hashCirc), tamRet = getTamHash(*hashRet);
    double x1, y1, raio, x, y, w, h;
    FILE *arqSvg;
    sscanf(linhaArquivo, "bb %s %s", sufixo, cor);
    saidaSvg = getSvgSaidaBB(localSaida, pGeo, pQry, sufixo);
    iniciarSvg(saidaSvg);
    arqSvg = fopen(saidaSvg, "a+");
    treeToSvg(*circulo, saidaSvg);
    treeToSvg(*retangulo, saidaSvg);
    Circulo c;
    Retangulo r;

    for (int i = 0; i < tamCirc; i++) {
        listaHash n = getIndiceHash(*hashCirc, i);
        if (n != NULL) {
            listaHash aux = n;
            while (aux != NULL) {
                n = getProxHash(n);
                c = getObjetoHash2(aux);
                x1 = getCirculoX(c);
                y1 = getCirculoY(c);
                raio = getCirculoRaio(c);
                x = x1 - raio;
                y = y1 - raio;
                w = (x1 + raio) - (x1 - raio);
                h = (y1 + raio) - (y1 - raio);
                fprintf(arqSvg,"\t<rect x='%lf' y='%lf' width='%lf' height='%lf' stroke='%s' fill='%s' stroke-width='1'/>\n", x, y, w, h, cor, cor);
                aux = n;
            }
        }
    }

    for (int i = 0; i < tamRet; i++) {
        listaHash n = getIndiceHash(*hashRet, i);
        if (n != NULL) {
            listaHash aux = n;
            while (aux != NULL) {
                n = getProxHash(n);
                r = getObjetoHash2(aux);
                x1 = getRetanguloX(r);
                y1 = getRetanguloY(r);
                w = getRetanguloLargura(r);
                h = getRetanguloAltura(r);
                x = x1 + w;
                y = y1 + h;
                fprintf(arqSvg, "<ellipse cx='%f' cy='%f' rx='%f' ry='%f' stroke='%s' fill='%s' />\n", x, y, w, h, cor, cor);
                aux = n;
            }
        }
    }

    fclose(arqSvg);
    finalizarSvg(saidaSvg);
    free(saidaSvg);
}


void comandoDq (char* comandos, char* nomeSvg, char* nomeTxt, struct tree **hidrante, struct tree **semaforo, struct tree **radio, struct tree**quadra, tabelaHash **hashHid, tabelaHash **hashSem, tabelaHash **hashRad, tabelaHash **hashQuad) {
    FILE *arqSvg = fopen(nomeSvg, "a+");
    char metrica[3], id[50], result[100];
    double dist1, dist2, x1, y1, x2, y2, w1, h1;
    int tam;
    sscanf(comandos, "dq %s %s %lf", metrica, id, &dist1);
    escreverTextoTxt(nomeTxt, comandos);

    Hidrante h;
    Semaforo s;
    Radio r;
    Quadra q;

    if ((h = getObjetoHash(*hashHid, id)) != NULL) {
        x2 = getHidranteX(h);
        y2 = getHidranteY(h);
        sprintf(result, "TIPO: HIDRANTE; X: %f; Y: %f", x2, y2);
    } else if ((s = getObjetoHash(*hashSem, id)) != NULL) {
        x2 = getSemaforoX(s);
        y2 = getSemaforoY(s);
        sprintf(result, "TIPO: SEMAFORO; X: %f; Y: %f", x2, y2);
    } else if ((r = getObjetoHash(*hashRad, id)) != NULL) {
        x2 = getRadioX(r);
        y2 = getRadioY(r);
        sprintf(result, "TIPO: TORRE DE CELULAR; X: %f; Y: %f", x2, y2);
    }
    fprintf(arqSvg,"\t<circle r='20' cx='%lf' cy='%lf' stroke='red' fill='blue' stroke-width='5'/>\n",x2, y2);
    escreverTextoTxt(nomeTxt, result);
    escreverTextoTxt(nomeTxt, "\nQUADRAS REMOVIDAS:");
    tam = getTamHash(*hashQuad);

    if (strcmp(metrica, "L1") == 0) {
        for (int i = 0; i < tam; i++) {
    		listaHash n = getIndiceHash(*hashQuad, i);
    		if (n != NULL) {
    			listaHash aux = n;
    			while (aux != NULL) {
    				n = getProxHash(n);
                    q = getObjetoHash2(aux);
                    x1 = getQuadraX(q);
                    y1 = getQuadraY(q);
                    h1 = getQuadraAltura(q);
                    w1 = getQuadraLargura(q);
                    if ((fabs(x2 - x1) + fabs(y2 - y1)) <= dist1 && (fabs(x2 - (x1+w1)) + fabs(y2 - y1)) <= dist1 && (fabs(x2 - x1) + fabs(y2 - (y1+h1))) <= dist1 && (fabs(x2 - (x1+w1)) + fabs(y2 - (y1+h1))) <= dist1) {
                        escreverTextoTxt(nomeTxt, getQuadraId(q));
                        escreverTextoTxt(nomeTxt, "; ");
                        removerObjetoHash(*hashQuad, getQuadraId(q));
                        q = findTree(*quadra, q);
                        deleteNodeTree(*quadra, q);
                    }
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
                    q = getObjetoHash2(aux);
                    x1 = getQuadraX(q);
                    y1 = getQuadraY(q);
                    h1 = getQuadraAltura(q);
                    w1 = getQuadraLargura(q);
                    if ((sqrt(pow((x2 - x1), 2) + pow((y2 - y1), 2))) <= dist1 && (sqrt(pow((x2 - (x1+w1)), 2) + pow((y2 - y1), 2))) <= dist1 && (sqrt(pow((x2 - x1), 2) + pow((y2 - (y1+h1)), 2))) <= dist1 && (sqrt(pow((x2 - (x1+w1)), 2) + pow((y2 - (y1+h1)), 2))) <= dist1) {
                        escreverTextoTxt(nomeTxt, getQuadraId(q));
                        escreverTextoTxt(nomeTxt, "; ");
                        removerObjetoHash(*hashQuad, getQuadraId(q));
                        q = findTree(*quadra, q);
                        deleteNodeTree(*quadra, q);
                    }
    				aux = n;
    			}
    		}
        }
    }
    escreverTextoTxt(nomeTxt, "\n\n");
    fclose(arqSvg);
}

void comandoDel(char *linhaArquivo,char *saidaSvg,char *saidaTxt,struct tree **hidrante, struct tree **semaforo, struct tree **radio, struct tree**quadra, tabelaHash **hashHid, tabelaHash **hashSem, tabelaHash **hashRad, tabelaHash **hashQuad) {
    char id[50], result[100];
    sscanf(linhaArquivo, "del %s", id);
    escreverTextoTxt(saidaTxt, linhaArquivo);
    Hidrante h;
    Semaforo s;
    Radio r;
    Quadra q;
    if ((q = getObjetoHash(*hashQuad, id)) != NULL) {
        sprintf(result, "TIPO: QUADRA; X: %lf; Y: %lf", getQuadraX(q), getQuadraY(q));
        removerObjetoHash(*hashQuad, getQuadraId(q));
        q = findTree(*quadra, q);
        deleteNodeTree(*quadra, q);
    } else if ((h = getObjetoHash(*hashHid, id)) != NULL) {
        sprintf(result, "TIPO: HIDRANTE; X: %lf; Y: %lf", getHidranteX(h), getHidranteY(h));
        removerObjetoHash(*hashHid, getHidranteId(h));
        h = findTree(*hidrante, h);
        deleteNodeTree(*hidrante, h);
    } else if ((s = getObjetoHash(*hashSem, id)) != NULL) {
        sprintf(result, "TIPO: SEMAFORO; X: %lf; Y: %lf", getSemaforoX(s), getSemaforoY(s));
        removerObjetoHash(*hashSem, getSemaforoId(s));
        s = findTree(*semaforo, s);
        deleteNodeTree(*semaforo, s);
    } else if ((r = getObjetoHash(*hashRad, id)) != NULL) {
        sprintf(result, "TIPO: TORRE DE CELULAR; X: %lf; Y: %lf", getRadioX(r), getRadioY(r));
        removerObjetoHash(*hashRad, getRadioId(r));
        r = findTree(*radio, r);
        deleteNodeTree(*radio, r);
    }
    escreverTextoTxt(saidaTxt, result);
    escreverTextoTxt(saidaTxt, "\n\n");
}

void comandoCbq(char *linhaArquivo,char *saidaSvg,char *saidaTxt,struct tree **quadra,tabelaHash **hashQuad) {
    char cstrk[50];
    int tam = getTamHash(*hashQuad);
    double x, y, r;
    Quadra q;
    sscanf(linhaArquivo, "cbq %lf %lf %lf %s", &x, &y, &r, cstrk);
    escreverTextoTxt(saidaTxt, linhaArquivo);
    escreverTextoTxt(saidaTxt, "QUADRAS COM BORDA ALTERADA: ");

    for (int i = 0; i < tam; i++) {
        listaHash n = getIndiceHash(*hashQuad, i);
        if (n != NULL) {
            listaHash aux = n;
            while (aux != NULL) {
                n = getProxHash(n);
                q = getObjetoHash2(aux);
                if (verificaQuadraDentroCirculo(x, y, r, q)) {
                    setQuadraCstrk(q, cstrk);
                    escreverTextoTxt(saidaTxt, getQuadraId(q));
                    escreverTextoTxt(saidaTxt, "; ");
                }
                aux = n;
            }
        }
    }
    escreverTextoTxt(saidaTxt, "\n\n");
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
    Hidrante h;
    Semaforo s;
    Radio r;
    Quadra q;

    sscanf(linhaArquivo,"crd? %s",id);

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

void comandoTrns(char *comandos, char *nomeSvg, char *nomeTxt, tabelaHash **hashQuad, tabelaHash **hashHid, tabelaHash **hashSem, tabelaHash **hashRad) {
    char result[100];
    double x1, x2, y1, y2, w1, w2, h1, h2, r1, dx, dy;
    int tamQuad = getTamHash(*hashQuad), tamHid = getTamHash(*hashHid), tamSem = getTamHash(*hashSem), tamRad = getTamHash(*hashRad);
    sscanf(comandos, "trns %lf %lf %lf %lf %lf %lf", &x2, &y2, &w2, &h2, &dx, &dy);
    escreverTextoTxt(nomeTxt, comandos);
    escreverTextoTxt(nomeTxt, "QUADRAS E EQUIPAMENTOS MOVIDOS:");

    Hidrante h;
    Semaforo s;
    Radio r;
    Quadra q;

    for (int i = 0; i < tamQuad; i++) {
        listaHash n = getIndiceHash(*hashQuad, i);
        if (n != NULL) {
            listaHash aux = n;
            while (aux != NULL) {
                n = getProxHash(n);
                q = getObjetoHash2(aux);
                x1 = getQuadraX(q);
                y1 = getQuadraY(q);
                w1 = getQuadraLargura(q);
                h1 = getQuadraAltura(q);
                if (x1 >= x2 && y1 >= y2 && x1+w1 <= x2+w2 && y1+h1 <= y2+h2) {
                    sprintf(result, "CEP: %s; X ANTIGO: %f; Y ANTIGO: %f; X NOVO: %f; Y NOVO: %f; ", getQuadraId(q), x1, y1, x1+dx, y1+dy);
                    escreverTextoTxt(nomeTxt, result);
                    setQuadraX(q, x1+dx);
                    setQuadraY(q, y1+dy);
                }
                aux = n;
            }
        }
    }

    for (int i = 0; i < tamHid; i++) {
        listaHash n = getIndiceHash(*hashHid, i);
        if (n != NULL) {
            listaHash aux = n;
            while (aux != NULL) {
                n = getProxHash(n);
                h = getObjetoHash2(aux);
                x1 = getHidranteX(h);
                y1 = getHidranteY(h);
                r1 = 3;
                if (x1-r1 >= x2 && y1-r1 >= y2 && x1+r1 <= x2+w2 && y1+r1 <= y2+h2) {
                    sprintf(result, "ID: %s; X ANTIGO: %f; Y ANTIGO: %f; X NOVO: %f; Y NOVO: %f; ", getHidranteId(h), x1, y1, x1+dx, y1+dy);
                    escreverTextoTxt(nomeTxt, result);
                    setHidranteX(h, x1+dx);
                    setHidranteY(h, y1+dy);
                }
                aux = n;
            }
        }
    }

    for (int i = 0; i < tamSem; i++) {
        listaHash n = getIndiceHash(*hashSem, i);
        if (n != NULL) {
            listaHash aux = n;
            while (aux != NULL) {
                n = getProxHash(n);
                s = getObjetoHash2(aux);
                x1 = getSemaforoX(s);
                y1 = getSemaforoY(s);
                r1 = 5;
                if (x1-r1 >= x2 && y1-r1 >= y2 && x1+r1 <= x2+w2 && y1+r1 <= y2+h2) {
                    sprintf(result, "ID: %s; X ANTIGO: %f; Y ANTIGO: %f; X NOVO: %f; Y NOVO: %f; ", getSemaforoId(s), x1, y1, x1+dx, y1+dy);
                    escreverTextoTxt(nomeTxt, result);
                    setHidranteX(s, x1+dx);
                    setHidranteY(s, y1+dy);
                }
                aux = n;
            }
        }
    }

    for (int i = 0; i < tamRad; i++) {
        listaHash n = getIndiceHash(*hashRad, i);
        if (n != NULL) {
            listaHash aux = n;
            while (aux != NULL) {
                n = getProxHash(n);
                r = getObjetoHash2(aux);
                x1 = getRadioX(r);
                y1 = getRadioY(r);
                r1 = 7;
                if (x1-r1 >= x2 && y1-r1 >= y2 && x1+r1 <= x2+w2 && y1+r1 <= y2+h2) {
                    sprintf(result, "ID: %s; X ANTIGO: %f; Y ANTIGO: %f; X NOVO: %f; Y NOVO: %f; ", getRadioId(h), x1, y1, x1+dx, y1+dy);
                    escreverTextoTxt(nomeTxt, result);
                    setRadioX(r, x1+dx);
                    setRadioY(r, y1+dy);
                }
                aux = n;
            }
        }
    }
    escreverTextoTxt(nomeTxt, "\n\n");
}

// COMANDOS T3

void peneira(float *vet, int raiz, int fundo) {
    int pronto, filhoMax;
    float tmp;

	pronto = 0;
	while ((raiz*2 <= fundo) && (!pronto)) {
		if (raiz*2 == fundo) {
			filhoMax = raiz * 2;
		} else if (vet[raiz * 2] > vet[raiz * 2 + 1]) {
			filhoMax = raiz * 2;
		} else {
			filhoMax = raiz * 2 + 1;
		}
	    if (vet[raiz] < vet[filhoMax]) {
		    tmp = vet[raiz];
		    vet[raiz] = vet[filhoMax];
		    vet[filhoMax] = tmp;
		    raiz = filhoMax;
        } else {
            pronto = 1;
        }
    }
}

void peneira2(float *vet, int raiz, int fundo) {
    int pronto, filhoMax;
    float tmp;

	pronto = 0;
	while ((raiz*2 <= fundo) && (!pronto)) {
		if (raiz*2 == fundo) {
			filhoMax = raiz * 2;
		} else if (vet[raiz * 2] < vet[raiz * 2 + 1]) {
			filhoMax = raiz * 2;
		} else {
			filhoMax = raiz * 2 + 1;
		}
	    if (vet[raiz] > vet[filhoMax]) {
		    tmp = vet[raiz];
		    vet[raiz] = vet[filhoMax];
		    vet[filhoMax] = tmp;
		    raiz = filhoMax;
        } else {
            pronto = 1;
        }
    }
}

void heapSort(float *vet, int n, bool ref) {
	int i;
    float tmp;

    if (ref) { //crescente
        for (i = (n / 2); i >= 0; i--) {
            peneira(vet, i, n - 1);
        }
        for (i = n-1; i >= 1; i--) {
            tmp = vet[0];
            vet[0] = vet[i];
            vet[i] = tmp;
            peneira(vet, 0, i-1);
        }
    } else { //decrescente
        for (i = (n / 2); i >= 0; i--) {
            peneira2(vet, i, n - 1);
        }
        for (i = n-1; i >= 1; i--) {
            tmp = vet[0];
            vet[0] = vet[i];
            vet[i] = tmp;
            peneira2(vet, 0, i-1);
        }
    }
}

void comandoFi(char *comandos, char* saidaSvg, char* saidaTxt, tabelaHash **hashSem, tabelaHash **hashHid) {
    float x1, x2, y1, y2, r, *dist;
    int ns, tamanho, l = 0, tamHid = getTamHash(*hashHid);
    char verificaIgual[100];
    FILE *arqSvg = fopen(saidaSvg, "a+");
    sscanf(comandos, "fi %f %f %d %f", &x2, &y2, &ns, &r);
    escreverTextoTxt(saidaTxt, comandos);
    escreverTextoTxt(saidaTxt, "Semaforos:");
    tamanho = getTamHash(*hashSem);
    dist = malloc(sizeof(float)* (tamanho));
    strcpy(verificaIgual, "");
    Semaforo s;
    Hidrante h;
    fprintf(arqSvg, "<polygon points='%f,%f %f,%f %f,%f' fill='orangered' stroke='yellow' stroke-width='1'/>\n", x2, y2-10, x2-10, y2+10, x2+10, y2+10);
    for (int i = 0; i < tamanho; i++) {
        listaHash n = getIndiceHash(*hashSem, i);
        if (n != NULL) {
            listaHash aux = n;
            while (aux != NULL) {
                n = getProxHash(n);
                s = getObjetoHash2(aux);
                x1 = getSemaforoX(s);
                y1 = getSemaforoY(s);
                dist[l] = sqrt(pow((x2 - x1), 2) + pow((y2 - y1), 2));
                l++;
                aux = n;
            }
        }
    }
    heapSort(dist, l, true);
    for(int k=0;k<ns;k++) {
        for (int i = 0; i < tamanho; i++) {
            listaHash n = getIndiceHash(*hashSem, i);
            if (n != NULL) {
                listaHash aux = n;
                while (aux != NULL) {
                    n = getProxHash(n);
                    s = getObjetoHash2(aux);
                    x1 = getSemaforoX(s);
                    y1 = getSemaforoY(s);
                    if (((int) (dist[k]*100)) == ((int)(sqrt(pow((x2 - x1), 2) + pow((y2 - y1), 2))*100))) {
                        if (strcmp(verificaIgual, getSemaforoId(s))) {
                            escreverTextoTxt(saidaTxt, getSemaforoId(s));
                            escreverTextoTxt(saidaTxt, ", ");
                            fprintf(arqSvg,"\t<circle r='15' cx='%lf' cy='%lf' stroke='black' fill='green' stroke-width='1'/>\n",getSemaforoX(s), getSemaforoY(s));
                            desenharLinha(saidaSvg, x1, x2, y1, y2);
                            strcpy(verificaIgual, getSemaforoId(s));
                            break;
                        }
                    }
                    aux = n;
                }
            }
        }
    }
    escreverTextoTxt(saidaTxt, "\nHidrantes:");
    for (int i = 0; i < tamHid; i++) {
        listaHash n = getIndiceHash(*hashHid, i);
        if (n != NULL) {
            listaHash aux = n;
            while (aux != NULL) {
                n = getProxHash(n);
                h = getObjetoHash2(aux);
                x1 = getHidranteX(h);
                y1 = getHidranteY(h);
                if ((sqrt(pow((x2 - x1), 2) + pow((y2 - y1), 2))) <= r) {
                    escreverTextoTxt(saidaTxt, getHidranteId(h));
                    escreverTextoTxt(saidaTxt, ", ");
                    fprintf(arqSvg,"\t<circle r='15' cx='%lf' cy='%lf' stroke='black' fill='green' stroke-width='1'/>\n",getHidranteX(h), getHidranteY(h));
                    desenharLinha(saidaSvg, x1, x2, y1, y2);
                }
                aux = n;
            }
        }
    }
    free(dist);
    escreverTextoTxt(saidaTxt, "\n\n");
    fclose(arqSvg);

}

void comandoFh(char *comandos, char* saidaSvg, char* saidaTxt, tabelaHash **hashHid, tabelaHash **hashPrd) {
    int k, num, l = 0, tamHid = getTamHash(*hashHid), tamPrd = getTamHash(*hashPrd);
    float *dist, x1, x2, y1, y2;
    char cep[100], face, ref, verificaIgual[100], id[100];
    Hidrante h;
    Predio p;
    FILE *arqSvg = fopen(saidaSvg, "a+");
    sscanf(comandos, "fh %c%d %s %c %d", &ref, &k, cep, &face, &num);
    dist = malloc(sizeof(float)* (tamHid));
    strcpy(verificaIgual, "");
    escreverTextoTxt(saidaTxt, comandos);
    sprintf(id, "%s%c%d", cep, face, num);

    p = getObjetoHash(*hashPrd, id);
    x2 = getPredioTexX(p);
    y2 = getPredioTexY(p);
    for (int i = 0; i < tamHid; i++) {
        listaHash n = getIndiceHash(*hashHid, i);
        if (n != NULL) {
            listaHash aux = n;
            while (aux != NULL) {
                n = getProxHash(n);
                h = getObjetoHash2(aux);
                x1 = getHidranteX(h);
                y1 = getHidranteY(h);
                dist[l] = sqrt(pow((x2 - x1), 2) + pow((y2 - y1), 2));
                l++;
                aux = n;
            }
        }
    }
    if (ref == '-') heapSort(dist, l, true);
    else if (ref == '+') heapSort(dist, l, false);

    for (int j=0;j<k;j++) {
        for (int i = 0; i < tamHid; i++) {
            listaHash n = getIndiceHash(*hashHid, i);
            if (n != NULL) {
                listaHash aux = n;
                while (aux != NULL) {
                    n = getProxHash(n);
                    h = getObjetoHash2(aux);
                    x1 = getHidranteX(h);
                    y1 = getHidranteY(h);
                    if (((int) (dist[j]*100)) == ((int)(sqrt(pow((x2 - x1), 2) + pow((y2 - y1), 2))*100))) {
                        if (strcmp(verificaIgual, getHidranteId(h))) {
                            escreverTextoTxt(saidaTxt, getHidranteId(h));
                            escreverTextoTxt(saidaTxt, ", ");
                            fprintf(arqSvg,"\t<circle r='15' cx='%lf' cy='%lf' stroke='black' fill='green' stroke-width='1'/>\n",getHidranteX(h), getHidranteY(h));
                            desenharLinha(saidaSvg, x1, x2, y1, y2);
                            strcpy(verificaIgual, getHidranteId(h));
                            break;
                        }
                    }
                    aux = n;
                }
            }
        }
    }
    free(dist);
    escreverTextoTxt(saidaTxt, "\n");
    fclose(arqSvg);
}

void comandoFs(char *comandos, char* saidaSvg, char* saidaTxt, tabelaHash **hashSem, tabelaHash **hashPrd) {
    int k, num, l = 0, tamanho = getTamHash(*hashSem), teste;
    float x1, x2, y1, y2, h1, h2, *dist;
    char cep[100], face, verificaIgual[100], id[100];
    FILE *arqSvg = fopen(saidaSvg, "a+");
    sscanf(comandos, "fs %d %s %c %d", &k, cep, &face, &num);
    Semaforo s;
    Predio p;
    dist = malloc(sizeof(float)* (tamanho));
    strcpy(verificaIgual, "");
    escreverTextoTxt(saidaTxt, comandos);
    sprintf(id, "%s%c%d", cep, face, num);

    p = getObjetoHash(*hashPrd, id);
    x2 = getPredioTexX(p);
    y2 = getPredioTexY(p);
    for (int i = 0; i < tamanho; i++) {
        listaHash n = getIndiceHash(*hashSem, i);
        if (n != NULL) {
            listaHash aux = n;
            while (aux != NULL) {
                n = getProxHash(n);
                s = getObjetoHash2(aux);
                x1 = getSemaforoX(s);
                y1 = getSemaforoY(s);
                dist[l] = sqrt(pow((x2 - x1), 2) + pow((y2 - y1), 2));
                l++;
                aux = n;
            }
        }
    }
    heapSort(dist, l, true);
    for (int j=0;j<k;j++) {
        for (int i = 0; i < tamanho; i++) {
            listaHash n = getIndiceHash(*hashSem, i);
            if (n != NULL) {
                listaHash aux = n;
                while (aux != NULL) {
                    n = getProxHash(n);
                    s = getObjetoHash2(aux);
                    x1 = getSemaforoX(s);
                    y1 = getSemaforoY(s);
                    if (((int) (dist[j]*100)) == ((int)(sqrt(pow((x2 - x1), 2) + pow((y2 - y1), 2))*100))) {
                        if (strcmp(verificaIgual, getSemaforoId(s))) {
                            escreverTextoTxt(saidaTxt, getSemaforoId(s));
                            escreverTextoTxt(saidaTxt, ", ");
                            fprintf(arqSvg,"\t<circle r='15' cx='%lf' cy='%lf' stroke='black' fill='green' stroke-width='1'/>\n",getSemaforoX(s), getSemaforoY(s));
                            desenharLinha(saidaSvg, x1, x2, y1, y2);
                            strcpy(verificaIgual, getSemaforoId(s));
                            break;
                        }
                    }
                    aux = n;
                }
            }
        }
    }
    free(dist);
    fclose(arqSvg);

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

void comandoMplg(char *comandos, char* nomeTxt, tabelaHash **hashMor) {

}

void comandoEplg(char *comandos, char* nomeTxt, tabelaHash **hashMor) {

}

void comandoCatac(char *comandos, char* nomeTxt, tabelaHash **hashMor) {
    
}


// BRL & BRN
double distancia(double x1, double y1, double x2, double y2) {
    return sqrt(pow(x2-x1,2)+pow(y2-y1,2));
}

int lado(Ponto A, Ponto B, Ponto C) {
    int S;
    S = getXPonto(A)*getYPonto(C) - getYPonto(A)*getXPonto(C) + getYPonto(A)*getXPonto(B)
        - getXPonto(A)*getYPonto(B) + getXPonto(C)*getYPonto(B) - getYPonto(C)*getXPonto(B);

    if(S<0) return -1;
    else if(S>0) return 1;
    else return 0;
}

double min(double vet[], int size) {
    double minimo = vet[0];
    for(int i=1;i<size;i++){
        if(vet[i]<minimo)
            minimo=vet[i];
    }
    return minimo;
}

double max(double vet[], int size) {
    double maximo = vet[0];
    for(int i=1;i<size;i++){
        if(vet[i]>maximo)
            maximo=vet[i];
    }
    return maximo;
}

int seInterceptam(Ponto A, Ponto B, Ponto C, Ponto D) {
    int abc,abd,cda,cdb;

    abc = lado(A,B,C);
    abd = lado(A,B,D);
    cda = lado(C,D,A);
    cdb = lado(C,D,B);

    return ((abc*abd<=0) && (cda*cdb<=0));
}

Ponto intersectionLines(Ponto A1, Ponto A2, Ponto B1, Ponto B2) {
    double m1, c1, m2, c2;
    double dx1, dy1,dx2, dy2;
    double intersection_X, intersection_Y;

    double Ax1 = getXPonto(A1);
    double Ay1 = getYPonto(A1);
    double Ax2 = getXPonto(A2);
    double Ay2 = getYPonto(A2);

    double Bx1 = getXPonto(B1);
    double By1 = getYPonto(B1);
    double Bx2 = getXPonto(B2);
    double By2 = getYPonto(B2);


    dx1 = Ax2 - Ax1;

    dy1 = Ay2 - Ay1;

    if(dx1==0){
        m1=0;
        Ay1=0;
    }
    else m1 = dy1 / dx1;

    c1 = Ay1 - m1 * Ax1;

    dx2 = Bx2 - Bx1;
    dy2 = By2 - By1;

    if(dx2==0){
        m2=0;
        By1=0;
    }
    else m2 = dy2 / dx2;
    c2 = By1 - m2 * Bx1;

    if( (m1 - m2) == 0 && m1!=0 && m2!=0){
        printf("No Intersection between the lines\n");
        return NULL;
    }else{
        if(dx1==0){
            intersection_X=Ax1;
            intersection_Y = m2 * intersection_X+c2;
        }
        else if(dx2==0){
            intersection_X=Bx1;
            intersection_Y = m1 * intersection_X+c1;
        }else{
            intersection_X = (c2 - c1) / (m1 - m2);
            intersection_Y = m1 * intersection_X + c1;
        }

        double Xs[4] = {Ax1,Ax2,Bx1,Bx2};
        double Ys[4] = {Ay1,Ay2,By1,By2};

        double minX=min(Xs,4);
        double maxX=max(Xs,4);
        double minY=min(Ys,4);
        double maxY=max(Ys,4);

       if((intersection_X > minX-100 || AreSame(intersection_X , minX)) && (intersection_X < maxX+100 || AreSame(intersection_X,maxX)) && (intersection_Y > minY-100 || AreSame(intersection_Y,minY)) && (intersection_Y < maxY+100 || AreSame(intersection_Y,maxY))){
            return criaPonto(intersection_X,intersection_Y);
        }else
        {
            return NULL;
        }

    }
}

int AreSame(double a, double b) {
    return fabs(a - b) < __DBL_EPSILON__;
}

int isEqual(Ponto A, Ponto B) {
    if(AreSame(getXPonto(A),getXPonto(B)) && AreSame(getYPonto(A),getYPonto(B)))
        return 1;
    else return 0;
}

Ponto pontoIntersecao(Ponto A, Ponto B, Ponto C, Ponto D) {
    double s, t,denom;
    if(!seInterceptam(A,B,C,D))
        return NULL;

    denom = ((getYPonto(B) - getYPonto(A)) * (getXPonto(D) - getXPonto(C)) - (getYPonto(D) - getYPonto(C)) * (getXPonto(B) - getXPonto(A)));
    if(denom == 0)
        return NULL;


    s = (getXPonto(A) * (getYPonto(D)-getYPonto(C)) + getXPonto(C)*(getYPonto(A)-getYPonto(D)) + getXPonto(D)*(getYPonto(C)-getYPonto(A)))/denom;

    t = - (getXPonto(A) * (getYPonto(C)-getYPonto(B)) + getXPonto(B)*(getYPonto(A)-getYPonto(C)) + getXPonto(C)*(getYPonto(B)-getYPonto(A)))/denom;

    if(s>=0 && s<=1 && t>=0 && t<=1){
        return criaPonto(getXPonto(A)+s*(getXPonto(B)-getXPonto(A)),getYPonto(A)+s*(getYPonto(B)-getYPonto(A)));
    } else return NULL;
}

int seInterceptamProprio(Ponto A, Ponto B, Ponto C, Ponto D) {
    int abc,abd,cda,cdb;

    abc = lado(A,B,C);
    abd = lado(A,B,D);
    cda = lado(C,D,A);
    cdb = lado(C,D,B);

    return ((abc*abd<0) && (cda*cdb<0));
}

Ponto pontoIntersecaoProprio(Ponto A, Ponto B, Ponto C, Ponto D) {
    double s, t,denom;
    if(!seInterceptamProprio(A,B,C,D))
        return NULL;

    denom = ((getYPonto(B) - getYPonto(A)) * (getXPonto(D) - getXPonto(C)) - (getYPonto(D) - getYPonto(C)) * (getXPonto(B) - getXPonto(A)));
    if(denom == 0)
        return NULL;


    s = (getXPonto(A) * (getYPonto(D)-getYPonto(C)) + getXPonto(C)*(getYPonto(A)-getYPonto(D)) + getXPonto(D)*(getYPonto(C)-getYPonto(A)))/denom;

    t = - (getXPonto(A) * (getYPonto(C)-getYPonto(B)) + getXPonto(B)*(getYPonto(A)-getYPonto(C)) + getXPonto(C)*(getYPonto(B)-getYPonto(A)))/denom;

    if(s>0 && s<1 && t>0 && t<1){
        return criaPonto(getXPonto(A)+s*(getXPonto(B)-getXPonto(A)),getYPonto(A)+s*(getYPonto(B)-getYPonto(A)));
    } else return NULL;
}

Segmento SegMaisProx(Vertice v, Vertice vet[], int indice) {
    int j=0;
    int id=-1;
    double minDist;
    Ponto foco = criaPonto(xFoco,yFoco);
    Ponto vertice = getPonto(v);
    for(int i=0;i<indice;i++){
        Segmento s = getSegmento(vet[i]);
        if(isSegmentoAtivo(s)==1){
            Ponto p1 = getPonto(getV1Segmento(s));
            Ponto p2 = getPonto(getV2Segmento(s));
            Ponto inter = intersectionLines(foco,vertice,p1,p2);
            if(inter!=NULL){
                if(j==0){
                    minDist=distancia(getXPonto(foco),getYPonto(foco),getXPonto(inter),getYPonto(inter));
                    id=i;
                    j++;
                }else{
                    if(distancia(getXPonto(foco),getYPonto(foco),getXPonto(inter),getYPonto(inter))<minDist ||
                        AreSame(distancia(getXPonto(foco),getYPonto(foco),getXPonto(inter),getYPonto(inter)),minDist)){
                            minDist=distancia(getXPonto(foco),getYPonto(foco),getXPonto(inter),getYPonto(inter));
                            id=i;
                    }
                }
                free(inter);
            }
        }
    }
    free(foco);
    if(id!=-1){
        return getSegmento(vet[id]);
    }else return NULL;
}

void organizaSegmentos(Lista Segmentos) {
    int posSeg = getFirst(Segmentos);
    while(posSeg!=-1){
        Segmento s = get(Segmentos,posSeg);
        Vertice v1 = getV1Segmento(s);
        Vertice v2 = getV2Segmento(s);
        Ponto p1 = getPonto(v1);
        Ponto p2 = getPonto(v2);
        Ponto c = criaPonto(xFoco,yFoco);

        if(lado(p1,p2,c)==1){
            setInicioFim(v2,0);
            setInicioFim(v1,1);
            swapVertices(s);
        }else{
            setInicioFim(v1,0);
            setInicioFim(v2,1);
        }
        posSeg = getNext(Segmentos,posSeg);
        free(c);
    }
}

int comparaVertices(const void *a, const void *b) {
    if(getAnguloVertice((*(Vertice*) a))>getAnguloVertice((*(Vertice*) b))) return 1;
    if(getAnguloVertice((*(Vertice*) a))<getAnguloVertice((*(Vertice*) b))) return -1;
    if(AreSame(getAnguloVertice((*(Vertice*) a)),getAnguloVertice((*(Vertice*) b)))){
        if(distancia(xFoco,yFoco,getXVertice((*(Vertice*) a)),getYVertice((*(Vertice*) a)))
            >distancia(xFoco,yFoco,getXVertice((*(Vertice*) b)),getYVertice((*(Vertice*) b)))){
                return 1;
        }else  if(distancia(xFoco,yFoco,getXVertice((*(Vertice*) a)),getYVertice((*(Vertice*) a)))
            <distancia(xFoco,yFoco,getXVertice((*(Vertice*) b)),getYVertice((*(Vertice*) b)))){
                return -1;
        }else if(AreSame(distancia(xFoco,yFoco,getXVertice((*(Vertice*) a)),getYVertice((*(Vertice*) a)))
            ,distancia(xFoco,yFoco,getXVertice((*(Vertice*) b)),getYVertice((*(Vertice*) b))))){
            if(isInicioOuFim((*(Vertice*) a))==0 && isInicioOuFim((*(Vertice*) b))==1)
                return -1;
            else if(isInicioOuFim((*(Vertice*) a))==1 && isInicioOuFim((*(Vertice*) b))==0)
                return 1;
            else return 0;
        }
    }

}

int isEncoberto(Vertice v,Lista segmentos) {
    Ponto foco=criaPonto(xFoco,yFoco);
    int posSeg = getFirst(segmentos);
    while (posSeg!=-1){
        Segmento s = get(segmentos,posSeg);
        Vertice v1=getV1Segmento(s);
        Vertice v2=getV2Segmento(s);
        Ponto sV1 = getPonto(v1);
        Ponto sV2 = getPonto(v2);
        if(pontoIntersecaoProprio(foco,getPonto(v),sV1,sV2)!=NULL) {
            free(foco);
            return 1;
        }
        else if(AreSame(getAnguloVertice(v),getAnguloVertice(v1))){
            if(!AreSame(distancia(xFoco,yFoco,getXPonto(sV1),getYPonto(sV1)),distancia(xFoco,yFoco,getXVertice(v),getYVertice(v)))
                && pontoIntersecao(foco,getPonto(v),sV1,sV2)!=NULL) {
                    free(foco);
                    return 1;
                }
        }else if(AreSame(getAnguloVertice(v),getAnguloVertice(v2))){
            if(!AreSame(distancia(xFoco,yFoco,getXPonto(sV2),getYPonto(sV2)),distancia(xFoco,yFoco,getXVertice(v),getYVertice(v)))
                && pontoIntersecao(foco,getPonto(v),sV1,sV2)!=NULL) {
                    free(foco);
                    return 1;
                }
        }
        posSeg=getNext(segmentos,posSeg);
    }
    free(foco);
    return 0;
}

int cortaHorizontal(Lista segmentos, Vertice vertices[], int indice, int tamanhoSeg, char *aux) {
    Vertice oesteA = getV1Segmento(contOeste);
    Vertice oesteB = getV2Segmento(contOeste);

    Ponto pOesteA = getPonto(oesteA);
    Ponto pOesteB = getPonto(oesteB);

    Ponto subInter = criaPonto(getXPonto(pOesteA),yFoco);

    Ponto foco = criaPonto(xFoco,yFoco);
    Ponto inter=pontoIntersecao(foco,subInter,pOesteA,pOesteB);

    Ponto intersecao;

    if(inter!=NULL){
        int posSeg = getFirst(segmentos);
        while (posSeg!=-1 && tamanhoSeg>0){
            Segmento s = get(segmentos,posSeg);
            int posAtual = posSeg;
            posSeg = getNext(segmentos,posSeg);
            Vertice v1=getV1Segmento(s);
            Vertice v2=getV2Segmento(s);
            Ponto pV1 = getPonto(v1);
            Ponto pV2 = getPonto(v2);

            intersecao = pontoIntersecao(foco,inter,pV1,pV2);
            if(intersecao!=NULL){
                Vertice Vi = criaVertice(intersecao,1,360);
                vertices[indice]=Vi;
                indice++;
                Segmento seg=criaSegmento(v1,Vi,0,0);
                segmentos=insert(segmentos,seg);
                setSegmento(v1,seg);
                setSegmento(Vi,seg);

                Vertice Vj = criaVertice(intersecao,0,0);
                vertices[indice]=Vj;
                indice++;
                seg=criaSegmento(Vj,v2,0,0);
                segmentos=insert(segmentos,seg);
                setSegmento(Vj,seg);
                setSegmento(v2,seg);

                remover(segmentos,posAtual);
            }
            tamanhoSeg--;
        }
    }
    free(intersecao);
    free(foco);
    free(inter);
    free(subInter);
    return indice;
}

float calcularAngulo(float x1, float y1, float x2, float y2) {
    float angulo = atan2(y2-y1,x2-x1)*(180/PI);

    if(angulo<0)
        angulo+=360;
    if(angulo>360)
        angulo-=360;

    return angulo;
}

int criaContorno(Vertice vertices[], Lista Segmentos, int indice, tabelaHash **hashQuad, tabelaHash **hashMur, char* svg) {
    float xMin=xFoco,yMin=yFoco,xMax=xFoco,yMax=yFoco;
    int i=0, tamQuadra = getTamHash(*hashQuad), tamMuro = getTamHash(*hashMur);
    Quadra q;
    Muro m;

    for (int i = 0; i < tamQuadra; i++) {
        listaHash n = getIndiceHash(*hashQuad, i);
        if (n != NULL) {
            listaHash aux = n;
            while (aux != NULL) {
                n = getProxHash(n);
                q = getObjetoHash2(aux);

                if(getQuadraX(q)<xMin)
                    xMin=getQuadraX(q);
                if(getQuadraX(q)+getQuadraLargura(q)>xMax)
                    xMax=getQuadraX(q)+getQuadraLargura(q);
                if(getQuadraY(q)<yMin)
                    yMin=getQuadraY(q);
                if(getQuadraY(q)+getQuadraAltura(q)>yMax)
                    yMax=getQuadraY(q)+getQuadraAltura(q);

                aux = n;
            }
        }
    }

    for (int i = 0; i < tamMuro; i++) {
        listaHash n = getIndiceHash(*hashMur, i);
        if (n != NULL) {
            listaHash aux = n;
            while (aux != NULL) {
                n = getProxHash(n);
                m = getObjetoHash2(aux);

                if(getMuroX1(m)<getMuroX2(m)){
                    if(xMin>getMuroX1(m))
                        xMin=getMuroX1(m);
                    if(xMax<getMuroX2(m))
                        xMax=getMuroX2(m);
                }else{
                    if(xMin>getMuroX2(m))
                        xMin=getMuroX2(m);
                    if(xMax<getMuroX1(m))
                        xMax=getMuroX1(m);
                }
                if(getMuroY1(m)<getMuroY2(m)){
                    if(yMin>getMuroY1(m))
                        yMin=getMuroY1(m);
                    if(yMax<getMuroY2(m))
                        yMax=getMuroY2(m);
                }else{
                    if(yMin>getMuroY2(m))
                        yMin=getMuroY2(m);
                    if(yMax<getMuroY1(m))
                        yMax=getMuroY1(m);
                }

                aux = n;
            }
        }
    }

    Ponto p1 = criaPonto(xMin-30,yMin-30);
    Vertice v1 = criaVertice(p1,-1,calcularAngulo(xFoco,yFoco,xMin-30,yMin-30));
    vertices[indice]=v1;
    indice++;

    Ponto p2 = criaPonto(xMin-30,yMax+30);
    Vertice v2 = criaVertice(p2,-1,calcularAngulo(xFoco,yFoco,xMin-30,yMax+30));
    vertices[indice]=v2;
    indice++;


    contLeste=criaSegmento(v1,v2,1,1);
    Segmentos = insert(Segmentos,contLeste);
    setSegmento(v1,contLeste);
    setSegmento(v2,contLeste);

    p1 = criaPonto(xMin-30,yMin-30);
    v1 = criaVertice(p1,-1,calcularAngulo(xFoco,yFoco,xMin-30,yMin-30));
    vertices[indice]=v1;
    indice++;

    p2 = criaPonto(xMax+30,yMin-30);
    v2 = criaVertice(p2,-1,calcularAngulo(xFoco,yFoco,xMax+30,yMin-30));
    vertices[indice]=v2;
    indice++;

    contSul=criaSegmento(v1,v2,1,1);
    Segmentos = insert(Segmentos,contSul);
    setSegmento(v1,contSul);
    setSegmento(v2,contSul);


    p1 = criaPonto(xMax+30,yMin-30);
    v1 = criaVertice(p1,-1,calcularAngulo(xFoco,yFoco,xMax+30,yMin-30));
    vertices[indice]=v1;
    indice++;

    p2 = criaPonto(xMax+30,yMax+30);
    v2 = criaVertice(p2,-1,calcularAngulo(xFoco,yFoco,xMax+30,yMax+30));
    vertices[indice]=v2;
    indice++;

    contOeste=criaSegmento(v1,v2,1,1);
    contOesteB=criaSegmento(v1,v2,1,1);
    Segmentos = insert(Segmentos,contOeste);

    setSegmento(v1,contOeste);
    setSegmento(v2,contOeste);


    p1 = criaPonto(xMin-30,yMax+30);
    v1 = criaVertice(p1,-1,calcularAngulo(xFoco,yFoco,xMin-30,yMax+30));
    vertices[indice]=v1;
    indice++;

    p2 = criaPonto(xMax+30,yMax+30);
    v2 = criaVertice(p2,-1,calcularAngulo(xFoco,yFoco,xMax+30,yMax+30));
    vertices[indice]=v2;
    indice++;

    contNorte=criaSegmento(v1,v2,1,1);
    Segmentos = insert(Segmentos,contNorte);

    setSegmento(v1,contNorte);
    setSegmento(v2,contNorte);

    desenharLinha(svg, xMin-30, xMin-30, yMin-30, yMax+30);
    desenharLinha(svg, xMin-30, xMax+30, yMin-30, yMin-30);
    desenharLinha(svg, xMax+30, xMax+30, yMin-30, yMax+30);
    desenharLinha(svg, xMin-30, xMax+30, yMax+30, yMax+30);

    return indice;
}

int criaVerticesAndSegmentos(tabelaHash **hashPrd, tabelaHash **hashMur, Vertice vertices[], Lista Segmentos) {
    int i=0, id=0, tamPredio = getTamHash(*hashPrd), tamMuro = getTamHash(*hashMur);
    Predio p;
    Muro m;

    Ponto foco = criaPonto(xFoco,yFoco);
    for (int j = 0; j < tamPredio; j++) {
        listaHash n = getIndiceHash(*hashPrd, j);
        if (n != NULL) {
            listaHash aux = n;
            while (aux != NULL) {
                n = getProxHash(n);
                p = getObjetoHash2(aux);
                Ponto ponto = criaPonto(getPredioX(p),getPredioY(p));
                Vertice v1=criaVertice(ponto,0,calcularAngulo(xFoco,yFoco,getPredioX(p),getPredioY(p)));
                vertices[i]=v1;
                i++;

                ponto= criaPonto(getPredioX(p), getPredioY(p)+getPredioAltura(p));
                Vertice v2=criaVertice(ponto,1,calcularAngulo(xFoco,yFoco,getPredioX(p),getPredioY(p)+getPredioAltura(p)));
                vertices[i]=v2;
                i++;

                Segmento s = criaSegmento(v1,v2,0,0);
                Segmentos = insert(Segmentos,s);

                setSegmento(v1,s);
                setSegmento(v2,s);

                ponto = criaPonto(getPredioX(p), getPredioY(p)+getPredioAltura(p));
                v1=criaVertice(ponto,0,calcularAngulo(xFoco,yFoco,getPredioX(p), getPredioY(p)+getPredioAltura(p)));
                vertices[i]=v1;
                i++;

                ponto = criaPonto(getPredioX(p)+getPredioLargura(p),getPredioY(p)+getPredioAltura(p));
                v2=criaVertice(ponto,1,calcularAngulo(xFoco,yFoco,getPredioX(p)+getPredioLargura(p),getPredioY(p)+getPredioAltura(p)));
                vertices[i]=v2;
                i++;

                s = criaSegmento(v1,v2,0,0);
                Segmentos = insert(Segmentos,s);

                setSegmento(v1,s);
                setSegmento(v2,s);

                ponto = criaPonto(getPredioX(p)+getPredioLargura(p),getPredioY(p)+getPredioAltura(p));
                v1=criaVertice(ponto,0,calcularAngulo(xFoco,yFoco,getPredioX(p)+getPredioLargura(p),getPredioY(p)+getPredioAltura(p)));
                vertices[i]=v1;
                i++;

                ponto= criaPonto(getPredioX(p)+getPredioLargura(p),getPredioY(p));
                v2=criaVertice(ponto,1,calcularAngulo(xFoco,yFoco,getPredioX(p)+getPredioLargura(p),getPredioY(p)));
                vertices[i]=v2;
                i++;

                s = criaSegmento(v1,v2,0,0);
                Segmentos = insert(Segmentos,s);

                setSegmento(v1,s);
                setSegmento(v2,s);

                ponto = criaPonto(getPredioX(p)+getPredioLargura(p),getPredioY(p));
                v1=criaVertice(ponto,0,calcularAngulo(xFoco,yFoco,getPredioX(p)+getPredioLargura(p),getPredioY(p)));
                vertices[i]=v1;
                i++;

                ponto= criaPonto(getPredioX(p),getPredioY(p));
                v2=criaVertice(ponto,1,calcularAngulo(xFoco,yFoco,getPredioX(p),getPredioY(p)));
                vertices[i]=v2;
                i++;

                s = criaSegmento(v1,v2,0,0);
                Segmentos = insert(Segmentos,s);

                setSegmento(v1,s);
                setSegmento(v2,s);

                aux = n;
            }
        }
    }

    for (int j = 0; j < tamMuro; j++) {
        listaHash n = getIndiceHash(*hashMur, j);
        if (n != NULL) {
            listaHash aux = n;
            while (aux != NULL) {
                n = getProxHash(n);
                m = getObjetoHash2(aux);

                Ponto ponto = criaPonto(getMuroX1(m),getMuroY1(m));
                Vertice v1=criaVertice(ponto,0,calcularAngulo(xFoco,yFoco,getMuroX1(m),getMuroY1(m)));
                vertices[i]=v1;
                i++;

                ponto = criaPonto(getMuroX2(m),getMuroY2(m));
                Vertice v2=criaVertice(ponto,1,calcularAngulo(xFoco,yFoco,getMuroX2(m),getMuroY2(m)));
                vertices[i]=v2;
                i++;

                Segmento s = criaSegmento(v1,v2,0,0);
                Segmentos = insert(Segmentos,s);

                setSegmento(v1,s);
                setSegmento(v2,s);

                aux = n;
            }
        }
    }
    free(foco);
    return i;
}

void desenhaSegmentos(Lista Segmentos, char *svg) {
    FILE *arqSvg;
    arqSvg = fopen(svg, "a");
    if (arqSvg == NULL) {
        printf("\nErro na abertura Svg.");
    }
    fprintf(arqSvg,"\n\t<polygon points=\"");
    int posSeg = getFirst(Segmentos);
    int i=0;
    while (posSeg!=-1){
        Segmento s = get(Segmentos,posSeg);
        Ponto p1=getPonto(getV1Segmento(s));
        Ponto p2=getPonto(getV2Segmento(s));
        fprintf(arqSvg,"%lf,%lf %lf,%lf ",getXPonto(p1),getYPonto(p1),getXPonto(p2),getYPonto(p2));
        posSeg=getNext(Segmentos,posSeg);
        if(i==5){
            fprintf(arqSvg,"\n\t\t");
            i=0;
        }
        i++;
    }
    fprintf(arqSvg,"\" style=\"fill:yellow;fill-opacity:0.5;stroke:purple;stroke-width:1\" />");
    fclose(arqSvg);
    desenharBomba(svg,xFoco,yFoco);
}

void comandoBrl(char *comandos, char *nomeSvg, tabelaHash **hashQuadra, tabelaHash **hashPredio, tabelaHash **hashMuro) {
    sscanf(comandos, "brl %f %f", &xFoco, &yFoco);
    int tamanhoVet = (getTamHash(*hashPredio)*8)+(getTamHash(*hashPredio)*2)+100;
    int tamanhoSegmentos = tamanhoVet/2;
    Ponto y;
    Vertice vy;

    Lista Segmentos = criaLista(tamanhoSegmentos);

    Vertice *vet=malloc(sizeof(Vertice)*tamanhoVet);

    int indice=criaVerticesAndSegmentos((tabelaHash)hashPredio, (tabelaHash)hashMuro, vet, Segmentos);

    indice=criaContorno(vet, Segmentos, indice, (tabelaHash)hashQuadra, (tabelaHash)hashMuro, nomeSvg);

    organizaSegmentos(Segmentos);

    indice=cortaHorizontal(Segmentos,vet,indice,length(Segmentos),nomeSvg);

    qsort(vet,indice,sizeof(Vertice),comparaVertices);

    Lista segmentosResposta = criaLista(tamanhoSegmentos*4);
    Lista segmentosAtivos = criaLista(tamanhoSegmentos);

    Ponto foco = criaPonto(xFoco,yFoco);

    Vertice biombo = vet[0];

    for(int i=0;i<indice;i++){
        Ponto pVet = getPonto(vet[i]);
        if(isInicioOuFim(vet[i])==0){
            if(getTipoSegmento(getSegmento(vet[i]))==0)
                ativaSegmento(getSegmento(vet[i]));
                segmentosAtivos= insert(segmentosAtivos,getSegmento(vet[i]));
            if(isEncoberto(vet[i],segmentosAtivos)==0){
                Segmento s = SegMaisProx(vet[i],vet,i);
                if(s!=NULL && i!=0){
                    Ponto pV1 = getPonto(getV1Segmento(s));
                    Ponto pV2 = getPonto(getV2Segmento(s));
                    y = intersectionLines(foco,pVet,pV1,pV2);
                    if(y!=NULL){
                        vy=criaVertice(y,1,0);
                        insert(segmentosResposta,criaSegmento(biombo,vy,1,1));
                        insert(segmentosResposta,criaSegmento(vy,vet[i],1,1));
                    }
                }
                biombo = vet[i];
            }
        } else {
            if(isEncoberto(vet[i],segmentosAtivos)==1) {
                desativaSegmento(getSegmento(vet[i]));
                removeElem(segmentosAtivos,getSegmento(vet[i]));
            } else {
                desativaSegmento(getSegmento(vet[i]));
                removeElem(segmentosAtivos,getSegmento(vet[i]));
                Segmento s = SegMaisProx(vet[i],vet,i);
                if(s!=NULL) {
                    Ponto pV1 = getPonto(getV1Segmento(s));
                    Ponto pV2 = getPonto(getV2Segmento(s));
                    y = intersectionLines(foco,pVet,pV1,pV2);
                    if(y!=NULL) {
                        vy=criaVertice(y,1,0);
                        insert(segmentosResposta,criaSegmento(biombo,vet[i],1,1));
                        insert(segmentosResposta,criaSegmento(vy,vet[i],1,1));
                        biombo = vy;
                    }
                }
            }
        }
        if(i==indice-1 && getAnguloVertice(vet[i]) != getAnguloVertice(vet[indice-1])){
            insert(segmentosResposta,criaSegmento(biombo,vet[i],1,1));
        }

        if(i+1<indice && isEqual(getPonto(vet[0]),getPonto(vet[i+1])) && getAnguloVertice(vet[i+1])==360){
            insert(segmentosResposta,criaSegmento(biombo,vet[0],1,1));
            break;
        }
    }
    desenhaSegmentos(segmentosResposta, nomeSvg);
    free(vy);
    free(y);
    free(vet);
    free(foco);
    desalocarlista(Segmentos);
    desalocarlista(segmentosResposta);
}

int criaContornoMuro(Vertice vertices[], Lista Segmentos, int indice, tabelaHash **hashMur, char* svg) {
    float xMin=xFoco,yMin=yFoco,xMax=xFoco,yMax=yFoco;
    int i=0, tamMuro = getTamHash(*hashMur);
    Muro m;

    for (int i = 0; i < tamMuro; i++) {
        listaHash n = getIndiceHash(*hashMur, i);
        if (n != NULL) {
            listaHash aux = n;
            while (aux != NULL) {
                n = getProxHash(n);
                m = getObjetoHash2(aux);

                if(getMuroX1(m)<getMuroX2(m)){
                    if(xMin>getMuroX1(m))
                        xMin=getMuroX1(m);
                    if(xMax<getMuroX2(m))
                        xMax=getMuroX2(m);
                }else{
                    if(xMin>getMuroX2(m))
                        xMin=getMuroX2(m);
                    if(xMax<getMuroX1(m))
                        xMax=getMuroX1(m);
                }
                if(getMuroY1(m)<getMuroY2(m)){
                    if(yMin>getMuroY1(m))
                        yMin=getMuroY1(m);
                    if(yMax<getMuroY2(m))
                        yMax=getMuroY2(m);
                }else{
                    if(yMin>getMuroY2(m))
                        yMin=getMuroY2(m);
                    if(yMax<getMuroY1(m))
                        yMax=getMuroY1(m);
                }

                aux = n;
            }
        }
    }

    Ponto p1 = criaPonto(xMin-30,yMin-30);
    Vertice v1 = criaVertice(p1,-1,calcularAngulo(xFoco,yFoco,xMin-30,yMin-30));
    vertices[indice]=v1;
    indice++;

    Ponto p2 = criaPonto(xMin-30,yMax+30);
    Vertice v2 = criaVertice(p2,-1,calcularAngulo(xFoco,yFoco,xMin-30,yMax+30));
    vertices[indice]=v2;
    indice++;


    contLeste=criaSegmento(v1,v2,1,1);
    Segmentos = insert(Segmentos,contLeste);
    setSegmento(v1,contLeste);
    setSegmento(v2,contLeste);

    p1 = criaPonto(xMin-30,yMin-30);
    v1 = criaVertice(p1,-1,calcularAngulo(xFoco,yFoco,xMin-30,yMin-30));
    vertices[indice]=v1;
    indice++;

    p2 = criaPonto(xMax+30,yMin-30);
    v2 = criaVertice(p2,-1,calcularAngulo(xFoco,yFoco,xMax+30,yMin-30));
    vertices[indice]=v2;
    indice++;

    contSul=criaSegmento(v1,v2,1,1);
    Segmentos = insert(Segmentos,contSul);
    setSegmento(v1,contSul);
    setSegmento(v2,contSul);


    p1 = criaPonto(xMax+30,yMin-30);
    v1 = criaVertice(p1,-1,calcularAngulo(xFoco,yFoco,xMax+30,yMin-30));
    vertices[indice]=v1;
    indice++;

    p2 = criaPonto(xMax+30,yMax+30);
    v2 = criaVertice(p2,-1,calcularAngulo(xFoco,yFoco,xMax+30,yMax+30));
    vertices[indice]=v2;
    indice++;

    contOeste=criaSegmento(v1,v2,1,1);
    contOesteB=criaSegmento(v1,v2,1,1);
    Segmentos = insert(Segmentos,contOeste);

    setSegmento(v1,contOeste);
    setSegmento(v2,contOeste);


    p1 = criaPonto(xMin-30,yMax+30);
    v1 = criaVertice(p1,-1,calcularAngulo(xFoco,yFoco,xMin-30,yMax+30));
    vertices[indice]=v1;
    indice++;

    p2 = criaPonto(xMax+30,yMax+30);
    v2 = criaVertice(p2,-1,calcularAngulo(xFoco,yFoco,xMax+30,yMax+30));
    vertices[indice]=v2;
    indice++;

    contNorte=criaSegmento(v1,v2,1,1);
    Segmentos = insert(Segmentos,contNorte);

    setSegmento(v1,contNorte);
    setSegmento(v2,contNorte);

    desenharLinha(svg, xMin-30, xMin-30, yMin-30, yMax+30);
    desenharLinha(svg, xMin-30, xMax+30, yMin-30, yMin-30);
    desenharLinha(svg, xMax+30, xMax+30, yMin-30, yMax+30);
    desenharLinha(svg, xMin-30, xMax+30, yMax+30, yMax+30);

    return indice;
}

int criaVerticesAndSegmentosMuro(tabelaHash **hashMur, Vertice vertices[], Lista Segmentos) {
    int i=0, id=0, tamMuro = getTamHash(*hashMur);
    Muro m;

    Ponto foco = criaPonto(xFoco,yFoco);
    for (int j = 0; j < tamMuro; j++) {
        listaHash n = getIndiceHash(*hashMur, j);
        if (n != NULL) {
            listaHash aux = n;
            while (aux != NULL) {
                n = getProxHash(n);
                m = getObjetoHash2(aux);

                Ponto ponto = criaPonto(getMuroX1(m),getMuroY1(m));
                Vertice v1=criaVertice(ponto,0,calcularAngulo(xFoco,yFoco,getMuroX1(m),getMuroY1(m)));
                vertices[i]=v1;
                i++;

                ponto = criaPonto(getMuroX2(m),getMuroY2(m));
                Vertice v2=criaVertice(ponto,1,calcularAngulo(xFoco,yFoco,getMuroX2(m),getMuroY2(m)));
                vertices[i]=v2;
                i++;

                Segmento s = criaSegmento(v1,v2,0,0);
                Segmentos = insert(Segmentos,s);

                setSegmento(v1,s);
                setSegmento(v2,s);

                aux = n;
            }
        }
    }
    free(foco);
    return i;
}

void desenhaSegmentosPoligono(Lista Segmentos, char *svg, char *pol) {
    FILE *arqSvg;
    arqSvg = fopen(svg, "a");
    if (arqSvg == NULL) {
        printf("\nErro na abertura Svg.");
    }

    FILE *arqPol;
    arqPol = fopen(pol, "a");

    fprintf(arqSvg,"\n\t<polygon points=\"");
    int posSeg = getFirst(Segmentos);
    int i=0;
    while (posSeg!=-1){
        Segmento s = get(Segmentos,posSeg);
        Ponto p1=getPonto(getV1Segmento(s));
        Ponto p2=getPonto(getV2Segmento(s));
        fprintf(arqSvg,"%lf,%lf %lf,%lf ",getXPonto(p1),getYPonto(p1),getXPonto(p2),getYPonto(p2));
        fprintf(arqPol, "%lf %lf\n%lf %lf\n", getXPonto(p1),getYPonto(p1),getXPonto(p2),getYPonto(p2));
        posSeg=getNext(Segmentos,posSeg);
        if(i==5){
            fprintf(arqSvg,"\n\t\t");
            i=0;
        }
        i++;
    }
    fprintf(arqSvg,"\" style=\"fill:yellow;fill-opacity:0.5;stroke:purple;stroke-width:1\" />");
    fclose(arqSvg);
    fclose(arqPol);
    desenharBomba(svg,xFoco,yFoco);
}

void comandoBrn(char *comandos, char *localEntrada, char *nomeSvg, tabelaHash **hashMuro) {
    char arqPolig[100], *temp5;
    sscanf(comandos, "brn %f %f %s", &xFoco, &yFoco, arqPolig);
    int tamanhoVet = (getTamHash(*hashMuro)*8)+(getTamHash(*hashMuro)*2)+100;
    int tamanhoSegmentos = tamanhoVet/2;
    Ponto y;
    Vertice vy;

    Lista Segmentos = criaLista(tamanhoSegmentos);

    Vertice *vet=malloc(sizeof(Vertice)*tamanhoVet);

    int indice=criaVerticesAndSegmentosMuro((tabelaHash)hashMuro, vet, Segmentos);

    indice=criaContornoMuro(vet, Segmentos, indice, (tabelaHash)hashMuro, nomeSvg);

    organizaSegmentos(Segmentos);

    indice=cortaHorizontal(Segmentos,vet,indice,length(Segmentos),nomeSvg);

    qsort(vet,indice,sizeof(Vertice),comparaVertices);

    Lista segmentosResposta = criaLista(tamanhoSegmentos*4);
    Lista segmentosAtivos = criaLista(tamanhoSegmentos);

    Ponto foco = criaPonto(xFoco,yFoco);

    Vertice biombo = vet[0];

    for(int i=0;i<indice;i++){
        Ponto pVet = getPonto(vet[i]);
        if(isInicioOuFim(vet[i])==0){
            if(getTipoSegmento(getSegmento(vet[i]))==0)
                ativaSegmento(getSegmento(vet[i]));
                segmentosAtivos= insert(segmentosAtivos,getSegmento(vet[i]));
            if(isEncoberto(vet[i],segmentosAtivos)==0){
                Segmento s = SegMaisProx(vet[i],vet,i);
                if(s!=NULL && i!=0){
                    Ponto pV1 = getPonto(getV1Segmento(s));
                    Ponto pV2 = getPonto(getV2Segmento(s));
                    y = intersectionLines(foco,pVet,pV1,pV2);
                    if(y!=NULL){
                        vy=criaVertice(y,1,0);
                        insert(segmentosResposta,criaSegmento(biombo,vy,1,1));
                        insert(segmentosResposta,criaSegmento(vy,vet[i],1,1));
                    }
                }
                biombo = vet[i];
            }
        } else {
            if(isEncoberto(vet[i],segmentosAtivos)==1) {
                desativaSegmento(getSegmento(vet[i]));
                removeElem(segmentosAtivos,getSegmento(vet[i]));
            } else {
                desativaSegmento(getSegmento(vet[i]));
                removeElem(segmentosAtivos,getSegmento(vet[i]));
                Segmento s = SegMaisProx(vet[i],vet,i);
                if(s!=NULL) {
                    Ponto pV1 = getPonto(getV1Segmento(s));
                    Ponto pV2 = getPonto(getV2Segmento(s));
                    y = intersectionLines(foco,pVet,pV1,pV2);
                    if(y!=NULL) {
                        vy=criaVertice(y,1,0);
                        insert(segmentosResposta,criaSegmento(biombo,vet[i],1,1));
                        insert(segmentosResposta,criaSegmento(vy,vet[i],1,1));
                        biombo = vy;
                    }
                }
            }
        }
        if(i==indice-1 && getAnguloVertice(vet[i]) != getAnguloVertice(vet[indice-1])){
            insert(segmentosResposta,criaSegmento(biombo,vet[i],1,1));
        }

        if(i+1<indice && isEqual(getPonto(vet[0]),getPonto(vet[i+1])) && getAnguloVertice(vet[i+1])==360){
            insert(segmentosResposta,criaSegmento(biombo,vet[0],1,1));
            break;
        }
    }
    FILE *arqPol;
    if(localEntrada != NULL) {
        temp5 = getArquivo(localEntrada,arqPolig);
        arqPol = fopen(temp5, "w");
    } else {
        arqPol = fopen(arqPolig, "w");
    }
    fclose(arqPol);
    desenhaSegmentosPoligono(segmentosResposta, nomeSvg, temp5);
    free(vy);
    free(y);
    free(vet);
    free(foco);
    desalocarlista(Segmentos);
    desalocarlista(segmentosResposta);
}
