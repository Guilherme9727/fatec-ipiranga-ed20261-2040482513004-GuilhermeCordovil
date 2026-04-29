/*----------------------------------------------------------------------------------*/
/*FATEC-Ipiranga                                                                    */         
/*ADS - Estrutura de Dados                                                          */
/*Atividade: N2-1                                                                   */
/*Objetivo: Explorando Árvore Binária                                               */
/*                                                                                  */
/*Autor: Guilherme Cordovil                                                         */
/*Data: 28/04/2026                                                                  */
/*----------------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arvore_binaria.h"

#define PREFIXO_MAX 1024

No* criar_no(int valor) {
    No *novo = (No *) malloc(sizeof(No));
    if (!novo) { perror("malloc"); exit(EXIT_FAILURE); }
    novo->valor = valor;
    novo->esq   = NULL;
    novo->dir   = NULL;
    return novo;
}

No* inserir(No *raiz, int valor) {
    if (!raiz)               return criar_no(valor);
    if (valor < raiz->valor) raiz->esq = inserir(raiz->esq, valor);
    else if (valor > raiz->valor) raiz->dir = inserir(raiz->dir, valor);
    return raiz;
}

No* buscar_no(No *raiz, int valor) {
    if (!raiz)                return NULL;
    if (valor == raiz->valor) return raiz;
    if (valor <  raiz->valor) return buscar_no(raiz->esq, valor);
    return                           buscar_no(raiz->dir, valor);
}

void imprimir_raiz(No *raiz) {
    printf("Raiz:\n");
    if (raiz) printf("%d\n", raiz->valor);
    else      printf("(arvore vazia)\n");
}

static void _nos_internos(No *no, int *primeiro) {
    if (!no) return;
    if (no->esq || no->dir) {
        if (!*primeiro) printf(", ");
        printf("%d", no->valor);
        *primeiro = 0;
    }
    _nos_internos(no->esq, primeiro);
    _nos_internos(no->dir, primeiro);
}

void listar_nos_internos(No *raiz) {
    printf("Nos Internos:\n");
    int primeiro = 1;
    _nos_internos(raiz, &primeiro);
    printf("\n");
}

static void _folhas(No *no, int *primeiro) {
    if (!no) return;
    if (!no->esq && !no->dir) {
        if (!*primeiro) printf(", ");
        printf("%d", no->valor);
        *primeiro = 0;
    }
    _folhas(no->esq, primeiro);
    _folhas(no->dir, primeiro);
}

void listar_folhas(No *raiz) {
    printf("Nos Externos (Folhas):\n");
    int primeiro = 1;
    _folhas(raiz, &primeiro);
    printf("\n");
}

static void _nos_nivel(No *no, int nivel_atual, int nivel_alvo, int *primeiro) {
    if (!no) return;
    if (nivel_atual == nivel_alvo) {
        if (!*primeiro) printf(", ");
        printf("%d", no->valor);
        *primeiro = 0;
        return;
    }
    _nos_nivel(no->esq, nivel_atual + 1, nivel_alvo, primeiro);
    _nos_nivel(no->dir, nivel_atual + 1, nivel_alvo, primeiro);
}

void imprimir_todos_niveis(No *raiz, int total_niveis) {
    printf("Niveis:\n");
    for (int i = 1; i <= total_niveis; i++) {
        printf("Nivel %d: ", i);
        int primeiro = 1;
        _nos_nivel(raiz, 1, i, &primeiro);
        if (primeiro) printf("(vazio)");
        printf("\n");
    }
}

int grau_no(No *no) {
    if (!no) return -1;
    return (no->esq ? 1 : 0) + (no->dir ? 1 : 0);
}

static void _grau_todos(No *no) {
    if (!no) return;
    printf("%d -> grau %d\n", no->valor, grau_no(no));
    _grau_todos(no->esq);
    _grau_todos(no->dir);
}

void imprimir_grau_todos(No *raiz) {
    printf("Grau dos Nos:\n");
    _grau_todos(raiz);
}

static int _ancestrais(No *no, int valor, int *primeiro) {
    if (!no) return 0;
    if (no->valor == valor) return 1;
    if (_ancestrais(no->esq, valor, primeiro) ||
        _ancestrais(no->dir, valor, primeiro)) {
        if (!*primeiro) printf(", ");
        printf("%d", no->valor);
        *primeiro = 0;
        return 1;
    }
    return 0;
}

void imprimir_ancestrais(No *raiz, int valor) {
    printf("Ancestrais de %d:\n", valor);
    int primeiro = 1;
    int encontrado = _ancestrais(raiz, valor, &primeiro);
    if (!encontrado)   printf("(no nao encontrado)");
    else if (primeiro) printf("(nenhum - e a raiz)");
    printf("\n");
}

static void _todos_desc(No *no, int *primeiro) {
    if (!no) return;
    if (!*primeiro) printf(", ");
    printf("%d", no->valor);
    *primeiro = 0;
    _todos_desc(no->esq, primeiro);
    _todos_desc(no->dir, primeiro);
}

static int _descendentes(No *no, int valor, int *primeiro) {
    if (!no) return 0;
    if (no->valor == valor) {
        _todos_desc(no->esq, primeiro);
        _todos_desc(no->dir, primeiro);
        return 1;
    }
    return _descendentes(no->esq, valor, primeiro) ||
           _descendentes(no->dir, valor, primeiro);
}

void imprimir_descendentes(No *raiz, int valor) {
    printf("Descendentes de %d:\n", valor);
    int primeiro = 1;
    int encontrado = _descendentes(raiz, valor, &primeiro);
    if (!encontrado)   printf("(no nao encontrado)");
    else if (primeiro) printf("(nenhum - e folha)");
    printf("\n");
}

static int _altura_subarvore(No *no) {
    if (!no) return -1;
    int esq = _altura_subarvore(no->esq);
    int dir = _altura_subarvore(no->dir);
    return 1 + (esq > dir ? esq : dir);
}

static int _altura_no(No *no, int valor) {
    if (!no) return -2;
    if (no->valor == valor) return _altura_subarvore(no);
    int res = _altura_no(no->esq, valor);
    if (res != -2) return res;
    return _altura_no(no->dir, valor);
}

int altura_no(No *raiz, int valor) {
    return _altura_no(raiz, valor);
}

int profundidade_no(No *raiz, int valor, int prof_atual) {
    if (!raiz)                return -1;
    if (raiz->valor == valor) return prof_atual;
    int res = profundidade_no(raiz->esq, valor, prof_atual + 1);
    if (res != -1) return res;
    return profundidade_no(raiz->dir, valor, prof_atual + 1);
}

static void _print_subarvore(No *no, char *prefixo, int eh_raiz) {
    if (!no) return;

    if (eh_raiz) printf("%d\n", no->valor);

    No  *lista[2];
    int  n = 0;
    if (no->esq) lista[n++] = no->esq;
    if (no->dir) lista[n++] = no->dir;

    for (int i = 0; i < n; i++) {
        int ultimo = (i == n - 1);
        printf("%s%s%d\n",
               prefixo,
               ultimo ? "\xe2\x94\x94\xe2\x94\x80\xe2\x94\x80 "
                      : "\xe2\x94\x9c\xe2\x94\x80\xe2\x94\x80 ",
               lista[i]->valor);

        char novo_prefixo[PREFIXO_MAX];
        snprintf(novo_prefixo, PREFIXO_MAX, "%s%s",
                 prefixo,
                 ultimo ? "    " : "\xe2\x94\x82   ");

        _print_subarvore(lista[i], novo_prefixo, 0);
    }
}

void imprimir_subarvore_por_valor(No *raiz, int valor) {
    No *alvo = buscar_no(raiz, valor);
    printf("Subarvore (raiz %d):\n", valor);
    if (!alvo) {
        printf("(no nao encontrado)\n");
        return;
    }
    _print_subarvore(alvo, "", 1);
}
