#include <stdio.h>
#include <malloc.h>
#include <stdbool.h>

typedef enum COR {
    BRANCO = 0,
    CINZA = 1,
    PRETO = 2,
} Cor;

typedef struct vertice Vertice;
typedef struct aresta Aresta;

// GRAFO

struct vertice {
    Cor cor;
    int chave, minor, ordem;
    Vertice *pai;
    Vertice *prox;
    Aresta *vizinhos;
};

struct aresta {
    Vertice *vizinho;
    Aresta *prox;
};

typedef struct {
    Vertice* inicio;
} Grafo;

// LISTA LIGADA RESULTANTE

typedef struct estrutura {
    Vertice* vertice;
    struct estrutura* esq;
    struct estrutura* dir;
} No;

typedef struct {
    No* inicio;
    No* fim;
} ListaLigada;

// Algoritmos da Lista Ligada

void inicializar_lista(ListaLigada *l) {
    l->inicio = NULL;
    l->fim = NULL;
}

void insere_elemento_no_final(ListaLigada *l, Vertice *v) {
    No* novo = (No*) malloc(sizeof(No));
    novo->vertice = v;
    novo->esq = novo->dir = NULL;

    if(l->inicio == NULL) l->inicio = novo;
    else {
        No* atual = l->fim;
        atual->dir = novo;
        novo->esq = atual;
    }
    l->fim = novo;
}

void insere_elemento(ListaLigada *l, Vertice *v, Vertice *pai) {
    if(l->inicio == NULL || pai == NULL) {
        insere_elemento_no_final(l, v);
        return;
    }
}

// Algoritmos do grafo

Vertice* criaVertice(int chave) {
    Vertice *v = (Vertice*) malloc(sizeof(Vertice));
    v->cor = BRANCO;
    v->chave = chave;
    v->ordem = v->minor = -1;
    v->pai = NULL;
    v->prox = NULL;
    v->vizinhos = NULL;
    return v;
}

void inicializar_grafo(Grafo *g, int max) {
    g->inicio = NULL;
    int i;
    for(i = 1; i <= max;) {
        Vertice *v = criaVertice(i++);
        if(g->inicio == NULL) g->inicio = v;
        else {
            Vertice *atual = g->inicio;
            while (atual->prox != NULL) atual = atual->prox;
            atual->prox = v;
        }
    }
}

Vertice* busca_vertice(Grafo g, int chave) {
    Vertice *atual = g.inicio;
    while(atual != NULL) {
        if(atual->chave == chave) return atual;
        atual = atual->prox;
    }
    return NULL;
}

void adiciona_aresta(Grafo g, int vertice, int vizinho) {
    Vertice* v = busca_vertice(g, vertice);
    Vertice* u = busca_vertice(g, vizinho);

    if(v == NULL || u == NULL) return;

    Aresta* nova = (Aresta*) malloc(sizeof(Aresta));
    nova->vizinho = u;
    nova->prox = NULL;

    if(v->vizinhos == NULL) v->vizinhos = nova;
    else {
        Aresta* atual = v->vizinhos;
        while(atual->prox != NULL) atual = atual->prox;
        atual->prox = nova;
    }
}

void adiciona_aresta_bidirecional(Grafo g, int vertice, int vizinho) {
    adiciona_aresta(g, vertice, vizinho);
    adiciona_aresta(g, vizinho, vertice);
}

void DFS_visit(Vertice *vertice) {
    vertice->cor = CINZA;

    Aresta *aresta = vertice->vizinhos;
    while(aresta) {
        Vertice *vizinho = aresta->vizinho;
        if(vizinho->cor == BRANCO) DFS_visit(vizinho);
        aresta = aresta->prox;
    }
    vertice->cor = PRETO;
    printf("%i\n", vertice->chave);
}

void DFS(Grafo g) {
    Vertice *vertice = g.inicio;

    while(vertice) {
        if(vertice->cor == BRANCO) DFS_visit(vertice);
        vertice = vertice->prox;
    }
}

void DFST_visit(Vertice *vertice, int *contador) {
    vertice->cor = CINZA;
    vertice->minor = vertice->ordem = *contador;
    *contador = *contador + 1;

    Aresta *aresta = vertice->vizinhos;
    while(aresta) {
        Vertice *vizinho = aresta->vizinho;
        if(vizinho->cor == BRANCO) {
            vizinho->pai = vertice;
            DFST_visit(vizinho, contador);
        }

        if(vertice->minor > vizinho->minor && vertice->pai != vizinho) {
            vertice->minor = vizinho->minor;
        }
        aresta = aresta->prox;
    }
    vertice->cor = PRETO;
}

bool DFST(Grafo g) {
    if(!g.inicio) return false;
    Vertice *atual = g.inicio;
    atual->pai = NULL;
    int contador = 1;
    
    DFST_visit(atual, &contador);

    while(atual) {
        if (
            (atual->cor == BRANCO || atual->minor >= atual->ordem) &&
            atual->chave != 1
        ) return false;
        atual = atual->prox;
    }

    return true;
}

int main() {
    Grafo g;
    inicializar_grafo(&g, 3);

    adiciona_aresta_bidirecional(g, 1, 2);
    adiciona_aresta_bidirecional(g, 2, 3);
    adiciona_aresta_bidirecional(g, 3, 1);

    if(DFST(g)) puts("É biconexo!");

    return 0;
}