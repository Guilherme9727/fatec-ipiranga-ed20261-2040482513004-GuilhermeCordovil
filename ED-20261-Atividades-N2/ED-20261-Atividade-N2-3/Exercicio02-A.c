// RA: 2040482513004 - Guilherme Cordovil Quirino Gomes

#include <stdio.h>

/* Calcula e retorna a media aritmetica do vetor */
float calcularMedia(float *vet, int n) {
    float soma = 0.0f;
    float *ptr = vet;
    for (int i = 0; i < n; i++) {
        soma += *ptr;   /* * acessa o float no endereco apontado por ptr */
        ptr++;          /* avanca ptr para o proximo elemento            */
    }
    return soma / n;
}

/* Encontra o maior e o menor valor; escreve diretamente nos enderecos recebidos */
void encontrarExtremos(float *vet, int n, float *maior, float *menor) {
    float *ptr = vet;
    *maior = *ptr;   /* inicializa maior com o primeiro elemento via desreferenciacao */
    *menor = *ptr;   /* inicializa menor com o primeiro elemento via desreferenciacao */
    ptr++;

    for (int i = 1; i < n; i++) {
        if (*ptr > *maior) *maior = *ptr;   /* * atualiza o valor no endereco de maior */
        if (*ptr < *menor) *menor = *ptr;   /* * atualiza o valor no endereco de menor */
        ptr++;
    }
}

/* Normaliza o vetor: cada elemento e dividido pelo valor maximo */
void normalizar(float *vet, int n) {
    float maior, menor;
    /* & passa os enderecos de maior e menor para que a funcao escreva neles */
    encontrarExtremos(vet, n, &maior, &menor);

    float *ptr = vet;
    for (int i = 0; i < n; i++) {
        *ptr = *ptr / maior;   /* * le e sobrescreve o valor diretamente na memoria */
        ptr++;
    }
    /*
     * A funcao altera o vetor original porque recebe um ponteiro (float *vet),
     * ou seja, o endereco real do primeiro elemento na memoria. Ao escrever via
     * *ptr, estamos modificando a posicao fisica na RAM, nao uma copia local.
     * Se o parametro fosse por valor (float vet[]), uma copia seria feita e o
     * original nao seria alterado — mas arrays em C sempre decaem para ponteiro.
     */
}

/* Imprime o vetor formatado com titulo */
void imprimirVetor(float *vet, int n, const char *titulo) {
    printf("%s: [ ", titulo);
    float *ptr = vet;
    for (int i = 0; i < n; i++) {
        printf("%.4f", *ptr);          /* * acessa o float no endereco de ptr */
        if (i < n - 1) printf(", ");
        ptr++;
    }
    printf(" ]\n");
}

int main(void) {
    float notas[] = {7.5f, 3.2f, 9.8f, 6.0f, 5.5f, 8.1f};
    int n = 6;

    imprimirVetor(notas, n, "Antes de normalizar");

    float media = calcularMedia(notas, n);
    printf("Media: %.4f\n", media);

    float maior, menor;
    /* & passa os enderecos de maior e menor para a funcao escrever neles */
    encontrarExtremos(notas, n, &maior, &menor);
    printf("Maior: %.4f  |  Menor: %.4f\n", maior, menor);

    normalizar(notas, n);

    imprimirVetor(notas, n, "Depois de normalizar");

    return 0;
}
