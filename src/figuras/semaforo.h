#ifndef SEMAFORO
#define SEMAFORO
#define MAX 50

typedef void *Semaforo;

Semaforo addSemaforo(char comandos[500],double cs,char cor1[MAX],char cor2[MAX]);

char *getSemaforoId(Semaforo recebeSemaforo);
double getSemaforoX(Semaforo recebeSemaforo);
double getSemaforoY(Semaforo recebeSemaforo);
char *getSemaforoCfill(Semaforo recebeSemaforo);
char *getSemaforoCstrk(Semaforo recebeSemaforo);
double getSemaforoCs(Semaforo recebeSemaforo);

void setSemaforoX(Semaforo recebeSemaforo,double nX);
void setSemaforoY(Semaforo recebeSemaforo,double nY);

void removeSemaforo(Semaforo recebeSemaforo);
void printValorSemaforo(Semaforo recebeSemaforo);
int comparaSemaforo(Semaforo recebeSemaforo1,Semaforo recebeSemaforo2);
int comparaIdSemaforo(Semaforo recebeSemaforo1,Semaforo recebeSemaforo2);


#endif