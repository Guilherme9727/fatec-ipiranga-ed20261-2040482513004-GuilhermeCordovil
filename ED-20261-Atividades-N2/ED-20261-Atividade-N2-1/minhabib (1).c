/*----------------------------------------------------------------------------------*/
/*FATEC-Ipiranga                                                                    */
/*ADS - Estrutura de Dados                                                          */
/*Prof - Veríssimo                                                                  */
/*                                                                                  */
/*Id da Atividade: N2-1                                                             */
/*Objetivo: Explorando a Anatomia da Arvore Binaria                                 */
/*                                                                                  */
/*Autor: Guilherme Cordovil                                                         */
/*Data: 03/05/2026                                                                  */
/*----------------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include "minhabib.h"

/* ======================================================
 * FUNCOES AUXILIARES INTERNAS
 * ====================================================== */

/* Busca e retorna o ponteiro para o no com o valor informado */
static No* buscar_no(No* raiz, int valor) {
    if (raiz == NULL)
        return NULL;
    if (raiz->valor == valor)
        return raiz;
    if (valor < raiz->valor)
        return buscar_no(raiz->esq, valor);
    return buscar_no(raiz->dir, valor);
}

/* Conta quantos filhos diretos um no possui (grau do no) */
static int contar_filhos(No* no) {
    int qtd = 0;
    if (no->esq != NULL) qtd++;
    if (no->dir != NULL) qtd++;
    return qtd;
}

/* Imprime os nos de um nivel especifico (helper para imprimir_niveis) */
static void imprimir_nivel_k(No* raiz, int nivel_atual, int alvo) {
    if (raiz == NULL) return;
    if (nivel_atual == alvo) {
        printf("%d  ", raiz->valor);
        return;
    }
    imprimir_nivel_k(raiz->esq, nivel_atual + 1, alvo);
    imprimir_nivel_k(raiz->dir, nivel_atual + 1, alvo);
}

/* Exibe a subarvore no formato de arvore com indentacao */
static void exibir_subarvore(No* no, int profundidade) {
    if (no == NULL) return;

    // imprime o lado direito primeiro para parecer uma arvore deitada
    exibir_subarvore(no->dir, profundidade + 1);

    for (int i = 0; i < profundidade; i++)
        printf("        ");
    printf("[%d]\n", no->valor);

    exibir_subarvore(no->esq, profundidade + 1);
}


/* ======================================================
 * FUNCOES PUBLICAS DA BIBLIOTECA
 * ====================================================== */

void imprimir_nos_internos(No* raiz) {
    if (raiz == NULL) return;

    // no interno = possui pelo menos um filho
    if (raiz->esq != NULL || raiz->dir != NULL) {
        printf("%d  ", raiz->valor);
    }
    imprimir_nos_internos(raiz->esq);
    imprimir_nos_internos(raiz->dir);
}

void imprimir_folhas(No* raiz) {
    if (raiz == NULL) return;

    if (raiz->esq == NULL && raiz->dir == NULL) {
        printf("%d  ", raiz->valor);
        return;
    }
    imprimir_folhas(raiz->esq);
    imprimir_folhas(raiz->dir);
}

void imprimir_niveis(No* raiz, int nivel_atual) {
    int altura = calcular_altura(raiz);
    for (int i = 0; i <= altura; i++) {
        printf("  Nivel %d: [ ", i);
        imprimir_nivel_k(raiz, 0, i);
        printf("]\n");
    }
}

int calcular_altura(No* no) {
    if (no == NULL) return -1;

    int h_esq = calcular_altura(no->esq);
    int h_dir = calcular_altura(no->dir);

    if (h_esq > h_dir)
        return h_esq + 1;
    return h_dir + 1;
}

int calcular_profundidade(No* raiz, int valor, int profundidade_atual) {
    if (raiz == NULL) return -1;
    if (raiz->valor == valor) return profundidade_atual;

    if (valor < raiz->valor)
        return calcular_profundidade(raiz->esq, valor, profundidade_atual + 1);
    return calcular_profundidade(raiz->dir, valor, profundidade_atual + 1);
}

/* Imprime o caminho da raiz ate o pai do no buscado (ordem ancestral) */
void imprimir_ancestrais(No* raiz, int valor) {
    if (raiz == NULL || raiz->valor == valor)
        return;

    printf("%d  ", raiz->valor);

    if (valor < raiz->valor)
        imprimir_ancestrais(raiz->esq, valor);
    else
        imprimir_ancestrais(raiz->dir, valor);
}

/* Percorre em pre-ordem e imprime todos os descendentes do no */
void imprimir_descendentes(No* no) {
    if (no == NULL) return;
    if (no->esq != NULL) {
        printf("%d  ", no->esq->valor);
        imprimir_descendentes(no->esq);
    }
    if (no->dir != NULL) {
        printf("%d  ", no->dir->valor);
        imprimir_descendentes(no->dir);
    }
}


/* ======================================================
 * FUNCAO PRINCIPAL DE DIAGNOSTICO
 * ====================================================== */

void analisar_arvore(No* raiz, int valorBusca) {

    printf("========================================\n");
    printf("   DIAGNOSTICO GERAL DA ARVORE\n");
    printf("========================================\n\n");

    printf("Raiz da arvore: %d  (end.: %p)\n\n", raiz->valor, (void*)raiz);

    printf("Nos Internos:\n  ");
    imprimir_nos_internos(raiz);
    printf("\n\n");

    printf("Nos Folha (externos):\n  ");
    imprimir_folhas(raiz);
    printf("\n\n");

    printf("Exibicao por Niveis:\n");
    imprimir_niveis(raiz, 0);
    printf("\n");

    /* --------------------------------------------------
     * DIAGNOSTICO ESPECIFICO
     * -------------------------------------------------- */
    printf("========================================\n");
    printf("   DIAGNOSTICO ESPECIFICO  (busca: %d)\n", valorBusca);
    printf("========================================\n\n");

    No* alvo = buscar_no(raiz, valorBusca);

    if (alvo == NULL) {
        printf("ERRO: o valor %d nao foi encontrado na arvore.\n", valorBusca);
        return;
    }

    printf("No encontrado: %d\n", alvo->valor);
    printf("Endereco de memoria: %p\n\n", (void*)alvo);

    int grau = contar_filhos(alvo);
    printf("Grau do no: %d filho(s)", grau);
    if (grau == 0)
        printf("  -> no folha");
    else if (grau == 1)
        printf("  -> no com um filho");
    else
        printf("  -> no completo");
    printf("\n\n");

    printf("Ancestrais (do no ate a raiz):\n  ");
    imprimir_ancestrais(raiz, valorBusca);
    printf("\n\n");

    printf("Descendentes:\n  ");
    if (alvo->esq == NULL && alvo->dir == NULL)
        printf("(nenhum - eh folha)");
    else
        imprimir_descendentes(alvo);
    printf("\n\n");

    int altura = calcular_altura(alvo);
    printf("Altura do no %d: %d\n", alvo->valor, altura);

    int prof = calcular_profundidade(raiz, valorBusca, 0);
    printf("Profundidade do no %d: %d\n\n", alvo->valor, prof);

    /* --------------------------------------------------
     * EXTRACAO DE SUB-ARVORE
     * -------------------------------------------------- */
    printf("========================================\n");
    printf("   SUB-ARVORE COM RAIZ EM %d\n", alvo->valor);
    printf("========================================\n\n");
    exibir_subarvore(alvo, 0);
    printf("\n");
}
