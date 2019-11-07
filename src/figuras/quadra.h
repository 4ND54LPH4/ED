#ifndef QUADRA
#define QUADRA
#define MAX 50

typedef void *Quadra;

Quadra addQuadra(char comandos[500],double cq,char cfill[MAX],char cstrk[MAX]);

char *getQuadraId(Quadra recebeQuadra);
double getQuadraX(Quadra recebeQuadra);
double getQuadraY(Quadra recebeQuadra);
double getQuadraLargura(Quadra recebeQuadra);
double getQuadraAltura(Quadra recebeQuadra);
char *getQuadraCfill(Quadra recebeQuadra);
char *getQuadraCstrk(Quadra recebeQuadra);
double getQuadraCq(Quadra recebeQuadra);

void setQuadraX(Quadra recebeQuadra,double nX);
void setQuadraY(Quadra recebeQuadra,double nY);
void setQuadraCfill(Quadra recebeQuadra,char cfill[MAX]);
void setQuadraCstrk(Quadra recebeQuadra,char cstrk[MAX]);


void removeQuadra(Quadra recebeQuadra);
void printValorQuadra(Quadra recebeQuadra);
int comparaQuadra(Quadra recebeQuadra1,Quadra recebeQuadra2);
int comparaIdQuadra(Quadra recebeQuadra1,Quadra recebeQuadra2);

#endif