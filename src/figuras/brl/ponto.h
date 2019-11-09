#ifndef ___PONTO_H_
#define ___PONTO_H_

typedef void* Ponto;

// cria uma instancia de ponto
Ponto criaPonto(double x,double y);
// retorna x do ponto
double getXPonto(Ponto M);
// retorna Y do ponto
double getYPonto(Ponto M);

#endif
