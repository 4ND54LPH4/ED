#ifndef GEO
#define GEO
#include "../nx/nx.h"
#include "../figuras/estrutura/hash.h"
#include "../figuras/estrutura/rbtree.h"

void processarComandosGeo(char *pGeo,char *localEntrada,char *localSaida,nx qtdFiguras,struct tree **circulo,struct tree **retangulo,struct tree **texto,struct tree **hidrante,struct tree **quadra,struct tree **semaforo,struct tree **radio,struct tree **muro,struct tree **predio,tabelaHash **hashCirc,tabelaHash **hashRet,tabelaHash **hashHid,tabelaHash **hashQuad,tabelaHash **hashSem,tabelaHash **hashRad,tabelaHash **hashPrd);

#endif
