#ifndef FUNCTIONSQRY
#define FUNCTIONSQRY
#include "../nx/nx.h"
#include "../figuras/estrutura/hash.h"
#include "../figuras/estrutura/rbtree.h"

void comandoDq (char* comandos, char* temp2, char* temp3, struct tree **hidrante, struct tree **semaforo, struct tree **radio, struct tree**quadra, tabelaHash **hashHid, tabelaHash **hashSem, tabelaHash **hashRad, tabelaHash **hashQuad);
void comandoDmprbt(char* comandos, char* localSaida, struct tree **hidrante, struct tree **semaforo, struct tree **radio, struct tree**quadra, struct tree**predio, struct tree**muro);
void comandoMoradores(char* comandos, char* nomeTxt, tabelaHash **hashQuad, tabelaHash **hashMor);
void comandoDm(char* comandos, char* nomeTxt, tabelaHash **hashMor);
void comandoDe(char* comandos, char* nomeTxt, tabelaHash **hashEst);

#endif
