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
    novo->dado = valor; novo->esq = NULL; novo->dir = NULL;
    return novo;
}

No *inserir(No *raiz, int valor) {
    if (raiz == NULL) return criarNo(valor);
    if (valor < raiz->dado) raiz->esq = inserir(raiz->esq, valor);
    else if (valor > raiz->dado) raiz->dir = inserir(raiz->dir, valor);
    return raiz;
}

/*
 * imprimirAncestral (implementacao recursiva)
 *
 * A funcao desce na arvore em direcao ao no com 'valor'.
 * Na volta da recursao (pos-chamada), imprime o no atual — assim os
 * ancestrais saem do pai imediato ate a raiz (ordem crescente de profundidade
 * vista de baixo para cima, conforme o enunciado: "do pai ate a raiz").
 *
 * Retorna 1 se o valor foi encontrado na subarvore, 0 caso contrario.
 */
int imprimirAncestral(No *raiz, int valor) {
    if (raiz == NULL) return 0;   /* valor nao existe nesta subarvore */
    if (raiz->dado == valor) return 1;   /* encontrado; nao imprime o proprio no */

    /* verifica as subarvores */
    int achou = 0;
    if (valor < raiz->dado)
        achou = imprimirAncestral(raiz->esq, valor);
    else
        achou = imprimirAncestral(raiz->dir, valor);

    /* se o valor esta abaixo deste no, entao este no e ancestral */
    if (achou) printf("%d ", raiz->dado);

    return achou;
}

/*
 * imprimirDescendentes: percurso em-ordem na subarvore de 'no',
 * excluindo o proprio no.
 * A funcao auxiliar faz o percurso e a principal localiza o no desejado.
 */
void percursoEmOrdem(No *no) {
    if (no == NULL) return;
    percursoEmOrdem(no->esq);
    printf("%d ", no->dado);
    percursoEmOrdem(no->dir);
}

void imprimirDescendentes(No *raiz, int valor) {
    if (raiz == NULL) {
        printf("No %d nao encontrado.\n", valor);
        return;
    }
    if (raiz->dado == valor) {
        /* Imprime todos os nos da subarvore, exceto o proprio no */
        percursoEmOrdem(raiz->esq);
        percursoEmOrdem(raiz->dir);
        return;
    }
    if (valor < raiz->dado)
        imprimirDescendentes(raiz->esq, valor);
    else
        imprimirDescendentes(raiz->dir, valor);
}

/*
 * contarDescendentes: conta quantos nos ha na subarvore de 'no',
 * excluindo o proprio no.
 */
int contarDescendentes(No *no) {
    if (no == NULL) return 0;
    /* conta filho esquerdo + filho direito e os descendentes deles */
    return contarDescendentes(no->esq) + contarDescendentes(no->dir)
           + (no->esq != NULL ? 1 : 0) + (no->dir != NULL ? 1 : 0);
}

/* Versao que localiza o no pelo valor antes de contar */
int contarDescendentesValor(No *raiz, int valor) {
    if (raiz == NULL) return -1;
    if (raiz->dado == valor) return contarDescendentes(raiz);
    if (valor < raiz->dado) return contarDescendentesValor(raiz->esq, valor);
    return contarDescendentesValor(raiz->dir, valor);
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

    printf("=== Ancestrais ===\n");
    int consulta[] = {50, 30, 10, 70};
    for (int i = 0; i < 4; i++) {
        int v = consulta[i];
        printf("Ancestrais de %d: ", v);
        int achou = imprimirAncestral(raiz, v);
        if (!achou) printf("(nao encontrado)");
        printf("\n");
    }

    printf("\n=== Descendentes ===\n");
    for (int i = 0; i < 4; i++) {
        int v = consulta[i];
        printf("Descendentes de %d: ", v);
        imprimirDescendentes(raiz, v);
        printf("(total: %d)\n", contarDescendentesValor(raiz, v));
    }

    liberarArvore(raiz);
    return 0;
}
