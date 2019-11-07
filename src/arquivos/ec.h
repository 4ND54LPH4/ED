#ifndef ARQUIVOEC
#define ARQUIVOEC
#include "../nx/nx.h"
#include "../figuras/estrutura/hash.h"
#include "../figuras/estrutura/rbtree.h"

void processarComandosEc(char *estabComercial,char *localEntrada,char *localSaida,nx qtdFiguras, struct tree **tipoEstabelecimento, struct tree **estabelecimento, tabelaHash **hashTipEst, tabelaHash **hashEst, tabelaHash **hashPes);

#endif
