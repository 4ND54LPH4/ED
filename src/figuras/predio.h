#ifndef PREDIO
#define PREDIO
#define MAX 50
#include "estrutura/hash.h"

typedef void *Predio;

Predio addPredio(char comandos[500], tabelaHash hashQuadra);

char *getPredioId(Predio recebePredio);
char getPredioFace(Predio recebePredio);
int getPredioNum(Predio recebePredio);
float getPredioF(Predio recebePredio);
float getPredioP(Predio recebePredio);
float getPredioMrg(Predio recebePredio);
float getPredioX(Predio recebePredio);
float getPredioY(Predio recebePredio);
float getPredioTexX(Predio recebePredio);
float getPredioTexY(Predio recebePredio);
float getPredioAltura(Predio recebePredio);
float getPredioLargura(Predio recebePredio);

void removePredio(Predio recebePredio);
char* printValorPredio(Predio recebePredio, char *dados);
int comparaPredio(Predio recebePredio1, Predio recebePredio2);
int comparaIdPredio(Predio recebePredio1, Predio recebePredio2);
int comparaKeyPredio(Predio recebePredio, char *key);

#endif
