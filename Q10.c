//10. Implemente a funcao recursiva a seguir definida por A(m, n) definido recursivamente da seguinte
//forma:
//(a) n + 1, se m = 0;
//(b) A(m − 1, 1), se m > 0, n = 0;
//(c) A(m − 1, A(m, n − 1)), se m > 0 e n > 0.
//Crie uma funcao auxiliar que recebe dois inteiros a e b e apresenta todos os resultados para A(x, y)
//de forma que x < a e y < b.

#include <stdio.h>

int A(int m, int n) {
    if (m == 0) {
        return n + 1;
    } else if (m > 0 && n == 0) {
        return A(m - 1, 1);
    } else if (m > 0 && n > 0) {
        return A(m - 1, A(m, n - 1));
    } else {
        return -1; 
    }
}

void apresentarResultados(int a, int b) {
    for (int x = 0; x < a; x++) {
        for (int y = 0; y < b; y++) {
            printf("A(%d, %d) = %d\n", x, y, A(x, y));
        }
    }
}

int main() {
    int a, b;

    printf("Digite o valor de a: ");
    scanf("%d", &a);

    printf("Digite o valor de b: ");
    scanf("%d", &b);

    apresentarResultados(a, b);

    return 0;
}