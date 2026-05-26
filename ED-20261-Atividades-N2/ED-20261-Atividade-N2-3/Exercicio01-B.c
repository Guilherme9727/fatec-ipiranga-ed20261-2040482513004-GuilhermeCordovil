// RA: 2040482513004 - Guilherme Cordovil Quirino Gomes

#include <stdio.h>

int main(void) {
    int v[] = {10, 20, 30, 40, 50};
    int tamanho = 5;
    int *ptr;

    /* --- a) Imprimir cada elemento e seu endereco --- */
    printf("=== a) Elementos e enderecos ===\n");
    for (ptr = v; ptr < v + tamanho; ptr++) {
        /* ptr aponta para cada posicao; * desreferencia, acessando o valor */
        printf("Valor: %d  |  Endereco: %p\n", *ptr, (void *)ptr);
    }

    /* --- b) Somar todos os elementos --- */
    printf("\n=== b) Soma dos elementos ===\n");
    int soma = 0;
    for (ptr = v; ptr < v + tamanho; ptr++) {
        soma += *ptr;   /* * acessa o inteiro armazenado no endereco apontado por ptr */
    }
    printf("Soma total: %d\n", soma);

    /* --- c) Inverter o vetor in-place com dois ponteiros --- */
    printf("\n=== c) Inversao do vetor ===\n");
    int *inicio = v;                    /* aponta para o primeiro elemento     */
    int *fim    = v + (tamanho - 1);    /* aponta para o ultimo elemento       */

    while (inicio < fim) {
        /* troca os valores sem variavel extra usando a funcao de soma */
        *inicio = *inicio + *fim;   /* * le e escreve no endereco de inicio    */
        *fim    = *inicio - *fim;   /* * le e escreve no endereco de fim       */
        *inicio = *inicio - *fim;   /* * finaliza a troca no endereco de inicio */
        inicio++;   /* avanca o ponteiro do comeco */
        fim--;      /* recua o ponteiro do fim     */
    }

    printf("Vetor apos inversao:\n");
    for (ptr = v; ptr < v + tamanho; ptr++) {
        printf("%d ", *ptr);   /* * desreferencia ptr para imprimir o valor */
    }
    printf("\n");

    return 0;
}
