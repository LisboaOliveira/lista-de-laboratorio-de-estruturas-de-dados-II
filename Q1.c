#include<stdio.h>

int main(){
    int array;
    
    printf("Entre com valores entre 1 e 30\nPara sair digite 0\n");
    
    do{
        scanf("%i", &array);
        for(int i=0; i<array; i++){
            printf("*");
        }
        printf("\n");
    }while(array == 0);
    return 0;
}