#ifndef MORADOR
#define MORADOR
#define MAX 50
#include "estrutura/hash.h"

typedef void *Morador;

Morador addMorador(char comandos[500], tabelaHash hashPessoa);

char *getMoradorCpf(Morador recebeMorador);
char *getMoradorCep(Morador recebeMorador);
char getMoradorFace(Morador recebeMorador);
int getMoradorNum(Morador recebeMorador);
char *getMoradorCompl(Morador recebeMorador);
char *getMoradorNome(Morador recebeMorador);
char *getMoradorSobrenome(Morador recebeMorador);
char getMoradorSexo(Morador recebeMorador);
char *getMoradorNascimento(Morador recebeMorador);

void setMoradorCep(Morador recebeMorador, char* pCep);
void setMoradorFace(Morador recebeMorador, char pFace);
void setMoradorNum(Morador recebeMorador, int pNum);
void setMoradorCompl(Morador recebeMorador, char* pCompl);

void removeMorador(Morador recebeMorador);
int comparaMorador(Morador recebeMorador1, Morador recebeMorador2);
int comparaKeyMorador(Morador recebeMorador, char* key);

#endif
