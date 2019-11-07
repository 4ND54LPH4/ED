#ifndef HIDRANTE
#define HIDRANTE
#define MAX 50

typedef void *Hidrante;

Hidrante addHidrante(char comandos[500],double ch,char cor1[MAX],char cor2[MAX]);

char *getHidranteId(Hidrante recebeHidrante);
double getHidranteX(Hidrante recebeHidrante);
double getHidranteY(Hidrante recebeHidrante);
char *getHidranteCfill(Hidrante recebeHidrante);
char *getHidranteCstrk(Hidrante recebeHidrante);
double getHidranteCh(Hidrante recebeHidrante);

void setHidranteX(Hidrante recebeHidrante,double nX);
void setHidranteY(Hidrante recebeHidrante,double nY);

void removeHidrante(Hidrante recebeHidrante);
char* printValorHidrante(Hidrante recebeHidrante, char *dados);
int comparaHidrante(Hidrante recebeHidrante1,Hidrante recebeHidrante2);
int comparaIdHidrante(Hidrante recebeHidrante1,Hidrante recebeHidrante2);
int comparaKeyHidrante(Hidrante recebeHidrante, char* key);

#endif
