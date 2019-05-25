#include<stdio.h>
#include<stdlib.h>

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

void f_push(Fila* f, Vertice* v) {
  elemento_fila* novo = f_criar_elemento(v);
  if(f->inicio == NULL) f->inicio = f->fim = novo;
  else {
    f->fim->prox = novo;
    f->fim = f->fim->prox;
  }
}

elemento_fila* f_pop(Fila* f) {
  if(f->fim == NULL) return NULL;
  elemento_fila* popped = f->inicio;
  popped->prox = NULL;
  f->inicio = f->inicio->prox;
  return popped;
}
