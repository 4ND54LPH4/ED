#ifndef CIRCULO
#define CIRCULO

typedef void *Circulo;

Circulo addCirculo(char comandos[500],double cw);

char* getCirculoID(Circulo recebeCirculo);
double getCirculoX(Circulo recebeCirculo);
double getCirculoY(Circulo recebeCirculo);
double getCirculoRaio(Circulo recebeCirculo);
char *getCirculoCfill(Circulo recebeCirculo);
char *getCirculoCstrk(Circulo recebeCirculo);
double getCirculoCw(Circulo recebeCirculo);

void setCirculoX(Circulo recebeCirculo,double nX);
void setCirculoY(Circulo recebeCirculo,double nY);

void removeCirculo(Circulo recebeCirculo);
int comparaCirculo(Circulo recebeCirculo1,Circulo recebeCirculo2);
int comparaIdCirculo(Circulo recebeCirculo1,Circulo recebeCirculo2);
int comparaKeyCirculo(Circulo recebeCirculo, char *key);

#endif
