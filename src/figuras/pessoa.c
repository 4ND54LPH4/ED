#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pessoa.h"


typedef struct pessoa {
    char cpf[15];
    char nome[MAX],sobrenome[MAX];
    char sexo;
    char nascimento[11];
    
} *pPessoa;