#include<stdio.h>

float funcao(float x1, float x2);

int main(){
    float Y, x1, x2;
    printf("Informe os valores de x1 e x2\n");
    scanf("%f%f", &x1, &x2);
    Y = funcao(x1, x2);
    printf("%.1f\n", Y);
    return 0;
}

float funcao(float x1, float x2){
    if(x1==0||x2==0){
        return 0;
    }
    if(x2==1){
        return x1;
    }
    return x1 + funcao(x1, x2-1);
}