#ifndef TIPOESTABELECIMENTO
#define TIPOESTABELECIMENTO
#define MAX 50

typedef void *TipoEstabelecimento;

TipoEstabelecimento addTipoEstabelecimento(char comandos[500]);

char *getTipoEstabelecimentoCodt(TipoEstabelecimento recebeTipoEstabelecimento);
char *getTipoEstabelecimentoDescricao(TipoEstabelecimento recebeTipoEstabelecimento);

void removeTipoEstabelecimento(TipoEstabelecimento recebeTipoEstabelecimento);
int comparaTipoEstabelecimento(TipoEstabelecimento recebeTipoEstabelecimento1, TipoEstabelecimento recebeTipoEstabelecimento2);
int comparaKeyTipoEstabelecimento(TipoEstabelecimento recebeTipoEstabelecimento, char* key);

#endif
