#ifndef QUADRA
#define QUADRA
#define MAX 50

typedef void *Quadra;

Quadra addQuadra(char comandos[500],float cq,char cfill[MAX],char cstrk[MAX]);

char *getQuadraId(Quadra recebeQuadra);
float getQuadraX(Quadra recebeQuadra);
float getQuadraY(Quadra recebeQuadra);
float getQuadraLargura(Quadra recebeQuadra);
float getQuadraAltura(Quadra recebeQuadra);
char *getQuadraCfill(Quadra recebeQuadra);
char *getQuadraCstrk(Quadra recebeQuadra);
float getQuadraCq(Quadra recebeQuadra);

void setQuadraX(Quadra recebeQuadra,float nX);
void setQuadraY(Quadra recebeQuadra,float nY);
void setQuadraCfill(Quadra recebeQuadra,char cfill[MAX]);
void setQuadraCstrk(Quadra recebeQuadra,char cstrk[MAX]);


void removeQuadra(Quadra recebeQuadra);
char* printValorQuadra(Quadra recebeQuadra, char *dados);
int comparaQuadra(Quadra recebeQuadra1,Quadra recebeQuadra2);
int comparaIdQuadra(Quadra recebeQuadra1,Quadra recebeQuadra2);
int comparaKeyQuadra(Quadra recebeQuadra, char* key);

#endif
