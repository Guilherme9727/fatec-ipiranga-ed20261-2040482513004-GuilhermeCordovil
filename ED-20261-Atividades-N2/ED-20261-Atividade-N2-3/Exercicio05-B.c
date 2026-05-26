// RA: 2040482513004 - Guilherme Cordovil Quirino Gomes

#include <stdio.h>
#include <stdlib.h>

typedef struct No {
    int dado;
    struct No *esq;
    struct No *dir;
} No;

No *criarNo(int valor) {
    No *novo = (No *)malloc(sizeof(No));
    if (novo == NULL) { printf("Erro de memoria.\n"); exit(1); }
    novo->dado = valor;
    novo->esq  = NULL;
    novo->dir  = NULL;
    return novo;
}

No *inserir(No *raiz, int valor) {
    if (raiz == NULL) return criarNo(valor);
    if (valor < raiz->dado) raiz->esq = inserir(raiz->esq, valor);
    else if (valor > raiz->dado) raiz->dir = inserir(raiz->dir, valor);
    return raiz;
}

/* Retorna -1 para no nulo; altura do no caso contrario */
int alturaNo(No *no) {
    if (no == NULL) return -1;
    int altEsq = alturaNo(no->esq);
    int altDir = alturaNo(no->dir);
    return ((altEsq > altDir) ? altEsq : altDir) + 1;
}

/* Busca o no pelo valor e retorna sua altura; -1 se nao encontrado */
int alturaValor(No *raiz, int valor) {
    if (raiz == NULL) return -1;
    if (raiz->dado == valor) return alturaNo(raiz);
    if (valor < raiz->dado) return alturaValor(raiz->esq, valor);
    return alturaValor(raiz->dir, valor);
}

/* Retorna -1 se o valor nao existir na arvore */
int profundidadeNo(No *raiz, int valor, int prof) {
    if (raiz == NULL) return -1;
    if (raiz->dado == valor) return prof;
    if (valor < raiz->dado) return profundidadeNo(raiz->esq, valor, prof + 1);
    return profundidadeNo(raiz->dir, valor, prof + 1);
}

int grauNo(No *no) {
    if (no == NULL) return 0;
    int g = 0;
    if (no->esq != NULL) g++;
    if (no->dir != NULL) g++;
    return g;
}

/* Percurso em-ordem imprimindo grau de cada no */
void percursoGrau(No *raiz) {
    if (raiz == NULL) return;
    percursoGrau(raiz->esq);
    printf("  No %2d: grau %d\n", raiz->dado, grauNo(raiz));
    percursoGrau(raiz->dir);
}

void liberarArvore(No *raiz) {
    if (raiz == NULL) return;
    liberarArvore(raiz->esq);
    liberarArvore(raiz->dir);
    free(raiz);
}

int main(void) {
    No *raiz = NULL;

    int valores[] = {50, 30, 70, 20, 40, 60, 80, 10, 25, 45, 65};
    int qtd = (int)(sizeof(valores) / sizeof(valores[0]));
    for (int i = 0; i < qtd; i++) raiz = inserir(raiz, valores[i]);

    /* -------------------------------------------------------
     * a) Altura dos nos: 50, 30, 70, 20 e 10
     * ------------------------------------------------------- */
    printf("=== a) Alturas ===\n");
    int consultaAltura[] = {50, 30, 70, 20, 10};
    for (int i = 0; i < 5; i++) {
        int v = consultaAltura[i];
        printf("  altura(%d) = %d\n", v, alturaValor(raiz, v));
    }

    /* -------------------------------------------------------
     * b) Profundidade dos nos: 50, 30, 70, 45 e 10
     * ------------------------------------------------------- */
    printf("\n=== b) Profundidades ===\n");
    int consultaProf[] = {50, 30, 70, 45, 10};
    for (int i = 0; i < 5; i++) {
        int v = consultaProf[i];
        printf("  profundidade(%d) = %d\n", v, profundidadeNo(raiz, v, 0));
    }

    /* -------------------------------------------------------
     * c) Grau de cada no (percurso em-ordem)
     * ------------------------------------------------------- */
    printf("\n=== c) Grau de cada no (em-ordem) ===\n");
    percursoGrau(raiz);

    /* -------------------------------------------------------
     * d) Altura total da arvore
     * ------------------------------------------------------- */
    printf("\n=== d) Altura total da arvore ===\n");
    printf("  altura(raiz) = %d\n", alturaNo(raiz));

    liberarArvore(raiz);
    return 0;
}
