// RA: 2040482513004 - Guilherme Cordovil Quirino Gomes

#include <stdio.h>

int chamadas_rapida  = 0;
int chamadas_ingenua = 0;

/*
 * Potenciacao Rapida (Fast Exponentiation) — O(log exp)
 *
 * Caso base:  exp == 0 → qualquer numero elevado a 0 e 1.
 * Caso recursivo par:    base^exp = (base^(exp/2))^2
 * Caso recursivo impar:  base^exp = base * base^(exp-1)
 *
 * Dividindo o expoente pela metade a cada chamada, o numero de
 * chamadas e proporcional a log2(exp), muito melhor que O(exp).
 */
long long potenciaRapida(long long base, int exp) {
    chamadas_rapida++;

    if (exp == 0) return 1;   /* caso base */

    if (exp % 2 == 0) {
        long long meio = potenciaRapida(base, exp / 2);   /* caso recursivo par */
        return meio * meio;
    } else {
        return base * potenciaRapida(base, exp - 1);      /* caso recursivo impar */
    }
}

/*
 * Potenciacao Ingenua — O(exp)
 *
 * Caso base:  exp == 0 → retorna 1.
 * Caso recursivo: base^exp = base * base^(exp-1)
 * Multiplica a base exp vezes, gerando exp+1 chamadas.
 */
long long potenciaIngenua(long long base, int exp) {
    chamadas_ingenua++;
    if (exp == 0) return 1;
    return base * potenciaIngenua(base, exp - 1);
}

static void testar(long long base, int exp) {
    chamadas_rapida  = 0;
    chamadas_ingenua = 0;

    long long res = potenciaRapida(base, exp);
    potenciaIngenua(base, exp);   /* apenas para contar as chamadas */

    printf("%lld^%d = %lld\n", base, exp, res);
    printf("  Chamadas rapida : %d  |  Chamadas ingenua: %d\n\n",
           chamadas_rapida, chamadas_ingenua);
}

int main(void) {
    printf("=== Comparacao: Potenciacao Rapida vs Ingenua ===\n\n");

    testar(2,  10);
    testar(3,   7);
    testar(5,   0);
    testar(7,  12);

    /*
     * Analise de complexidade:
     *
     * Potenciacao rapida  → O(log exp): divide o expoente pela metade a cada passo.
     * Potenciacao ingenua → O(exp):     subtrai 1 do expoente a cada passo.
     *
     * Exemplo: 2^10
     *   Rapida : ~5 chamadas (log2(10) ≈ 3,3, mais overhead de impares)
     *   Ingenua: 11 chamadas (10 + 1 para o caso base)
     *
     * Exemplo: 7^12
     *   Rapida : ~8 chamadas
     *   Ingenua: 13 chamadas
     *
     * Para expoentes grandes a diferenca cresce exponencialmente.
     */

    return 0;
}
