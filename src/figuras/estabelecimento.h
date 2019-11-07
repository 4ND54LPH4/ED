#ifndef ESTABELECIMENTO
#define ESTABELECIMENTO
#define MAX 50
#include "estrutura/hash.h"

typedef void *Estabelecimento;

Estabelecimento addEstabelecimento(char comandos[500], tabelaHash hashPessoa, tabelaHash hashTipo);

char *getEstabelecimentoCnpj(Estabelecimento recebeEstabelecimento);
char *getEstabelecimentoCpf(Estabelecimento recebeEstabelecimento);
char *getEstabelecimentoCodt(Estabelecimento recebeEstabelecimento);
char *getEstabelecimentoCep(Estabelecimento recebeEstabelecimento);
char getEstabelecimentoFace(Estabelecimento recebeEstabelecimento);
int getEstabelecimentoNum(Estabelecimento recebeEstabelecimento);
char *getEstabelecimentoNome(Estabelecimento recebeEstabelecimento);
char *getEstabelecimentoDescricao(Estabelecimento recebeEstabelecimento);
char *getEstabelecimentoProprietarioNome(Estabelecimento recebeEstabelecimento);
char *getEstabelecimentoProprietarioSobrenome(Estabelecimento recebeEstabelecimento);
char getEstabelecimentoProprietarioSexo(Estabelecimento recebeEstabelecimento);
char *getEstabelecimentoProprietarioNascimento(Estabelecimento recebeEstabelecimento);

void removeEstabelecimento(Estabelecimento recebeEstabelecimento);
int comparaEstabelecimento(Estabelecimento recebeEstabelecimento1, Estabelecimento recebeEstabelecimento2);
int comparaKeyEstabelecimento(Estabelecimento recebeEstabelecimento, char* key);

#endif
