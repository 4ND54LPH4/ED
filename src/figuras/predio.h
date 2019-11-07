#ifndef PREDIO
#define PREDIO
#define MAX 50
#include "estrutura/hash.h"

typedef void *Predio;

Predio addPredio(char comandos[500], tabelaHash hashQuadra);

char *getPredioId(Predio recebePredio);
char getPredioFace(Predio recebePredio);
int getPredioNum(Predio recebePredio);
double getPredioF(Predio recebePredio);
double getPredioP(Predio recebePredio);
double getPredioMrg(Predio recebePredio);
double getPredioX(Predio recebePredio);
double getPredioY(Predio recebePredio);
double getPredioTexX(Predio recebePredio);
double getPredioTexY(Predio recebePredio);
double getPredioAltura(Predio recebePredio);
double getPredioLargura(Predio recebePredio);

void removePredio(Predio recebePredio);
char* printValorPredio(Predio recebePredio, char *dados);
int comparaPredio(Predio recebePredio1, Predio recebePredio2);
int comparaIdPredio(Predio recebePredio1, Predio recebePredio2);
int comparaKeyPredio(Predio recebePredio, char *key);

#endif
