#include "rbtree.h"
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include "../circulo.h"
#include "../retangulo.h"

struct node {
    struct node *objeto;
    int cor; /* 0 = preto; 1 = vermelho */
    struct node *left, *right, *pai;
};

struct tree {
    int (*cmpTree)(void *a, void *b);
    int (*cmpIdTree)(void *a, void *b);
    void (*delete)(void *a);
    void (*print)(char* arqSvg, void *a);
    struct node *raiz, *nil;
    unsigned int tamanho;
};

struct tree *criarTree(int (*cmpTreeFunc)(void*, void*), int (*cmpIdTreeFunc)(void*, void*), void (*deleteFunc)(void*), void (*printFunc)(char*, void*)) {
    struct tree *tree;
    struct node *temp;

    tree = (struct tree*)malloc(sizeof(struct tree));
    if (tree == NULL) return NULL;

    tree->cmpTree =  cmpTreeFunc;
    tree->cmpIdTree = cmpIdTreeFunc;
    tree->delete = deleteFunc;
    tree->print = printFunc;
    tree->tamanho = 0;

    /* inicializa os nodes de raiz e nil */
    temp = tree->nil = (struct node*)malloc(sizeof(struct node));
    temp->pai = temp->left = temp->right = temp;
    temp->cor = 0;
    temp->objeto = 0;

    temp = tree->raiz = (struct node*)malloc(sizeof(struct node));
    temp->pai = temp->left = temp->right = tree->nil;
    temp->cor = 0;
    temp->objeto = 0;

    return tree;
}

int verificaVazioTree(struct tree *tree) {
    return (tree->raiz->left == tree->nil);
}

unsigned int tamanhoTree(struct tree *tree) {
    return tree->tamanho;
}

struct node *beginTree(struct tree *tree) {
    struct node *x = tree->raiz->left;

    while (x->left != tree->nil)
	x = x->left;

    return x;
}

struct node *endTree(struct tree *tree) {
    return tree->nil;
}

// Funcao interna. Rotaciona para a esquerda
static void rotacionarLeftTree(struct tree *tree, struct node *x) {
    struct node *y, *nil = tree->nil;

    y = x->right;
    x->right = y->left;

    if (y->left != nil) y->left->pai = x;

    y->pai = x->pai;

    if (x == x->pai->left) {
	    x->pai->left = y;
    } else {
	    x->pai->right = y;
    }

    y->left = x;
    x->pai = y;

    assert(!tree->nil->cor);
}

// Funcao interna. Rotaciona para a direita
static void rotacionarRightTree(struct tree *tree, struct node *y) {
    struct node *x, *nil = tree->nil;

    x = y->left;
    y->left = x->right;

    if (nil != x->right) x->right->pai = y;

    x->pai = y->pai;

    if (y == y->pai->left) {
	    y->pai->left = x;
    } else {
	    y->pai->right = x;
    }

    x->right=y;
    y->pai=x;

    assert(!tree->nil->cor);
}


// Funcao interna usada por insertTree()
static void insertAuxTree(struct tree *tree, struct node *z) {
    struct node *x, *y, *nil = tree->nil;

    z->left = z->right = nil;
    y = tree->raiz;
    x = tree->raiz->left;

    while (x != nil) {
    	y = x;
    	if (tree->cmpTree(x->objeto, z->objeto) > 0) { /* x.objeto > z.objeto */
    	    x = x->left;
    	} else { /* x,objeto <= z.objeto */
    	    x = x->right;
    	}
    }
    z->pai = y;
    if ( (y == tree->raiz) || (tree->cmpTree(y->objeto, z->objeto) > 0) ) { /* y.objeto > z.objeto */
	    y->left = z;
    } else {
	    y->right = z;
    }

    assert(!tree->nil->cor);
}

struct node *insertTree(struct tree *tree, void *objeto) {
    struct node *x, *y, *newnode;

    x = (struct node*)malloc(sizeof(struct node));
    x->objeto = objeto;

    insertAuxTree(tree, x);
    newnode = x;
    x->cor = 1;

    while (x->pai->cor) {
    	if (x->pai == x->pai->pai->left) {
    	    y = x->pai->pai->right;
    	    if (y->cor) {
    		    x->pai->cor = 0;
    		    y->cor = 0;
    		    x->pai->pai->cor = 1;
    		    x = x->pai->pai;
    	    } else {
        		if (x == x->pai->right) {
        		    x = x->pai;
        		    rotacionarLeftTree(tree, x);
        		}
        		x->pai->cor = 0;
        		x->pai->pai->cor = 1;
        		rotacionarRightTree(tree, x->pai->pai);
    	    }
    	} else { /* caso x->pai == x->pai->pai->right */
    	    y = x->pai->pai->left;
    	    if (y->cor) {
        		x->pai->cor = 0;
        		y->cor = 0;
        		x->pai->pai->cor = 1;
        		x = x->pai->pai;
    	    } else {
        		if (x == x->pai->left) {
        		    x = x->pai;
        		    rotacionarRightTree(tree, x);
        		}
        		x->pai->cor = 0;
        		x->pai->pai->cor = 1;
        		rotacionarLeftTree(tree, x->pai->pai);
    	    }
    	}
    }

    tree->raiz->left->cor = 0;

    ++tree->tamanho;

#ifdef RBTREE_VERIFY
    assert(verificarTree(tree));
#endif

    return newnode;
}

struct node *sucessorTree(struct tree *tree, struct node *x) {
    struct node *y, *nil = tree->nil;
    struct node *raiz = tree->raiz;

    if (nil != (y = x->right)) {
    	while (y->left != nil) {
    	    y = y->left;
    	}
    	return y;
    } else {
    	y = x->pai;
    	while (x == y->right) {
    	    x = y;
    	    y = y->pai;
	    }
    	if (y == raiz) return nil;
    	return y;
    }
}

struct node *antecessorTree(struct tree *tree, struct node *x) {
    struct node *y, *nil = tree->nil;
    struct node *raiz = tree->raiz;

    if (nil != (y = x->left)) {
    	while (y->right != nil) {
    	    y = y->right;
    	}
    	return y;
    } else {
    	y = x->pai;
    	while (x == y->left) {
    	    if (y == raiz) return nil;
    	    x = y;
    	    y = y->pai;
    	}
    	return y;
    }
}

// Funcao interna para recursivamente deletar todos os nodes da arvore
static void deleteAuxTree(struct tree *tree, struct node *x) {
    if (x != tree->nil) {
    	deleteAuxTree(tree, x->left);
    	deleteAuxTree(tree, x->right);
    	tree->delete(x->objeto);
    	free(x);
    }
}

void deleteTree(struct tree *tree) {
    deleteAuxTree(tree, tree->raiz->left);
    free(tree->raiz);
    free(tree->nil);
    free(tree);
}

int Y_PRINT_ARVORE = 15;
// Funcao interna para recursivamente printar toda a arvore em ordem
static void printOrdenadoTree(struct tree *tree, int x1, struct node *x, char* nomeArq, char* (*printFunc)(void*, char*)) {
    FILE *arqSvg = fopen(nomeArq, "a+");

    if (x != tree->nil) {
        x1+=20;
    	printOrdenadoTree(tree, x1, x->left, nomeArq, printFunc);

        fprintf(arqSvg, "<circle r='5' cx='%d' cy='%d' stroke='black' fill='%s' stroke-width='1'/>\n", Y_PRINT_ARVORE, x1, x->cor == 0 ? "black" : "red");
        char dados[150];
        fprintf(arqSvg, "<text x='%d' y='%d' fill='black' font-size='5'>%s</text>\n", Y_PRINT_ARVORE, x1, printFunc(x->objeto, dados));

        Y_PRINT_ARVORE+=15;
    	printOrdenadoTree(tree, x1, x->right, nomeArq, printFunc);
    }
    fclose(arqSvg);
}

void printTree(struct tree *tree, char *nomeArq, char* (*printFunc)(void*, char*)) {
    printOrdenadoTree(tree, 0, tree->raiz->left, nomeArq, printFunc);
}

static void treeToSvgAux(struct tree *tree, struct node *x, char *nomeArq) {
    if (x != tree->nil) {
        treeToSvgAux(tree, x->left, nomeArq);
        tree->print(nomeArq, x->objeto);
        treeToSvgAux(tree, x->right, nomeArq);
    }
}

void treeToSvg(struct tree *tree, char *nomeArq) {
    treeToSvgAux(tree, tree->raiz->left, nomeArq);
}
/*
static void treeToSvgCirculo(struct tree *tree, struct node *x, char *nomeArq,char *cor) {
    FILE *boundingBox = NULL;

    if (x != tree->nil) {
        treeToSvgCirculo(tree, x->left, nomeArq,cor);
        tree->print(nomeArq, x->objeto);
        boundingBox = fopen(nomeArq,"a+");
        fprintf(boundingBox,"\t<rect x='%lf' y='%lf' width='%lf' height='%lf' stroke='%s' fill='%s' stroke-width='%lf'/>\n");
        fclose(boundingBox);
        treeToSvgCirculo(tree, x->right, nomeArq,cor);
    }

}

static void treeToSvgRetangulo(struct tree *tree, struct node *x, char *nomeArq,char *cor) {
    FILE *boundingBox = NULL;
    
    if (x != tree->nil) {
        treeToSvgAux(tree, x->left, nomeArq);
        tree->print(nomeArq, x->objeto);
        boundingBox = fopen(nomeArq,"a+");
        fprintf("");
        fclose(boundingBox);
        treeToSvgAux(tree, x->right, nomeArq);
    }

}

void treeToSvgBB(struct tree *tree, char *nomeArq,char *cor,int op) {
    if(op == 0) {
        treeToSvgCirculo(tree, tree->raiz->left, nomeArq,cor);
    } else if(op == 1) {
        treeToSvgRetangulo(tree, tree->raiz->left, nomeArq,cor);
    }
}*/

struct node *findTree(struct tree *tree, void *objeto) {
    struct node *x = tree->raiz->left;
    struct node *nil = tree->nil;
    int cmpval;

    if (x == nil) return NULL;

    cmpval = tree->cmpIdTree(x->objeto, objeto);

    while (cmpval != 0) {
    	if (cmpval > 0) { /* x->objeto > q */
    	    x = x->left;
    	} else {
    	    x = x->right;
    	}
    	if (x == nil) return NULL;

    	cmpval = tree->cmpIdTree(x->objeto, objeto);
    }

    while (x->left != nil && tree->cmpIdTree(objeto, x->left->objeto) == 0) {
	    x = x->left;
    }

    return x;
}

// Funcao interna para rebalancear a arvore depois de deletar um node
static void deleteFixTree(struct tree *tree, struct node *x) {
    struct node *raiz = tree->raiz->left;
    struct node *w;

    while ( (!x->cor) && (raiz != x) ) {
    	if (x == x->pai->left) {
    	    w = x->pai->right;
    	    if (w->cor) {
        		w->cor = 0;
        		x->pai->cor = 1;
        		rotacionarLeftTree(tree, x->pai);
        		w = x->pai->right;
    	    }
    	    if ( (!w->right->cor) && (!w->left->cor) ) {
        		w->cor = 1;
        		x = x->pai;
    	    } else {
        		if (!w->right->cor) {
        		    w->left->cor = 0;
        		    w->cor = 1;
        		    rotacionarRightTree(tree, w);
        		    w = x->pai->right;
        		}
        		w->cor = x->pai->cor;
        		x->pai->cor = 0;
        		w->right->cor = 0;
        		rotacionarLeftTree(tree, x->pai);
        		x = raiz;
    	    }
    	} else {
    	    w = x->pai->left;
    	    if (w->cor) {
        		w->cor = 0;
        		x->pai->cor = 1;
        		rotacionarRightTree(tree, x->pai);
        		w = x->pai->left;
    	    }
    	    if ( (!w->right->cor) && (!w->left->cor) ) {
        		w->cor = 1;
        		x = x->pai;
    	    } else {
        		if (!w->left->cor) {
        		    w->right->cor = 0;
        		    w->cor = 1;
        		    rotacionarLeftTree(tree, w);
        		    w = x->pai->left;
    		}
    		w->cor = x->pai->cor;
    		x->pai->cor = 0;
    		w->left->cor = 0;
    		rotacionarRightTree(tree, x->pai);
    		x = raiz;
    	    }
    	}
    }
    x->cor = 0;

    assert(!tree->nil->cor);
}

void deleteNodeTree(struct tree *tree, struct node *z) {
    struct node *x, *y, *nil = tree->nil;
    struct node *raiz = tree->raiz;


    y = ((z->left == nil) || (z->right == nil)) ? z : sucessorTree(tree, z);
    x = (y->left == nil) ? y->right : y->left;

    if (raiz == (x->pai = y->pai)) {
    	raiz->left = x;
    } else {
    	if (y == y->pai->left) {
    	    y->pai->left = x;
    	} else {
    	    y->pai->right = x;
    	}
    }
    if (y != z) {
    	assert( (y!=tree->nil) );

    	if (!(y->cor)) deleteFixTree(tree, x);

    	tree->delete(z->objeto);

    	y->left = z->left;
    	y->right = z->right;
    	y->pai = z->pai;
    	y->cor = z->cor;
    	z->left->pai = z->right->pai = y;

    	if (z == z->pai->left) {
    	    z->pai->left = y;
    	} else {
    	    z->pai->right = y;
    	}
    	free(z);
    } else {
    	tree->delete(y->objeto);

    	if (!(y->cor)) deleteFixTree(tree, x);
    	free(y);
    }

    --tree->tamanho;
#ifdef RBTREE_VERIFY
    assert(verificarTree(tree));
#endif
}

// Verifica as regras da arvore rubro-negra: a raiz e preta, os filhos de um node vermelho e preto e todo caminho da raiz para a folha tem o mesmo numero de nodes pretos
static int verificarAuxTree(struct tree *tree, struct node *z, int blacks, int *blackmatch, unsigned int *count) {
    if (z->cor) {
    	/* os dois filhos de um node vermelho devem ser pretos */
    	if (z->left->cor) return 0;
    	if (z->right->cor) return 0;
    }

    if (!z->cor) ++blacks;

    if (++(*count) > tree->tamanho)
    	return 0;

    if (z->left != tree->nil) {
    	if (!verificarAuxTree(tree, z->left, blacks, blackmatch, count))
    	    return 0;
    } else {
    	if (*blackmatch < 0)
    	    *blackmatch = blacks;
    	else if (*blackmatch != blacks)
    	    return 0;
    }

    if (z->right != tree->nil) {
    	if (!verificarAuxTree(tree, z->right, blacks, blackmatch, count))
    	    return 0;
    } else {
    	if (*blackmatch < 0)
    	    *blackmatch = blacks;
    	else if (*blackmatch != blacks)
    	    return 0;
    }

    return 1;
}

int verificarTree(struct tree *tree) {
    int blackmatch = -1;
    unsigned int count = 0;

    /* folha deve ser preta */
    if (tree->nil->cor) return 0;

    /* a raiz deve sempre ser preta */
    if (tree->raiz->left->cor) return 0;

    if (tree->raiz->left != tree->nil) {
    	if (!verificarAuxTree(tree, tree->raiz->left, 0, &blackmatch, &count))
    	    return 0;
    }

    if (count != tree->tamanho) return 0;

    return 1;
}

char* getCorNode(struct node *n) {
	struct node* node = (struct node*) n;
	return node->cor == 0 ? "Preto" : "Vermelho";
}

struct node* getRaizArvore(struct tree* t) {
    struct tree* tree = (struct tree*) t;
    return tree->raiz->left;
}

struct node* getNilArvore(struct tree* t) {
    struct tree* tree = (struct tree*) t;
    return tree->nil;
}

void* getObjetoNode(struct node* n) {
    struct node* node = (struct node*) n;
    return node->objeto;
}

struct node* getLeftNode(struct node* n) {
    struct node* node = (struct node*) n;
    return node->left;
}

struct node* getRightNode(struct node* n) {
    struct node* node = (struct node*) n;
    return node->right;
}

struct node* getPaiNode(struct node* n) {
    struct node* node = (struct node*) n;
    return node->pai;
}

/*struct node* next(struct tree* t, struct node* n) {
    struct tree* tree = (struct tree*) t;
    struct node* node = (struct node*) n;
    if (node == tree->nil) return tree->nil;

    if (node->left != tree->nil) {
        return node->left;
    } else if (node->right != tree->nil) {
        return node->right;
    } else {
        return node->pai;
    }
}
*/
