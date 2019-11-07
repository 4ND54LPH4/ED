#ifndef NX
#define NX

typedef void *nx;

nx criaNx();
nx getNx(nx recebeNx,char *localEntrada,char *fileGeo);
nx iniciaNx(nx recebeNx);

int contadorEspacosNx(char *localEntrada,char *fileGeo);
int getINx(nx recebeNx);
int getNqNx(nx recebeNx);
int getNhNx(nx recebeNx);
int getNsNx(nx recebeNx);
int getNrNx(nx recebeNx);
int getNpNx(nx recebeNx);
int getNmNx(nx recebeNx);

#endif