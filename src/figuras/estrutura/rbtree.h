#ifndef _RBTREE_H
#define _RBTREE_H 1


// declaracao das structs
struct node;
struct tree;

/**
 * - cmpTree(a,b) deve retornar >0 if *a > *b, <0 if *a < *b ou =0 if *a == *b
 * - delete(a) recebe um ponteiro para um objeto e deve dar free nesse objeto
 * - print(a) e usado por printTree() para printar a arvore
*/

// Cria uma nova arvore rubro negra. Todos os ponteiros das funcoes devem ser passados como parametros. Retorna um novo objeto de arvore
struct tree *criarTree(int (*cmpTreeFunc)(void*, void*), int (*cmpIdTreeFunc)(void*, void*), void (*deleteFunc)(void*), char* (*printFunc)(void*, char*));

// Retorna true se a arvore esta vazio
int verificaVazioTree(struct tree *tree);

// Retorna o numero de elementos na arvore
unsigned int tamanhoTree(struct tree *tree);

// Retorna o primeiro elemento ou nil
struct node *beginTree(struct tree *tree);

// Retorna o elemento nil
struct node *endTree(struct tree *tree);

// Funcao de insercao na arvore. Primeiro insere um novo node depois faz rotacoes para balancear arvore
struct node *insertTree(struct tree *tree, void *objeto);

// Retorna o node sucessor de x na arvore ou tree->nil se nao tiver
struct node *sucessorTree(struct tree *tree, struct node *x);

// Retorna o node antecessor de x na arovre ou tree->nil se nao tiver
struct node *antecessorTree(struct tree *tree, struct node *x);

// Deleta a arvore e todos seus nodes
void deleteTree(struct tree *tree);

// Printar toda a arvore utilizando a funcao print do objeto
void printTree(struct tree *tree, char *nomeArq);

// Procura o primeiro node correspondente a key. Retorna NULL se nao encontrar
struct node *findTree(struct tree *tree, void *objeto);

// Deleta um node da arvore e a rebalanceia
void deleteNodeTree(struct tree *tree, struct node *z);

// Verifica as regras da arvore rubro-negra: a raiz e preta, os filhos de um node vermelho e preto e todo caminho da raiz para a folha tem o mesmo numero de nodes pretos
int verificarTree(struct tree *tree);

// Getters arvore
char* getCorNode(struct node *n);
struct node* getRaizArvore(struct tree* t);
struct node* getNilArvore(struct tree* t);
void* getObjetoNode(struct node* n);
struct node* getLeftNode(struct node* n);
struct node* getRightNode(struct node* n);
struct node* getPaiNode(struct node* n);

#endif
