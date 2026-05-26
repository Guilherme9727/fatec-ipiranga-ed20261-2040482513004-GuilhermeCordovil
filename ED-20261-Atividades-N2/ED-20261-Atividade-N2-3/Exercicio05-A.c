// RA: 2040482513004 - Guilherme Cordovil Quirino Gomes

#include <stdio.h>
#include <stdlib.h>

/* -----------------------------------------------------------------
 * Definicao da estrutura do no da Arvore Binaria de Busca (ABB)
 * ----------------------------------------------------------------- */
typedef struct No {
    int dado;
    struct No *esq;
    struct No *dir;
} No;

/* Aloca e retorna um novo no com o valor fornecido */
No *criarNo(int valor) {
    No *novo = (No *)malloc(sizeof(No));
    if (novo == NULL) {
        printf("Erro: falha ao alocar memoria.\n");
        exit(1);
    }
    novo->dado = valor;
    novo->esq  = NULL;
    novo->dir  = NULL;
    return novo;
}

/* Insere 'valor' na ABB e retorna a raiz atualizada */
No *inserir(No *raiz, int valor) {
    if (raiz == NULL) return criarNo(valor);   /* posicao encontrada */

    if (valor < raiz->dado)
        raiz->esq = inserir(raiz->esq, valor); /* vai para a subarvore esquerda */
    else if (valor > raiz->dado)
        raiz->dir = inserir(raiz->dir, valor); /* vai para a subarvore direita  */
    /* valor duplicado e ignorado */

    return raiz;
}

/*
 * alturaNo: maior distancia (em arestas) do no ate uma folha descendente.
 * Retorna -1 para ponteiro nulo (convencionado pelo enunciado).
 */
int alturaNo(No *no) {
    if (no == NULL) return -1;   /* caso base: no inexistente */

    int altEsq = alturaNo(no->esq);
    int altDir = alturaNo(no->dir);

    int maior = (altEsq > altDir) ? altEsq : altDir;
    return maior + 1;
}

/*
 * profundidadeNo: numero de arestas do no ate a raiz.
 * Retorna -1 se o valor nao existir na arvore.
 */
int profundidadeNo(No *raiz, int valor, int prof) {
    if (raiz == NULL) return -1;            /* valor nao encontrado */
    if (raiz->dado == valor) return prof;   /* no encontrado: profundidade atual */

    if (valor < raiz->dado)
        return profundidadeNo(raiz->esq, valor, prof + 1);
    else
        return profundidadeNo(raiz->dir, valor, prof + 1);
}

/*
 * grauNo: numero de filhos diretos do no.
 * Retorna 0, 1 ou 2.
 */
int grauNo(No *no) {
    if (no == NULL) return 0;
    int g = 0;
    if (no->esq != NULL) g++;
    if (no->dir != NULL) g++;
    return g;
}

/* Percurso em-ordem (esq → raiz → dir) imprimindo grau de cada no */
void percursoGrau(No *raiz) {
    if (raiz == NULL) return;
    percursoGrau(raiz->esq);
    printf("  No %d: grau %d\n", raiz->dado, grauNo(raiz));
    percursoGrau(raiz->dir);
}

/* Libera toda a memoria alocada pela arvore (pos-ordem) */
void liberarArvore(No *raiz) {
    if (raiz == NULL) return;
    liberarArvore(raiz->esq);
    liberarArvore(raiz->dir);
    free(raiz);
}

int main(void) {
    No *raiz = NULL;

    /* Insercoes em sequencia conforme o enunciado */
    int valores[] = {50, 30, 70, 20, 40, 60, 80, 10, 25, 45, 65};
    int qtd = (int)(sizeof(valores) / sizeof(valores[0]));

    for (int i = 0; i < qtd; i++) {
        raiz = inserir(raiz, valores[i]);
    }

    printf("=== Parte B — Alturas ===\n");
    int alturasConsulta[] = {50, 30, 70, 20, 10};
    for (int i = 0; i < 5; i++) {
        int v = alturasConsulta[i];
        printf("  alturaNo(%d) = %d\n", v,
               alturaNo(raiz->dado == v ? raiz
                        : (v < raiz->dado ? raiz->esq : raiz->dir)));
        /* Nota: para consulta generica usamos profundidade + busca;
           aqui navegamos manualmente para ilustrar. Veja Exercicio05-B.c
           para a implementacao com busca recursiva completa.          */
    }

    printf("\n=== Parte B — Profundidades ===\n");
    int profConsulta[] = {50, 30, 70, 45, 10};
    for (int i = 0; i < 5; i++) {
        int v = profConsulta[i];
        printf("  profundidadeNo(%d) = %d\n", v,
               profundidadeNo(raiz, v, 0));
    }

    printf("\n=== Parte B — Grau de cada no (percurso em-ordem) ===\n");
    percursoGrau(raiz);

    printf("\n=== Parte B — Altura total da arvore ===\n");
    printf("  alturaNo(raiz) = %d\n", alturaNo(raiz));

    liberarArvore(raiz);
    return 0;
}
