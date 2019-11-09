#ifndef FUNCTIONSQRY
#define FUNCTIONSQRY
#include "../figuras/brl/segmento.h"
#include "../figuras/brl/vertice.h"
#include "../figuras/brl/ponto.h"
#include "../figuras/brl/lista.h"
#include "../nx/nx.h"
#include "../figuras/estrutura/hash.h"
#include "../figuras/estrutura/rbtree.h"
#include "../figuras/quadra.h"


// Comandos T1
void comandoOverlap(char *linhaArquivo,char *saidaSvg,char *saidaTxt,struct tree **circulo,struct tree **retangulo,tabelaHash **hashCirc,tabelaHash **hashRet);
void comandoInterno(char *linhaArquivo,char *saidaSvg,char *saidaTxt,struct tree **circulo,struct tree **retangulo,tabelaHash **hashCirc,tabelaHash **hashRet);
void comandoDistancia(char *linhaArquivo,char *saidaSvg,char *saidaTxt,struct tree **circulo,struct tree **retangulo,tabelaHash **hashCirc,tabelaHash **hashRet);
void comandoBB(char *linhaArquivo,char *nomeSaidaSvg,struct tree **circulo,struct tree **retangulo,struct tree **texto);

// Comandos T2
void comandoDq (char* comandos, char* temp2, char* temp3, struct tree **hidrante, struct tree **semaforo, struct tree **radio, struct tree**quadra, tabelaHash **hashHid, tabelaHash **hashSem, tabelaHash **hashRad, tabelaHash **hashQuad);
void comandoDel(char *linhaArquivo,char *saidaSvg,char *saidaTxt,struct tree **hidrante, struct tree **semaforo, struct tree **radio, struct tree**quadra, tabelaHash **hashHid, tabelaHash **hashSem, tabelaHash **hashRad, tabelaHash **hashQuad);
void comandoCbq(char *linhaArquivo,char *saidaSvg,char *saidaTxt,struct tree **quadra,tabelaHash **hashQuad);
int verificaQuadraDentroCirculo(double x,double y,double raio,Quadra q);
void comandoCrd(char *linhaArquivo,char *saidaTxt,struct tree **hidrante, struct tree **semaforo, struct tree **radio, struct tree**quadra, tabelaHash **hashHid, tabelaHash **hashSem, tabelaHash **hashRad, tabelaHash **hashQuad);
void comandoTrns();

// Comandos T3
void comandoBrl();
void comandoFi();
void comandoFh();
void comandoFs();

// Comandos T4
void comandoDmprbt(char* comandos, char* localSaida, struct tree **hidrante, struct tree **semaforo, struct tree **radio, struct tree**quadra, struct tree**predio, struct tree**muro);
void comandoMoradores(char* comandos, char* nomeTxt, tabelaHash **hashQuad, tabelaHash **hashMor);
void comandoDm(char* comandos, char* nomeTxt, tabelaHash **hashMor);
void comandoDe(char* comandos, char* nomeTxt, tabelaHash **hashEst);
void comandoMud(char* comandos, char* nomeTxt, tabelaHash **hashMor);

// Calcular distancia entre 2 pontos
double distancia(double x1, double y1, double x2, double y2);
// Determina o lado que um segmento vai virar
int lado(Ponto A, Ponto B, Ponto C);
// Retorna valor minimo de um vetor
double min(double vet[], int size);
// Retorna valor maximo de um vetor
double max(double vet[], int size);
// Verifica se 2 segmentos se interceptam
int seInterceptam(Ponto A, Ponto B, Ponto C, Ponto D);
// Retorna o ponto de interseccao pela equacao da reta impropria dos segmentos dados
Ponto intersectionLines(Ponto A1, Ponto A2, Ponto B1, Ponto B2);
// Verifica se dois valores sao iguais (utilizando macro __DBL_EPSILON__)
int AreSame(double a, double b);
// Verifica se A = B
int isEqual(Ponto A, Ponto B);
// Retorna o ponto de interseccao entre 2 segmentos
Ponto pontoIntersecao(Ponto A, Ponto B, Ponto C, Ponto D);
// Verifica se ha interseccao propria entre 2 segmentos
int seInterceptamProprio(Ponto A, Ponto B, Ponto C, Ponto D);
// Retorna o ponto de interseccao proprio entre 2 segmentos
Ponto pontoIntersecaoProprio(Ponto A, Ponto B, Ponto C, Ponto D);
// Retorna o segmento mais proximo
Segmento SegMaisProx(Vertice v, Vertice vet[], int indice);
// Ordenar segmentos
void organizaSegmentos(Lista Segmentos);
// Comparar vertice A com B
int comparaVertices(const void *a, const void *b);
// Verifica se vertice esta encoberto
int isEncoberto(Vertice v,Lista segmentos);
// Faz um corte na horizontal de um segmento
int cortaHorizontal(Lista segmentos, Vertice vertices[], int indice, int tamanhoSeg, char *aux);
// Calcular angulo para gerar segmento
float calcularAngulo(float x1, float y1, float x2, float y2);
// Cria contorno em volta de um segmento
int criaContorno(Vertice vertices[], Lista Segmentos, int indice, tabelaHash **hashQuad, tabelaHash **hashMur, char* svg);
// Criar vertices e segmentos com base nos predios, muros e quadras
int criaVerticesAndSegmentos(tabelaHash **hashPrd, tabelaHash **hashMur, Vertice vertices[], Lista Segmentos);
// Desenha a regiao afetada (point visibility region)
void desenhaSegmentos(Lista Segmentos, char *svg);
// Le comando brl e adiciona a saida .svg
void comandoBrl(char *comandos, char *nomeSvg, tabelaHash **hashQuadra, tabelaHash **hashPredio, tabelaHash **hashMuro);
// Cria contorno em volta de um segmento de muro
int criaContornoMuro(Vertice vertices[], Lista Segmentos, int indice, tabelaHash **hashMur, char* svg);
// Criar vertices e segmentos com base nos muros somente
int criaVerticesAndSegmentosMuro(tabelaHash **hashMur, Vertice vertices[], Lista Segmentos);
// Desenha a regiao afetada (point visibility region) no svg e escreve pontos do poligono resultante no arquivo informado no comando
void desenhaSegmentosPoligono(Lista Segmentos, char *svg, char *pol);
// Le comando brn e adiciona a saida .svg .txt e .pol
void comandoBrn(char *comandos, char *localEntrada, char *nomeSvg, tabelaHash **hashMuro);

#endif
