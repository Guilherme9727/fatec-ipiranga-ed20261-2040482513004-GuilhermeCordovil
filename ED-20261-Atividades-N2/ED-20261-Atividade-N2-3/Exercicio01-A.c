// RA: 2040482513004 - Guilherme Cordovil Quirino Gomes

#include <stdio.h>

/*
 * Troca os valores apontados por 'a' e 'b' usando apenas aritmetica de inteiros.
 * Nao usa variavel temporaria e nem XOR.
 */
void trocar(int *a, int *b) {
    *a = *a + *b;   /* *a acumula a soma dos dois valores originais         */
    *b = *a - *b;   /* *b recebe (*a + *b) - *b, ou seja, o valor original de *a */
    *a = *a - *b;   /* *a recebe a soma menos o novo *b, ficando com o valor de *b */
}

int main(void) {
    int x = 10;
    int y = 20;

    /* & retorna o endereco de memoria de x e y */
    printf("Endereco de x: %p\n", (void *)&x);
    printf("Endereco de y: %p\n", (void *)&y);

    printf("\nAntes da troca: x = %d  |  y = %d\n", x, y);

    trocar(&x, &y);   /* & passa o endereco de x e y para a funcao */

    printf("Depois da troca: x = %d  |  y = %d\n", x, y);

    return 0;
}
