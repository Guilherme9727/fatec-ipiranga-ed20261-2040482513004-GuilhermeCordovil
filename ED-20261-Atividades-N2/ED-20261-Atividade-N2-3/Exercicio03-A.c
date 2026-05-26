// RA: 2040482513004 - Guilherme Cordovil Quirino Gomes

#include <stdio.h>

/*
 * Resolve o problema das Torres de Hanoi de forma puramente recursiva.
 * Transfere n discos da haste 'origem' para 'destino' usando 'auxiliar'.
 *
 * Caso base:  n == 1 → move o unico disco diretamente.
 * Caso recursivo:
 *   1. Move os n-1 discos superiores de origem para auxiliar.
 *   2. Move o disco n (o maior) de origem para destino.
 *   3. Move os n-1 discos de auxiliar para destino.
 */
void hanoi(int n, char origem, char destino, char auxiliar) {
    if (n == 1) {
        printf("Mover disco 1 de %c para %c\n", origem, destino);
        return;
    }
    hanoi(n - 1, origem, auxiliar, destino);
    printf("Mover disco %d de %c para %c\n", n, origem, destino);
    hanoi(n - 1, auxiliar, destino, origem);
}

int main(void) {
    printf("=== Torres de Hanoi com n = 1 ===\n");
    hanoi(1, 'A', 'C', 'B');

    printf("\n=== Torres de Hanoi com n = 3 ===\n");
    hanoi(3, 'A', 'C', 'B');

    printf("\n=== Torres de Hanoi com n = 4 ===\n");
    hanoi(4, 'A', 'C', 'B');

    return 0;
}
