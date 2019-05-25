#ifndef STRUCTS_C
#define STRUCTS_C

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
    int chave, minor, ordem, st_number;
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

// LISTA LIGADA

typedef struct estrutura {
    Vertice* vertice;
    struct estrutura* esq;
    struct estrutura* dir;
} No;

typedef struct {
    No* inicio;
    No* fim;
} ListaLigada;

// FILA

typedef struct elem {
  Vertice* vertice;
  struct elem* prox;
} elemento_fila;

typedef struct {
  elemento_fila* inicio;
  elemento_fila* fim;
} Fila;

#endif