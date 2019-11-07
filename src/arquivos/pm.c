#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ec.h"
#include "../util/util.h"
#include "../figuras/figuras.h"
#include "../figuras/estrutura/rbtree.h"
#include "../figuras/estrutura/hash.h"

void processarComandosPm(char *pessoas,char *localEntrada,char *localSaida,nx qtdFiguras, struct tree **pessoa, struct tree **morador, tabelaHash **hashPes, tabelaHash **hashMor) {
    // Variável para leitura da linha do arquivo
    char linhaArquivo[500];
    // Variáveis auxiliares para abertura do arquivo
    char *temp1 = NULL;
    char *temp2 = NULL;
    // Variáveis para controle da quantidade de figuras
    int totalFeitos = 0;
    // Variáveis das trees das figuras
    *pessoa = criarTree(comparaPessoa, comparaPessoa, removePessoa, NULL);
    *morador = criarTree(comparaMorador, comparaMorador, removeMorador, NULL);
    // Variáveis das hash das figuras
    *hashPes = criarTabelaHash(1000, comparaKeyPessoa, getPessoaCpf);
    *hashMor = criarTabelaHash(1000, comparaKeyMorador, getMoradorCpf);
    // Variáveis dos arquivos de entrada e saída
    FILE *arquivoEntrada = NULL;
    FILE *arquivoSaida = NULL;

    // Abre o arquivo de comandos
    if(localEntrada == NULL) {
        arquivoEntrada = fopen(pessoas,"r");
    } else {
        temp1 = getArquivo(localEntrada,pessoas);
        arquivoEntrada = fopen(temp1,"r");
    }

    // Abre o arquivo svg de saída
    temp2 = getSvgSaida(localSaida,pessoas);
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
        if(linhaArquivo[0]=='p' && linhaArquivo[1]==' ') {
            // Adiciona pessoa
            Pessoa tempPessoa = addPessoa(linhaArquivo);
            insertTree(*pessoa, tempPessoa);
            inserirHash(*hashPes, tempPessoa);
        } else if(linhaArquivo[0]=='m' && linhaArquivo[1]==' ') {
            // Insere endereço
            Morador tempMorador = addMorador(linhaArquivo, *hashPes);
            Pessoa tempPes = getObjetoHash(*hashPes, getMoradorCpf(tempMorador));
            if (getPessoaCpf(tempPes) != NULL) {
                insertTree(*morador, tempMorador);
                inserirHash(*hashMor, tempMorador);
            } else {
                printf("Pessoa nao cadastrada!\n");
            }
        }
    }

    // Fecha arquivos
    fclose(arquivoEntrada);
    fclose(arquivoSaida);
    free(temp1);
    free(temp2);
}
