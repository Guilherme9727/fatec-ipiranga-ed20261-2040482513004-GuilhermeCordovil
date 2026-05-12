/*----------------------------------------------------------------------------------*/
/*FATEC-Ipiranga                                                                     */
/*ADS - Estrutura de Dados                                                           */
/*Prof - Veríssimo                                                                   */
/*                                                                                   */
/*Id da Atividade: N2-2                                                              */
/*Objetivo: Calculando Fator de Balanceamento (AVL)                                  */
/*                                                                                   */
/*Autor: Guilherme Cordovil                                                          */
/*Data: 11/05/2026                                                                   */
/*----------------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>

struct No {
    int valor;
    int altura;
    struct No *esq;
    struct No *dir;
};

// se o no for NULL retorna -1, senao calcula a altura recursivamente
int calcularAltura(struct No *n) {
    if (n == NULL)
        return -1;

    int h_esq = calcularAltura(n->esq);
    int h_dir = calcularAltura(n->dir);

    // pega o maior dos dois lados e soma 1
    if (h_esq > h_dir)
        n->altura = 1 + h_esq;
    else
        n->altura = 1 + h_dir;

    return n->altura;
}

// FB = altura do filho esq - altura do filho dir
int obterFB(struct No *n) {
    if (n == NULL)
        return 0;

    return calcularAltura(n->esq) - calcularAltura(n->dir);
}

struct No *criarNo(int val) {
    struct No *novo = (struct No*) malloc(sizeof(struct No));
    novo->valor  = val;
    novo->altura = 0;
    novo->esq    = NULL;
    novo->dir    = NULL;
    return novo;
}

int main() {

    // montando a arvore manualmente: 20 -> 10 -> 5 -> 2
    struct No *raiz = criarNo(20);
    raiz->esq       = criarNo(10);
    raiz->esq->esq  = criarNo(5);
    raiz->esq->esq->esq = criarNo(2);

    // calcula a altura de toda a arvore a partir da raiz
    calcularAltura(raiz);

    printf("Altura do no 2  : %d\n", raiz->esq->esq->esq->altura);
    printf("Altura do no 5  : %d\n", raiz->esq->esq->altura);
    printf("Altura do no 10 : %d\n", raiz->esq->altura);
    printf("Altura do no 20 : %d\n", raiz->altura);

    int fb = obterFB(raiz);
    printf("\nFator de Balanceamento da raiz (no 20): %d\n", fb);

    if (fb > 1 || fb < -1)
        printf("Arvore DESBALANCEADA!\n");
    else
        printf("Arvore balanceada.\n");

    // libera memoria
    free(raiz->esq->esq->esq);
    free(raiz->esq->esq);
    free(raiz->esq);
    free(raiz);

    return 0;
}
