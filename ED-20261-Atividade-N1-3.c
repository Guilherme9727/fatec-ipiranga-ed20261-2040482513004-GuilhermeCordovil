/*----------------------------------------------------------------------------------*/
/*FATEC-Ipiranga                                                                    */         
/*ADS - Estrutura de Dados                                                          */
/*Atividade: N1-3                                                             */
/*Objetivo: Simulador de Calculadora HP12c (Pilha RPN)                              */
/* */
/*Autor: Guilherme Cordovil                                                                 */
/*Data: 03/04/2026                                                                  */
/*----------------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Registradores de memória da HP12c (Pilha de 4 níveis) [cite: 12, 13]
float X = 0, Y = 0, Z = 0, T = 0;

// Exibe o estado de todos os registradores a cada passo [cite: 15, 23]
void exibirPilha() {
    printf("\n--- Visualizacao da Pilha --- \n");
    printf("T: %.2f\n", T);
    printf("Z: %.2f\n", Z);
    printf("Y: %.2f\n", Y);
    printf("X: %.2f (Display)\n", X); // O display reflete o valor contido em X [cite: 14]
    printf("-----------------------------\n");
}

// Insere novo operando e sobe os valores na pilha
void push(float valor) {
    T = Z;
    Z = Y;
    Y = X;
    X = valor;
}

// Executa as 4 operações aritméticas fundamentais [cite: 22]
void calcular(char op) {
    float resultado = 0;

    switch (op) {
        case '+': resultado = Y + X; break;
        case '-': resultado = Y - X; break;
        case '*': resultado = Y * X; break;
        case '/': 
            if (X != 0) {
                resultado = Y / X;
            } else {
                printf("Erro: Divisao por zero!\n");
                return;
            }
            break;
    }

    // Após a operação, os níveis descem preenchendo X
    X = resultado;
    Y = Z;
    Z = T;
}

int main() {
    char expressao[150];
    char *token;

    printf("Simulador HP12c - Notacao Polonesa Reversa\n");
    printf("Digite a expressao RPN (ex: 5 1 2 + 4 * + 3 -): ");
    fgets(expressao, sizeof(expressao), stdin);

    // Processa a string baseando-se nos espaços [cite: 11]
    token = strtok(expressao, " \n");

    while (token != NULL) {
        // Valida se o token é um operando (número) [cite: 21]
        if (isdigit(token[0]) || (token[0] == '-' && isdigit(token[1]))) {
            push(atof(token));
        } 
        // Valida se o token é um operador [cite: 21]
        else if (strlen(token) == 1 && strchr("+-*/", token[0])) {
            calcular(token[0]);
        }

        exibirPilha();
        token = strtok(NULL, " \n");
    }

    // Mensagem final conforme especificação [cite: 29, 30]
    printf("\nO resultado da expressao algebrica e: %.2f\n", X);

    return 0;
}