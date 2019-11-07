#ifndef MURO
#define MURO

typedef void *Muro;

Muro addMuro(char comandos[500],int pId);

int getMuroId(Muro recebeMuro);
double getMuroX1(Muro recebeMuro);
double getMuroY1(Muro recebeMuro);
double getMuroX2(Muro recebeMuro);
double getMuroY2(Muro recebeMuro);

void removeMuro(Muro recebeMuro);
char* printValorMuro(Muro recebeMuro, char *dados);
int comparaMuro(Muro recebeMuro1,Muro recebeMuro2);

#endif
