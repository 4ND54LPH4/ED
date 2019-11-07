#ifndef ARQUIVOPM
#define ARQUIVOPM
#include "../nx/nx.h"
#include "../figuras/estrutura/rbtree.h"
#include "../figuras/estrutura/hash.h"

void processarComandosPm(char *pessoas,char *localEntrada,char *localSaida,nx qtdFiguras, struct tree **pessoa, struct tree **morador, tabelaHash **hashPes, tabelaHash **hashMor);

#endif
