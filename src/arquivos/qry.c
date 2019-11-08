#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "qry.h"
#include "../util/util.h"
#include "../svg/svg.h"


void processarComandosQry(char *pGeo,char *pQry,char *localEntrada,char *localSaida,nx qtdFiguras,
    struct tree **circulo,struct tree **retangulo,struct tree **texto,struct tree **hidrante,
    struct tree **quadra,struct tree **semaforo,struct tree **radio,struct tree **muro,struct tree **predio,
    struct tree **tipoEstabelecimento, struct tree **estabelecimento,struct tree **pessoa,struct tree**morador,
    tabelaHash **hashCirc,tabelaHash **hashRet,tabelaHash **hashHid,
    tabelaHash **hashQuad,tabelaHash **hashSem,tabelaHash **hashRad,
    tabelaHash **hashPrd,tabelaHash **hashTipEst,tabelaHash **hashEst,
    tabelaHash **hashPes,tabelaHash **hashMor) {
    // Variável para leitura da linha do arquivo
    char linhaArquivo[500];
    // Variáveis auxiliares para abertura do arquivo
    char *temp1 = NULL;
    char *temp2 = NULL;
    char *temp3 = NULL;
    // Variáveis dos arquivos de entrada e saída
    FILE *arquivoEntrada = NULL;
    FILE *arquivoSaidaSvg = NULL;
    FILE *arquivoSaidaTxt = NULL;

    // Abre o arquivo de pesquisa
    if(localEntrada == NULL) {
        arquivoEntrada = fopen(pQry,"r");
    } else {
        temp1 = getArquivo(localEntrada,pQry);
        arquivoEntrada = fopen(temp1,"r");
    }

    // Abre o arquivo svg de saída
    temp2 = getSvgSaidaQry(localSaida,pGeo,pQry);
    arquivoSaidaSvg = fopen(temp2,"w");

    // Abre o arquivo txt de saída
    temp3 = getTxtSaidaQry(localSaida,pGeo,pQry);
    arquivoSaidaTxt = fopen(temp3,"w");

    // Erro na abertura do arquivo
    if(arquivoEntrada == NULL) {
        printf("Erro ao abrir o arquivo geo\n");
        exit(0);
    }

    // Erro na criação do arquivo
    if(arquivoSaidaSvg == NULL || arquivoSaidaTxt == NULL) {
        printf("Erro ao criar arquivo\n");
        exit(0);
    }

    // Lê e executa comandos
    while(fgets(linhaArquivo,500,arquivoEntrada)!=NULL) {
        if(linhaArquivo[0]=='o' && linhaArquivo[1]=='?') {
            // Formas j e k se sobrepoem?
            printf("o\n");

        } else if(linhaArquivo[0]=='i' && linhaArquivo[1]=='?') {
            // Ponto (x,y) é interno a forma j?
            printf("i\n");


        } else if(linhaArquivo[0]=='d' && linhaArquivo[1]=='?') {
            // Distancia entre centros de massa das formas j e k?
            printf("d\n");

        } else if(linhaArquivo[0]=='b' && linhaArquivo[1]=='b') {
            // Cria novo arquivo svg contendo os circulos e retangulos referentes aos comandos c e r processados ate o momento.
            printf("bb\n");

        } else if(linhaArquivo[0]=='d' && linhaArquivo[1]=='q') {
            comandoDq(linhaArquivo, temp2, temp3, hidrante, semaforo, radio, quadra, (tabelaHash)hashHid, (tabelaHash)hashSem, (tabelaHash)hashRad, (tabelaHash)hashQuad);
            printf("dq\n");

        } else if(linhaArquivo[0]=='d' && linhaArquivo[1]=='e' && linhaArquivo[2]=='l') {
            // Remove a forma identificada por id (ou cep)
            printf("del\n");

        } else if(linhaArquivo[0]=='c' && linhaArquivo[1]=='b' && linhaArquivo[2]=='q') {
            // Muda a cor da borda de todas as quadras que estiverem inteiramente contidas dentro do circulo de centro em (x,y) e de raio r.
            printf("cbq\n");

        } else if(linhaArquivo[0]=='c' && linhaArquivo[1]=='r' && linhaArquivo[2]=='d') {
            // Imprime as coordenadas e a especie do equipamento urbano
            printf("crd\n");

        } else if(linhaArquivo[0]=='t' && linhaArquivo[1]=='r' && linhaArquivo[2]=='n') {
            // Desloca todas as quadras e equipamentos urbanos que estiverem inteiramente dentro do retangulo (x,y,w,h) em dx e dy unidades.
            printf("trans kkkkkkkkkkk\n");

        } else if(linhaArquivo[0]=='b' && linhaArquivo[1]=='r' && linhaArquivo[2]=='l') {
            // Detonada bomba de radiação luminosa na coordenada (x,y)
            printf("brl\n");

        } else if(linhaArquivo[0]=='f' && linhaArquivo[1]=='i') {
            // Foco de incendio. Encontrar os ns semaforos mais proximos do foco e os hidrantes que estejam a uma distancia de ate r do foco.
            printf("filho\n");

        } else if(linhaArquivo[0]=='f' && linhaArquivo[1]=='h') {
            // Determinar os k hidrantes mais proximos (se -k) ou mais distantes (se +k) do endereço.
            printf("fh\n");

        } else if(linhaArquivo[0]=='f' && linhaArquivo[1]=='s') {
            // Determinar os k semaforos mais proximos do endereço cep,face,num.
            printf("fs\n");

        } else if(linhaArquivo[0]=='b' && linhaArquivo[1]=='r' && linhaArquivo[2] == 'n') {
            //Detonada bomba de radiação nuclear na coordenada (x,y)
            printf("brn\n");

        } else if(linhaArquivo[0]=='m' && linhaArquivo[1]=='?') {
            //Moradores da quadra cujo cep é cep. Mostra mensagem de erro se quadra não existir.
            comandoMoradores(linhaArquivo, temp3, (tabelaHash)hashQuad, (tabelaHash)hashMor);

        } else if(linhaArquivo[0]=='m' && linhaArquivo[1]=='p' && linhaArquivo[2]=='l') {
            // Moradores dos prédios inteiramente contidos na região delimitada pelo polígono e as quadras que estão ao menos parcialmente dentro da delimitada pelo polígono.
            printf("mplg?\n");

        } else if(linhaArquivo[0]=='d' && linhaArquivo[1]=='m' && linhaArquivo[2]=='?') {
            //Imprime todos os dados do morador identificado pelo cpf.
            comandoDm(linhaArquivo, temp3, (tabelaHash)hashMor);

        } else if(linhaArquivo[0]=='d' && linhaArquivo[1]=='e' && linhaArquivo[2]=='?') {
            //Imprime todos os dados do estabelecimento comercial identificado por cnpj.
            comandoDe(linhaArquivo, temp3, (tabelaHash)hashEst);

        } else if(linhaArquivo[0]=='m' && linhaArquivo[1]=='u' && linhaArquivo[2]=='d') {
            //A pessoa identificada por cpf muda-se para o endereço determinado pelos parâmetros.
            comandoMud(linhaArquivo, temp3, (tabelaHash)hashMor);

        } else if(linhaArquivo[0]=='e' && linhaArquivo[1]=='p' && linhaArquivo[2]=='l') {
            //Estabelecimentos comerciais do tipo tp (ou de qualquer tipo, caso *) que estão inteiramente dentro da região delimitada pelo polígono.
            printf("eplg?\n");

        } else if(linhaArquivo[0]=='c' && linhaArquivo[1]=='a' && linhaArquivo[2]=='t') {
            //Considere a região delimitada pelo polígono. Remover as quadras que estejam inteiramente contidas no poligono. Remover prédios (inteiramente contidos no poligono) e respectivos moradores, hidrantes, semáforos, rádios-bases.
            printf("catac\n");

        } else if(linhaArquivo[0]=='d' && linhaArquivo[1]=='m' && linhaArquivo[2]=='p') {
            //Imprime o estado atual de uma árvore no arquivo arq.svg.
            comandoDmprbt(linhaArquivo, localSaida, hidrante, semaforo, radio, quadra, predio, muro);

        }
    }
    iniciarSvg(temp2);
    treeToSvg(*circulo, temp2);
    treeToSvg(*retangulo, temp2);
    treeToSvg(*texto, temp2);
    treeToSvg(*hidrante, temp2);
    treeToSvg(*quadra, temp2);
    treeToSvg(*semaforo, temp2);
    treeToSvg(*radio, temp2);
    treeToSvg(*predio, temp2);
    treeToSvg(*muro, temp2);
    finalizarSvg(temp2);

    // Fecha arquivo de leitura
    fclose(arquivoEntrada);
    fclose(arquivoSaidaSvg);
    fclose(arquivoSaidaTxt);
    free(temp1);
    free(temp2);
    free(temp3);
}
