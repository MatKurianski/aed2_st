#include "structs.c"

// Algoritmos da Lista Ligada

No* criar_no(Vertice *v) {
    No* novo = (No*) malloc(sizeof(No));
    novo->vertice = v;
    novo->esq = novo->dir = NULL;
    return novo;
} 

void inicializar_lista(ListaLigada *l) {
    l->inicio = NULL;
    l->fim = NULL;
}

No* buscar_no(ListaLigada l, Vertice *v) {
    No* atual = l.inicio;
    while(atual) {
        if(atual->vertice == v) return atual;
        atual = atual->dir;
    }
    return NULL;
}

void insere_elemento_no_final(ListaLigada *l, Vertice *v) {
    No* novo = criar_no(v);

    if(l->inicio == NULL) l->inicio = novo;
    else {
        No* atual = l->fim;
        atual->dir = novo;
        novo->esq = atual;
    }
    l->fim = novo;
}

void insere_elemento(ListaLigada *l, Vertice *v, No *pai, char* pos) {
    if(l->inicio == NULL || pai == NULL) {
        insere_elemento_no_final(l, v);
        return;
    }

    No* novo = criar_no(v);
    if(pos == "esq") {
        if(pai->esq == NULL) l->inicio = novo;
        else {
            novo->esq = pai->esq;
            pai->esq->dir = novo;
        }
        novo->dir = pai;
        pai->esq = novo;
    } else if(pos == "dir") {
        if(pai->dir == NULL) l->fim = novo;
        else {
            novo->dir = pai->dir;
            pai->dir->esq = novo;
        }
        novo->esq = pai;
        pai->dir = novo;
    } else {
        puts("error");
        return;
    }
}
