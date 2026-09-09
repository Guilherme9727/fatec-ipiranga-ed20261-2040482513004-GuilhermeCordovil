/*---------------------------------------------------------------*/
/*FATEC-Ipiranga                                                 */
/*ADS - Estrutura de Dados                                       */
/*Id da Atividade: N1-4                                          */
/*Objetivo: Editor de texto                                      */
/*                                                               */
/*Autor: Sabrina Bernardi, Carolina Gusmão, Guilherme Cordovil   */
/*Data: 12/04/2026                                               */
/*                                                               */
/*---------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TEXTO 1000

char texto[MAX_TEXTO] = "";

//Estrutura do Nó da Pilha Dinâmica
typedef struct No {
    char estado[MAX_TEXTO];
    struct No* proximo;
} No;

//Topos das pilhas inicados vazios(NULL)
No* topo_historico = NULL;
No* topo_refazer   = NULL;

//Push - aloca um novo nó e empilha o conteúdo
void push(No** topo, const char* conteudo) {
    No* novo_no = (No*)malloc(sizeof(No));
    if (novo_no == NULL) {
        printf("Erro: Sem memoria RAM disponivel!\n");
        return;
    }
    strcpy(novo_no->estado, conteudo);
    novo_no->proximo = *topo;
    *topo = novo_no;
}

//Pop - desempilha e libera a memória do nó removido
void pop(No** topo, char* destino) {
    if (*topo == NULL) return;

    No* no_remover = *topo;

    if (destino != NULL) {
        strcpy(destino, no_remover->estado);
    }

    *topo = no_remover->proximo;
    free(no_remover);
}

//Esvazia uma pilha inteira, liberando toda a memória
void limpar_pilha(No** topo) {
    while (*topo != NULL) {
        pop(topo, NULL);
    }
}

/* ==========================================
    LÓGICA DO EDITOR USANDO AS PILHAS DINÂMICAS
   ========================================== */

void salvar_estado() {
    push(&topo_historico, texto);
}

void inserir_texto(char* novo_texto) {
    if (strlen(novo_texto) == 0) {
        printf("\n[Aviso] Nenhum texto digitado. Operacao ignorada.\n");
        return;
    }

    if (strlen(texto) + strlen(novo_texto) >= MAX_TEXTO) {
        printf("\n[Aviso] Texto muito longo! Limite de %d caracteres atingido.\n", MAX_TEXTO - 1);
        return;
    }

    salvar_estado();
    strcat(texto, novo_texto);
    limpar_pilha(&topo_refazer);
}

void apagar_digito() {
    int tamanho = strlen(texto);
    if (tamanho > 0) {
        salvar_estado();
        texto[tamanho - 1] = '\0';
        limpar_pilha(&topo_refazer);
    } else {
        printf("\n[Aviso] O texto ja esta vazio!\n");
    }
}

void desfazer() {
    if (topo_historico != NULL) {
        push(&topo_refazer, texto);
        pop(&topo_historico, texto);
        printf("\n[Acao] Desfazer realizado com sucesso.\n");
    } else {
        printf("\n[Aviso] Nada para desfazer!\n");
    }
}

void refazer() {
    if (topo_refazer != NULL) {
        push(&topo_historico, texto);
        pop(&topo_refazer, texto);
        printf("\n[Acao] Refazer realizado com sucesso.\n");
    } else {
        printf("\n[Aviso] Nada para refazer!\n");
    }
}

int main() {
    int opcao;
    char entrada[MAX_TEXTO];

    while (1) {
        printf("\n===================================\n");
        printf("TEXTO ATUAL: \"%s\"\n", texto);
        printf("===================================\n");
        printf("1. Digitar texto\n");
        printf("2. Apagar ultimo digito\n");
        printf("3. Desfazer (Undo CTRL+Z)\n");
        printf("4. Refazer (Redo CTRL+Y)\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        getchar(); // Limpa o Enter do buffer

        switch (opcao) {
            case 1:
                printf("Digite o que deseja inserir: ");
                fgets(entrada, MAX_TEXTO, stdin);
                entrada[strcspn(entrada, "\n")] = 0;
                inserir_texto(entrada);
                break;

            case 2:
                apagar_digito();
                break;

            case 3:
                desfazer();
                break;

            case 4:
                refazer();
                break;

            case 0:
                printf("Limpando a memoria...\n");
                limpar_pilha(&topo_historico);
                limpar_pilha(&topo_refazer);
                printf("Encerrando o editor. Ate mais!\n");
                return 0;
                
            default:
                printf("Opcao invalida! Tente novamente.\n");
        }
    }
    return 0;
}
