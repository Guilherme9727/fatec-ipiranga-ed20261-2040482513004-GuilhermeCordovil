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

/* Imprime ancestrais recursivamente; retorna 1 se encontrou, 0 se nao */
int imprimirAncestral(No *raiz, int valor) {
    if (raiz == NULL) return 0;
    if (raiz->dado == valor) return 1;
    int achou = (valor < raiz->dado)
                ? imprimirAncestral(raiz->esq, valor)
                : imprimirAncestral(raiz->dir, valor);
    if (achou) printf("%d ", raiz->dado);
    return achou;
}

/* Percurso em-ordem na subarvore de 'no' */
void percursoEmOrdem(No *no) {
    if (no == NULL) return;
    percursoEmOrdem(no->esq);
    printf("%d ", no->dado);
    percursoEmOrdem(no->dir);
}

void imprimirDescendentes(No *raiz, int valor) {
    if (raiz == NULL) return;
    if (raiz->dado == valor) {
        percursoEmOrdem(raiz->esq);
        percursoEmOrdem(raiz->dir);
        return;
    }
    if (valor < raiz->dado) imprimirDescendentes(raiz->esq, valor);
    else imprimirDescendentes(raiz->dir, valor);
}

int contarDescendentes(No *no) {
    if (no == NULL) return 0;
    return (no->esq != NULL ? 1 : 0) + (no->dir != NULL ? 1 : 0)
           + contarDescendentes(no->esq) + contarDescendentes(no->dir);
}

int contarDescendentesValor(No *raiz, int valor) {
    if (raiz == NULL) return -1;
    if (raiz->dado == valor) return contarDescendentes(raiz);
    if (valor < raiz->dado) return contarDescendentesValor(raiz->esq, valor);
    return contarDescendentesValor(raiz->dir, valor);
}

/* Verifica se o valor existe na arvore */
int existe(No *raiz, int valor) {
    if (raiz == NULL) return 0;
    if (raiz->dado == valor) return 1;
    if (valor < raiz->dado) return existe(raiz->esq, valor);
    return existe(raiz->dir, valor);
}

/*
 * relatorioNo: imprime um relatorio estrutural completo do no com 'valor'.
 */
void relatorioNo(No *raiz, int valor) {
    if (!existe(raiz, valor)) {
        printf("+----------------------------------+\n");
        printf("| ERRO: no %d nao encontrado.      |\n", valor);
        printf("+----------------------------------+\n");
        return;
    }

    int prof  = profundidadeNo(raiz, valor, 0);
    int alt   = alturaValor(raiz, valor);
    int grau  = grauValor(raiz, valor);
    int qtdD  = contarDescendentesValor(raiz, valor);

    printf("+----------------------------------+\n");
    printf("| RELATORIO DO NO: %-14d |\n", valor);
    printf("+----------------------------------+\n");
    printf("| Profundidade : %-17d |\n", prof);
    printf("| Altura       : %-17d |\n", alt);
    printf("| Grau         : %-17d |\n", grau);

    printf("| Ancestrais   : ");
    int achou = imprimirAncestral(raiz, valor);
    if (!achou || prof == 0) printf("(nenhum)         ");
    printf("|\n");

    printf("| Descendentes : ");
    if (qtdD == 0) {
        printf("(nenhum)         ");
    } else {
        imprimirDescendentes(raiz, valor);
    }
    printf("|\n");

    printf("| Qtd Descend. : %-17d |\n", qtdD);
    printf("+----------------------------------+\n\n");
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

    relatorioNo(raiz, 30);

    liberarArvore(raiz);
    return 0;
}
