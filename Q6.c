//6. Escreva uma funcao recusiva para calcular o Maximo Divisor de dois numeros
//inteiros.

#include <stdio.h>

struct ParInteiro {
    int numero1;
    int numero2;
};

int mdc(struct ParInteiro numeros) {
    int a = numeros.numero1;
    int b = numeros.numero2;

    if (b == 0) {
        return a;
    } else {
        struct ParInteiro novoPar = {b, a % b};
        return mdc(novoPar);
    }
}

int main() {
    struct ParInteiro numeros;

    printf("Digite o primeiro numero inteiro: ");
    scanf("%d", &numeros.numero1);

    printf("Digite o segundo numero inteiro: ");
    scanf("%d", &numeros.numero2);

  
    int resultado = mdc(numeros);
    printf("O Maximo Divisor Comum (MDC) de %d e %d é: %d\n", numeros.numero1, numeros.numero2, resultado);

    return 0;
}