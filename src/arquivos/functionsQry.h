#ifndef FUNCTIONSQRY
#define FUNCTIONSQRY
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
//void comandoDel(char *linhaArquivo,char *saidaSvg,char *saidaTxt,struct tree **hidrante, struct tree **semaforo, struct tree **radio, struct tree**quadra, tabelaHash **hashHid, tabelaHash **hashSem, tabelaHash **hashRad, tabelaHash **hashQuad);
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

#endif
