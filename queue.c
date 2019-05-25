#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

#include "structs.c"

void f_inicializar(Fila* f) {
  f->inicio = NULL;
  f->fim = NULL;
}

elemento_fila* f_criar_elemento(Vertice* v) {
  elemento_fila* novo = (elemento_fila*) malloc(sizeof(elemento_fila));
  novo->vertice = v;
  novo->prox = NULL;
  return novo;
}

bool f_eh_vazia(Fila f) {
  if(f.inicio == NULL) return true;
  return false;
}

void f_push(Fila* f, Vertice* v) {
  elemento_fila* novo = f_criar_elemento(v);
  if(f_eh_vazia(*f)) f->inicio = f->fim = novo;
  else {
    f->fim->prox = novo;
    f->fim = f->fim->prox;
  }
}

elemento_fila* f_pop(Fila* f) {
  if(f_eh_vazia(*f)) return NULL;
  elemento_fila* popped = f->inicio;
  if(f->inicio == f->fim) f->fim = NULL;
  f->inicio = f->inicio->prox;
  popped->prox = NULL;
  return popped;
}

// void imprimirFila(Fila f) {
//   elemento_fila* e = f.inicio;
//   printf("*****IMPRIMINDO FILA ATUAL*****\n\n");
//   while(e) {
//     printf("Elemento_fila: %i\n\n", e->vertice->chave);
//     e = e->prox;
//   }
// }
