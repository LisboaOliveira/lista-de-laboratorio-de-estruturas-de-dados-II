#include<stdio.h>
#include<locale.h>

int main(){
    setlocale(LC_ALL, "portuguese");
    
    int parametro;
    
    printf("Digite o parâmetro\n");
    scanf("%i", &parametro );
    
    for(int i=1; i<=parametro; i++){
        for(int j=1; j<=parametro; j++){
            for(int k=1; k<=parametro; k++){
                if((i*i)+(j*j)==(k*k) && i<j){
                printf("Triplos Pitagóricos\ncateto1 = %i\ncateto2 = %i\nhipotenusa = %i\n", i, j, k);
                }
            }    
        }
    }
    return 0;
}