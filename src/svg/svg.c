#include <stdlib.h>
#include <string.h>
#include "svg.h"
#include "../figuras/figuras.h"

void iniciarSvg(char *fileName) {
    FILE *arquivo = NULL;
    arquivo = fopen(fileName,"w");
    fputs("<svg style='stroke-width:3px;fill-opacity:0.5'>\n<rect width = '100%' height = '100%' fill = 'white' fill-opacity = '1.0'/>\n",arquivo);
    fclose(arquivo);
}

void finalizarSvg(char *fileName) {
    FILE *arquivo = NULL;
    arquivo = fopen(fileName,"a+");
    fputs("</svg>",arquivo);
    fclose(arquivo);
}

void desenharCirculo(char *fileName,Circulo recebeCirculo) {
    FILE *saidaSvg = NULL;
    saidaSvg = fopen(fileName,"a+");

    fprintf(saidaSvg,"\t<circle r='%lf' cx='%lf' cy='%lf' stroke='%s' fill='%s' stroke-width='%lf'/>\n",
    getCirculoRaio(recebeCirculo),getCirculoX(recebeCirculo),getCirculoY(recebeCirculo),
    getCirculoCfill(recebeCirculo),getCirculoCstrk(recebeCirculo),getCirculoCw(recebeCirculo));

    fclose(saidaSvg);
}

void desenharRetangulo(char *fileName,Retangulo recebeRetangulo) {
    FILE *saidaSvg = NULL;
    saidaSvg = fopen(fileName,"a+");

    fprintf(saidaSvg,"\t<rect x='%lf' y='%lf' width='%lf' height='%lf' stroke='%s' fill='%s' stroke-width='%lf'/>\n",
    getRetanguloX(recebeRetangulo),getRetanguloY(recebeRetangulo),getRetanguloLargura(recebeRetangulo),
    getRetanguloAltura(recebeRetangulo),getRetanguloCstrk(recebeRetangulo),
    getRetanguloCfill(recebeRetangulo),getRetanguloRw(recebeRetangulo));

    fclose(saidaSvg);
}

void escreverTexto(char *fileName,Texto recebeTexto) {
    FILE *saidaSvg = NULL;
    saidaSvg = fopen(fileName,"a+");

    fprintf(saidaSvg,"\t<text x='%lf' y='%lf'>%s</text>\n",getTextoX(recebeTexto),getTextoY(recebeTexto),
    getTextoTexto(recebeTexto));

    fclose(saidaSvg);
}

void desenharQuadra(char *fileName,Quadra recebeQuadra) {
    FILE *saidaSvg = NULL;
    saidaSvg = fopen(fileName,"a+");

    fprintf(saidaSvg,"\t<rect x='%lf' y='%lf' width='%lf' height='%lf' stroke='%s' fill='%s' stroke-width='%lf'/>\n",
        getQuadraX(recebeQuadra),getQuadraY(recebeQuadra),getQuadraLargura(recebeQuadra),
        getQuadraAltura(recebeQuadra),getQuadraCstrk(recebeQuadra),getQuadraCfill(recebeQuadra),getQuadraCq(recebeQuadra));

    fprintf(saidaSvg,"\t<text x='%lf' y='%lf' text-anchor='middle' font-size='10px'>%s</text>\n",
        getQuadraX(recebeQuadra)+getQuadraLargura(recebeQuadra)/4,getQuadraY(recebeQuadra)+getQuadraAltura(recebeQuadra)/4,
        getQuadraId(recebeQuadra));

    fclose(saidaSvg);
}

void desenharHidrante(char *fileName,Hidrante recebeHidrante) {
    FILE *saidaSvg = NULL;
    saidaSvg = fopen(fileName,"a+");

    fprintf(saidaSvg,"\t<circle r='3' cx='%lf' cy='%lf' stroke='%s' fill='%s' stroke-width='%lf'/>\n",
        getHidranteX(recebeHidrante),getHidranteY(recebeHidrante),getHidranteCstrk(recebeHidrante),
        getHidranteCfill(recebeHidrante),getHidranteCh(recebeHidrante));

    fprintf(saidaSvg,"\t<text x='%lf' y='%lf' text-anchor='middle' font-size='4px'>H</text>\n",
            getHidranteX(recebeHidrante),getHidranteY(recebeHidrante)+0.75);

    fclose(saidaSvg);
}

void desenharSemaforo(char *fileName,Semaforo recebeSemaforo) {
    FILE *saidaSvg = NULL;
    saidaSvg = fopen(fileName,"a+");

    fprintf(saidaSvg,"\t<circle r='5' cx='%lf' cy='%lf' stroke='%s' fill='%s' stroke-width='%lf'/>\n",
        getSemaforoX(recebeSemaforo),getSemaforoY(recebeSemaforo),getSemaforoCstrk(recebeSemaforo),
        getSemaforoCfill(recebeSemaforo),getSemaforoCs(recebeSemaforo));

    fprintf(saidaSvg,"\t<text x='%lf' y='%lf' text-anchor='middle' font-size='5px'>S</text>\n",
        getSemaforoX(recebeSemaforo),getSemaforoY(recebeSemaforo)+0.75);

    fclose(saidaSvg);
}

void desenharRadio(char *fileName,Radio recebeRadio) {
    FILE *saidaSvg = NULL;
    saidaSvg = fopen(fileName,"a+");

    fprintf(saidaSvg,"\t<circle r='7' cx='%lf' cy='%lf' stroke='%s' fill='%s' stroke-width='%lf'/>\n",
        getRadioX(recebeRadio),getRadioY(recebeRadio),getRadioCstrk(recebeRadio),
        getRadioCfill(recebeRadio),getRadioCr(recebeRadio));

    fprintf(saidaSvg,"\t<text x='%lf' y='%lf' text-anchor='middle' font-size='8px'>R</text>\n",
        getRadioX(recebeRadio),getRadioY(recebeRadio)+0.75);

    fclose(saidaSvg);
}


void desenharPredio(char *fileName,Predio recebePredio) {
    FILE *saidaSvg = NULL;
    saidaSvg = fopen(fileName,"a+");

    fprintf(saidaSvg,"\t<rect x='%lf' y='%lf' width='%lf' height='%lf' stroke='black' fill='grey' stroke-width='1.5'/>\n",
    getPredioX(recebePredio),getPredioY(recebePredio),getPredioLargura(recebePredio),
    getPredioAltura(recebePredio));

    fprintf(saidaSvg,"\t<text x='%lf' y='%lf' fill-opacity='1.0' text-anchor='middle' fill ='black' text-size='1'>%d</text>\n",
    getPredioTexX(recebePredio),getPredioTexY(recebePredio),getPredioNum(recebePredio));

    fclose(saidaSvg);
}

void desenharMuro(char *fileName,Muro recebeMuro) {
    FILE *saidaSvg = NULL;
    saidaSvg = fopen(fileName,"a+");

    fprintf(saidaSvg,"\t<line x1='%lf' y1='%lf' x2='%lf' y2='%lf' stroke-width='3' stroke='black' />\n",
        getMuroX1(recebeMuro),getMuroY1(recebeMuro),getMuroX2(recebeMuro),getMuroY2(recebeMuro));

    fclose(saidaSvg);
}

void desenharBomba(char *fileName, float x, float y) {
    FILE *saidaSvg = NULL;
    saidaSvg = fopen(fileName,"a");

    fprintf(saidaSvg, "<circle r='7' cx='%f' cy='%f' stroke='black' fill='grey' stroke-width='1'/>\n", x, y);

    fclose(saidaSvg);
}

void desenharLinha(char *fileName, float x1, float x2, float y1, float y2) {
    FILE *saidaSvg = NULL;
    saidaSvg = fopen(fileName,"a");

    fprintf(saidaSvg, "<line x1='%f' y1='%f' x2='%f' y2='%f' style='stroke:rgb(0,0,0);stroke-width:2;'/>\n", x1, y1, x2, y2);

    fclose(saidaSvg);
}

void escreverPontoInterno(double x,double y,char linhaArquivo[500],char *sTxt,char *sSvg) {
    FILE *saidaTxt = fopen(sTxt,"a+");
    FILE *saidaSvg = fopen(sSvg,"a+");

    fprintf(saidaTxt,"%sINTERNO\n",linhaArquivo);
    fprintf(saidaSvg,"\t<circle r='5' cx='%lf' cy='%lf' stroke='green' fill='forestgreen' stroke-width='2'/>\n",x,y);

    fclose(saidaTxt);
    fclose(saidaSvg);
}

void escreverPontoNaoInterno(double x,double y,char linhaArquivo[500],char *sTxt,char *sSvg) {
    FILE *saidaTxt = fopen(sTxt,"a+");
    FILE *saidaSvg = fopen(sSvg,"a+");

    fprintf(saidaTxt,"%sNAO INTERNO\n",linhaArquivo);
    fprintf(saidaSvg,"\t<circle r='5' cx='%lf' cy='%lf' stroke='darkred' fill='red' stroke-width='2'/>\n",x,y);

    fclose(saidaTxt);
    fclose(saidaSvg);
}

void escreverRetaDistancia(double xInicio, double yInicio,double xFinal,double yFinal,char *cor,char *sSvg) {
    FILE *saidaSvg = fopen(sSvg,"a+");

    fprintf(saidaSvg,"\t<line x1='%lf' y1='%lf' x2='%lf' y2='%lf' stroke-width='3' stroke='%s' />\n",xInicio,yInicio,xFinal,yFinal,cor);

    fclose(saidaSvg);
}

void escreverDistanciaSvg(double x,double y,double distancia,char *sSvg) {
    FILE *saidaSvg = fopen(sSvg,"a+");

    fprintf(saidaSvg,"\t<text x='%lf' y='%lf' text-anchor='middle' font-size='10px'>%lf</text>\n",x,y,distancia);

    fclose(saidaSvg);
}

void escreverDistanciaTxt(char linhaArquivo[500],double distancia,char *sTxt) {
    FILE *saidaTxt = fopen(sTxt,"a+");

    fprintf(saidaTxt,"%s%lf\n",linhaArquivo,distancia);

    fclose(saidaTxt);
}

void escreverTextoTxt(char *nomeArq, char* texto) {
    FILE *saidaTxt = fopen(nomeArq, "a+");
    fprintf(saidaTxt, "%s", texto);
    fclose(saidaTxt);
}

void desenhaSvgBB(char *nomeSaida,char *cor) {
    FILE *arquivoSaida = NULL;

    arquivoSaida = fopen(nomeSaida,"w");



    fclose(arquivoSaida);
}
