// RA: 2040482513004 - Guilherme Cordovil Quirino Gomes

#include <stdio.h>

/* Contador global de chamadas recursivas (reiniciado antes de cada busca) */
int chamadas = 0;

/*
 * Busca Binaria Recursiva em vetor ordenado.
 *
 * Caso base 1: inicio > fim  → elemento nao encontrado, retorna -1.
 * Caso base 2: vet[meio] == alvo → encontrado, retorna o indice.
 * Caso recursivo:
 *   - Se alvo > vet[meio], busca na metade direita.
 *   - Se alvo < vet[meio], busca na metade esquerda.
 */
int buscaBinaria(int *vet, int inicio, int fim, int alvo) {
    chamadas++;

    if (inicio > fim) return -1;   /* caso base: intervalo vazio */

    int meio = (inicio + fim) / 2;

    if (vet[meio] == alvo) {
        return meio;               /* caso base: encontrado */
    } else if (vet[meio] < alvo) {
        return buscaBinaria(vet, meio + 1, fim, alvo);    /* metade direita */
    } else {
        return buscaBinaria(vet, inicio, meio - 1, alvo); /* metade esquerda */
    }
}

int main(void) {
    int dados[] = {2, 5, 8, 12, 16, 23, 38, 45, 72, 91};
    int n = 10;
    int resultado;

    printf("Vetor: {2, 5, 8, 12, 16, 23, 38, 45, 72, 91}\n\n");

    /* Busca de elemento presente */
    chamadas = 0;
    resultado = buscaBinaria(dados, 0, n - 1, 23);
    printf("Busca por 23: indice %d  | Chamadas recursivas: %d\n", resultado, chamadas);

    /* Busca de elemento ausente */
    chamadas = 0;
    resultado = buscaBinaria(dados, 0, n - 1, 10);
    printf("Busca por 10: indice %d  | Chamadas recursivas: %d\n", resultado, chamadas);

    /* Busca do primeiro elemento */
    chamadas = 0;
    resultado = buscaBinaria(dados, 0, n - 1, 2);
    printf("Busca por  2: indice %d  | Chamadas recursivas: %d\n", resultado, chamadas);

    return 0;
}
