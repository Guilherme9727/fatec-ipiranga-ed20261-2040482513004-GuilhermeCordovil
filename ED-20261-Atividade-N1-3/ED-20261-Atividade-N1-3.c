/*----------------------------------------------------------------------------------*/
/*FATEC-Ipiranga                                                                    */         
/*ADS - Estrutura de Dados                                                          */
/*Atividade: N1-3                                                             */
/*Objetivo: Simulador de Calculadora HP12c (Pilha RPN)                              */
/* */
/*Autor: Guilherme Cordovil                                                               */
/*Data: 03/04/2026                                                                  */
/*----------------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// 1. Definição da Estrutura da Pilha (Registradores clássicos) [cite: 12, 13]
typedef struct {
    float x; // Visor (Reflete o valor em X) [cite: 14]
    float y;
    float z;
    float t;
} HP12c;

// Inicializa os registradores com zero
void inicializar(HP12c *calc) {
    calc->x = 0;
    calc->y = 0;
    calc->z = 0;
    calc->t = 0;
}

// 2. Exibição Detalhada do estado da pilha [cite: 15, 23]
void exibir_status(HP12c *calc) {
    printf("\n--- Visualizacao da Pilha --- \n");
    printf("T: %.2f\n", calc->t);
    printf("Z: %.2f\n", calc->z);
    printf("Y: %.2f\n", calc->y);
    printf("X: %.2f (Display)\n", calc->x);
    printf("-----------------------------\n");
}

// 3. Função de Empilhar (Push) - Sobe os níveis da pilha [cite: 9]
void push(HP12c *calc, float valor) {
    calc->t = calc->z;
    calc->z = calc->y;
    calc->y = calc->x;
    calc->x = valor;
}

// 4. Processamento das 4 operações fundamentais [cite: 22]
void executar_operacao(HP12c *calc, char op) {
    float resultado = 0;

    switch (op) {
        case '+': resultado = calc->y + calc->x; break;
        case '-': resultado = calc->y - calc->x; break;
        case '*': resultado = calc->y * calc->x; break;
        case '/': 
            if (calc->x != 0) {
                resultado = calc->y / calc->x;
            } else {
                printf("\n[ERRO] Divisao por zero!\n");
                return;
            }
            break;
    }

    // Regra de descida da pilha após operação
    calc->x = resultado;
    calc->y = calc->z;
    calc->z = calc->t; 
    // O registrador T mantém seu valor original na lógica HP
}

int main() {
    HP12c hp;
    char entrada[200];
    char *item;

    inicializar(&hp);

    printf("FATEC Ipiranga - Simulador HP12c (RPN)\n");
    printf("Digite a expressao (ex: 5 1 2 + 4 * + 3 -): ");
    fgets(entrada, sizeof(entrada), stdin);

    // 5. Validação e Processamento da String [cite: 11, 21]
    item = strtok(entrada, " \n");

    while (item != NULL) {
        // Verifica se é número (aceita negativos)
        if (isdigit(item[0]) || (item[0] == '-' && isdigit(item[1]))) {
            push(&hp, atof(item));
        } 
        // Verifica se é operador válido
        else if (strlen(item) == 1 && strchr("+-*/", item[0])) {
            executar_operacao(&hp, item[0]);
        }

        exibir_status(&hp);
        item = strtok(NULL, " \n");
    }

    // Saída final conforme exigido [cite: 29, 30, 31]
    printf("\nO resultado da expressao algebrica e: %.2f\n", hp.x);

    return 0;
}
