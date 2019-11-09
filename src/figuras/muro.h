#ifndef MURO
#define MURO

typedef void *Muro;

Muro addMuro(char comandos[500],char* pId);

char* getMuroId(Muro recebeMuro);
float getMuroX1(Muro recebeMuro);
float getMuroY1(Muro recebeMuro);
float getMuroX2(Muro recebeMuro);
float getMuroY2(Muro recebeMuro);

void removeMuro(Muro recebeMuro);
char* printValorMuro(Muro recebeMuro, char *dados);
int comparaMuro(Muro recebeMuro1,Muro recebeMuro2);
int comparaKeyMuro(Muro recebeMuro,char *key);

#endif
