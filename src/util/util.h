#ifndef UTIL
#define UTIL

void tratarParametros(char **pGeo,char **pQry,char **localEntrada,char **localSaida,char **estabComercial,char **pessoas);
void tratarArquivo(char **file);
void tratarLocal(char **local);

char *getArquivo(char *local,char *arquivo);
char *getSvgSaida(char *localSaida,char *arquivo);
char *getSvgSaidaQry(char *localSaida,char *pGeo,char *pQry);
char *getSvgSaidaBB(char *localSaida,char *pGeo,char *pQry,char *sufixo);
char *getTxtSaidaQry(char *localSaida,char *pGeo,char *pQry);

char *tiraExtensao(char *arquivo);
char *tiraBarra(char *file);
void adicionaExtensao(char **arquivo,char *ext);

#endif
