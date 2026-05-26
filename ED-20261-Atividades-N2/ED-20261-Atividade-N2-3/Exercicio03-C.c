// RA: 2040482513004 - Guilherme Cordovil Quirino Gomes

#include <stdio.h>

/*
 * Versao com rastreamento de profundidade da recursao.
 * O parametro 'nivel' indica a profundidade atual na pilha de chamadas.
 * A saida e indentada com (nivel * 2) espacos para visualizar a hierarquia.
 *
 * Caso base:  n == 1 → move diretamente, imprimindo o nivel.
 * Caso recursivo: identico ao Exercicio03-A.c, acrescentando nivel + 1.
 */
void hanoi(int n, char origem, char destino, char auxiliar, int nivel) {
    /* imprime indentacao proporcional ao nivel de profundidade */
    for (int i = 0; i < nivel * 2; i++) {
        printf(" ");
    }

    if (n == 1) {
        printf("[Nivel %d] Mover disco 1 de %c para %c\n", nivel, origem, destino);
        return;
    }

    printf("[Nivel %d] Chamada: mover %d discos de %c para %c (aux: %c)\n",
           nivel, n, origem, destino, auxiliar);

    hanoi(n - 1, origem, auxiliar, destino, nivel + 1);

    for (int i = 0; i < nivel * 2; i++) printf(" ");
    printf("[Nivel %d] Mover disco %d de %c para %c\n", nivel, n, origem, destino);

    hanoi(n - 1, auxiliar, destino, origem, nivel + 1);
}

int main(void) {
    printf("=== Torres de Hanoi com n = 1 (com rastreamento) ===\n");
    hanoi(1, 'A', 'C', 'B', 0);

    printf("\n=== Torres de Hanoi com n = 3 (com rastreamento) ===\n");
    hanoi(3, 'A', 'C', 'B', 0);

    printf("\n=== Torres de Hanoi com n = 4 (com rastreamento) ===\n");
    hanoi(4, 'A', 'C', 'B', 0);

    return 0;
}
