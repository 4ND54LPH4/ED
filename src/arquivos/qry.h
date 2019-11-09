#ifndef QRY
#define QRY
#include "../nx/nx.h"
#include "../figuras/estrutura/hash.h"
#include "../figuras/estrutura/rbtree.h"
#include "functionsQry.h"

void processarComandosQry(char *pGeo,char *pQry,char *localEntrada,char *localSaida,nx qtdFiguras,
    struct tree **circulo,struct tree **retangulo,struct tree **texto,struct tree **hidrante,
    struct tree **quadra,struct tree **semaforo,struct tree **radio,struct tree **muro,struct tree **predio,
    struct tree **tipoEstabelecimento, struct tree **estabelecimento,struct tree **pessoa,struct tree**morador,
    tabelaHash **hashCirc,tabelaHash **hashRet,tabelaHash **hashHid,
    tabelaHash **hashQuad,tabelaHash **hashSem,tabelaHash **hashRad,
    tabelaHash **hashPrd,tabelaHash **hashMur,tabelaHash **hashTipEst,
    tabelaHash **hashEst,tabelaHash **hashPes,tabelaHash **hashMor);

#endif
