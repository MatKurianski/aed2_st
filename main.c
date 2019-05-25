#include <stdio.h>
#include <malloc.h>
#include <stdbool.h>
#include <limits.h>

#include "structs.c"
#include "lista_ligada.c"
#include "queue.c"

Vertice* criaVertice(int chave) {
    Vertice *v = (Vertice*) malloc(sizeof(Vertice));
    v->cor = BRANCO;
    v->chave = chave;
    v->ordem = v->minor = v->st_number = -1;
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
}

void DFS(Grafo g) {
    Vertice *vertice = g.inicio;

    while(vertice) {
        if(vertice->cor == BRANCO) DFS_visit(vertice);
        vertice = vertice->prox;
    }
}

void visita_topologica(Grafo g, Vertice* v, ListaLigada *l) {
  v->cor = CINZA;
  insere_elemento_no_final(l, v);
  Aresta* aresta = v->vizinhos;
  while(aresta) {
    Vertice* vizinho = aresta->vizinho;
    if(vizinho->cor == BRANCO) visita_topologica(g, vizinho, l);
    aresta = aresta->prox;
  }
  v->cor = PRETO;
}

ListaLigada ordenacao_topologica(Grafo g) {
  Vertice* v = g.inicio;
  ListaLigada l;
  inicializar_lista(&l);

  while(v) {
    if(v->cor == BRANCO) visita_topologica(g, v, &l);
    v = v->prox;
  }
  return l;
}

void BFS(Grafo g) {
  Vertice* atual = g.inicio;
  while(atual) {
    atual->cor = BRANCO;
    atual->ordem = INT_MAX;
    atual->pai = NULL;
    atual = atual->prox;
  }

  atual = g.inicio;
  atual->cor = CINZA;
  atual->ordem = 0;

  Fila f;
  f_inicializar(&f);
  f_push(&f, atual);

  while(!f_eh_vazia(f)) {
    Vertice* vertice = f_pop(&f)->vertice;
    // imprimirFila(f);
    Aresta* aresta = vertice->vizinhos;

    while(aresta) {
      Vertice* vizinho = aresta->vizinho;
      if(vizinho->cor == BRANCO) {
        vizinho->cor = CINZA;
        vizinho->ordem = vertice->ordem + 1;
        vizinho->pai = vertice;
        f_push(&f, vizinho);
      }
      aresta = aresta->prox;
    }
    printf("%i ", vertice->chave);
    vertice->cor = PRETO;
  }
}

int main() {
    Grafo g;
    inicializar_grafo(&g, 6);

    adiciona_aresta(g, 1, 2);
    adiciona_aresta(g, 1, 3);
    adiciona_aresta(g, 1, 6);

    adiciona_aresta(g, 2, 4);
    adiciona_aresta(g, 2, 5);

    BFS(g);

    printf("\n");
    return 0;
}