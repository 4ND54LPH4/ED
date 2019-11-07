#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ec.h"
#include "../util/util.h"

void processarComandosEc(char *estabComercial,char *localEntrada,char *localSaida,nx qtdFiguras) {
    // Variável para leitura da linha do arquivo
    char linhaArquivo[500];
    // Variáveis auxiliares para abertura do arquivo
    char *temp1 = NULL;
    char *temp2 = NULL;
    // Variáveis para controle da quantidade de figuras
    int totalFeitos = 0;
    // Variáveis dos arquivos de entrada e saída
    FILE *arquivoEntrada = NULL;
    FILE *arquivoSaida = NULL;

    // Abre o arquivo de comandos
    if(localEntrada == NULL) {
        arquivoEntrada = fopen(estabComercial,"r");
    } else {
        temp1 = getArquivo(localEntrada,estabComercial);
        arquivoEntrada = fopen(temp1,"r");
    }

    // Abre o arquivo svg de saída
    temp2 = getSvgSaida(localSaida,estabComercial);
    printf("TEMP2: %s\n\n",temp2);
    arquivoSaida = fopen(temp2,"w");

    if(arquivoEntrada == NULL) {
        printf("Erro ao abrir o arquivo geo\n");
        exit(0);
    }

    if(arquivoSaida == NULL) {
        printf("Erro ao criar arquivo\n");
        exit(0);
    }

    // Lê e executa comandos
    while(fgets(linhaArquivo,500,arquivoEntrada)!=NULL) {
        if(linhaArquivo[0]=='t' && linhaArquivo[1]==' ') {
            // Define o tipo de estabelecimento
            
        } else if(linhaArquivo[0]=='e' && linhaArquivo[1]==' ') {
            // Adiciona Estabelecimento
            
        }
    }

    // Fecha arquivos
    fclose(arquivoEntrada);
    fclose(arquivoSaida);
    free(temp1);
    free(temp2);
}