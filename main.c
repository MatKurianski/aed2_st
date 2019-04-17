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

void inicializar_grafo(Grafo *g, int max) {
    g->inicio = NULL;
    
    int i;
    for(i = 0; i < max;) {
        Vertice *v = (Vertice*) malloc(sizeof(Vertice));
        v->cor = BRANCO;
        v->chave = i++;
        v->ordem, v->minor = -1;
        v->pai = NULL;
        v->prox = NULL;
        v->vizinhos = NULL;

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

void DFS_visit(Grafo g, Vertice *vertice) {
    vertice->cor = CINZA;

    Aresta *aresta = vertice->vizinhos;
    while(aresta) {
        Vertice *vizinho = aresta->vizinho;
        if(vizinho->cor == BRANCO) DFS_visit(g, vizinho);
        aresta = aresta->prox;
    }
    vertice->cor = PRETO;
    printf("%i\n", vertice->chave);
}

void DFS(Grafo g) {
    Vertice *vertice = g.inicio;

    while(vertice) {
        if(vertice->cor == BRANCO) DFS_visit(g, vertice);
        vertice = vertice->prox;
    }
}

int main() {
    Grafo g;
    inicializar_grafo(&g, 3);

    adiciona_aresta(g, 1, 2);
    adiciona_aresta(g, 2, 3);
    adiciona_aresta(g, 3, 1);

    DFS(g);
    return 0;
}