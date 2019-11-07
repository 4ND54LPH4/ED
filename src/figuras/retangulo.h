#ifndef RETANGULO
#define RETANGULO

typedef void *Retangulo;

Retangulo addRetangulo(char comandos[500],double rw);

char* getRetanguloID(Retangulo recebeRetangulo);
double getRetanguloX(Retangulo recebeRetangulo);
double getRetanguloY(Retangulo recebeRetangulo);
double getRetanguloAltura(Retangulo recebeRetangulo);
double getRetanguloLargura(Retangulo recebeRetangulo);
char *getRetanguloCfill(Retangulo recebeRetangulo);
char *getRetanguloCstrk(Retangulo recebeRetangulo);
double getRetanguloRw(Retangulo recebeRetangulo);

void setRetanguloX(Retangulo recebeRetangulo,double nX);
void setRetanguloY(Retangulo recebeRetangulo,double nY);

void removeRetangulo(Retangulo recebeRetangulo);
int comparaRetangulo(Retangulo recebeRetangulo1,Retangulo recebeRetangulo2);
int comparaIdRetangulo(Retangulo recebeRetangulo1,Retangulo recebeRetangulo2);
int comparaKeyRetangulo(Retangulo recebeRetangulo, char* key);

#endif
