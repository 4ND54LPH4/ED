#ifndef UTIL
#define UTIL

void tratarParametros(char **pGeo,char **pQry,char **localEntrada,char **localSaida,char **estabComercial,char **pessoas);
void tratarArquivo(char **file);
void tratarLocal(char **local);

char *getArquivo(char *local,char *arquivo);
char *getSvgSaida(char *localSaida,char *arquivo);

//char *getNomeArquivo(char *arquivo);


/*
char *arquivoSaidaSvg(char *local,char *arquivo);
char *getNomeArquivo(char *arquivo);
char *saidaQryTxt(char *nomeArquivoGeo,char *nomeArquivoQry,char *localSaida);
char *saidaQryTxt(char *nomeArquivoGeo,char *nomeArquivoQry,char *localSaida);*/

char *tiraExtensao(char *arquivo);
char *tiraBarra(char *file);
void adicionaExtensao(char **arquivo,char *ext);

#endif