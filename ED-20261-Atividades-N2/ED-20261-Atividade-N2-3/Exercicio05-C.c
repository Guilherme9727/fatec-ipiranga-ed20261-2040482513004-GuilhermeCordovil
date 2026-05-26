// RA: 2040482513004 - Guilherme Cordovil Quirino Gomes

/*
 * =======================================================================
 * PARTE C — Verificacao manual da estrutura da ABB (ASCII Art)
 *
 * Sequencia de insercao: 50, 30, 70, 20, 40, 60, 80, 10, 25, 45, 65
 *
 *                        50              <- raiz (prof=0, alt=3, grau=2)
 *                      /    \
 *                    30      70          <- prof=1, alt=2, grau=2 cada
 *                   /  \    /  \
 *                 20   40  60   80       <- prof=2
 *                / \    \    \
 *              10  25   45   65          <- prof=3 (folhas)
 *
 * Verificacao manual de tres nos:
 *
 *  No 50 (raiz):
 *    - Profundidade: 0  (e a raiz, sem arestas ate ela mesma)
 *    - Altura: 3        (caminho mais longo: 50→30→20→10, 3 arestas)
 *    - Grau: 2          (filhos: 30 e 70)
 *    Calculado pela funcao: profundidade=0, altura=3, grau=2 ✓
 *
 *  No 30:
 *    - Profundidade: 1  (1 aresta de 50 ate 30)
 *    - Altura: 2        (caminho mais longo: 30→20→10, 2 arestas)
 *    - Grau: 2          (filhos: 20 e 40)
 *    Calculado pela funcao: profundidade=1, altura=2, grau=2 ✓
 *
 *  No 45 (folha):
 *    - Profundidade: 3  (50→30→40→45)
 *    - Altura: 0        (folha: nenhum filho)
 *    - Grau: 0          (sem filhos)
 *    Calculado pela funcao: profundidade=3, altura=0, grau=0 ✓
 *
 * =======================================================================
 */

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
    novo->dado = valor; novo->esq = NULL; novo->dir = NULL;
    return novo;
}

No *inserir(No *raiz, int valor) {
    if (raiz == NULL) return criarNo(valor);
    if (valor < raiz->dado) raiz->esq = inserir(raiz->esq, valor);
    else if (valor > raiz->dado) raiz->dir = inserir(raiz->dir, valor);
    return raiz;
}

int alturaNo(No *no) {
    if (no == NULL) return -1;
    int ae = alturaNo(no->esq), ad = alturaNo(no->dir);
    return ((ae > ad) ? ae : ad) + 1;
}

int alturaValor(No *raiz, int valor) {
    if (raiz == NULL) return -1;
    if (raiz->dado == valor) return alturaNo(raiz);
    if (valor < raiz->dado) return alturaValor(raiz->esq, valor);
    return alturaValor(raiz->dir, valor);
}

int profundidadeNo(No *raiz, int valor, int prof) {
    if (raiz == NULL) return -1;
    if (raiz->dado == valor) return prof;
    if (valor < raiz->dado) return profundidadeNo(raiz->esq, valor, prof + 1);
    return profundidadeNo(raiz->dir, valor, prof + 1);
}

int grauNo(No *no) {
    if (no == NULL) return 0;
    return (no->esq != NULL) + (no->dir != NULL);
}

int grauValor(No *raiz, int valor) {
    if (raiz == NULL) return -1;
    if (raiz->dado == valor) return grauNo(raiz);
    if (valor < raiz->dado) return grauValor(raiz->esq, valor);
    return grauValor(raiz->dir, valor);
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

    /* Verificacao dos tres nos descritos no cabecalho */
    int nos[] = {50, 30, 45};
    printf("=== Verificacao manual (tres nos) ===\n");
    for (int i = 0; i < 3; i++) {
        int v = nos[i];
        printf("No %d: profundidade=%d  altura=%d  grau=%d\n",
               v,
               profundidadeNo(raiz, v, 0),
               alturaValor(raiz, v),
               grauValor(raiz, v));
    }

    liberarArvore(raiz);
    return 0;
}
