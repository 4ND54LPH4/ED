#ifndef TEXTO
#define TEXTO

typedef void *Texto;

Texto addTexto(char comandos[500]);

double getTextoX(Texto recebeTexto);
double getTextoY(Texto recebeTexto);
char *getTextoTexto(Texto recebeTexto);

void removeTexto(Texto recebeTexto);

#endif