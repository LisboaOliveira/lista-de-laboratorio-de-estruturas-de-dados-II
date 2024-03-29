#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<locale.h>
#include<math.h>
#include<stdbool.h>

#define tamanho 149
#define aurea 0.618033

typedef struct Contatos{
 char nome[25];
 int tel;
 char email[40];
 bool livre;
}contato;

void iniciarTabela (contato tabelahash[]){
    for(int i=0; i < tamanho; i++){
        tabelahash[i].livre = true;
    }
}

int acharchave(int chave){
    return (int)(tamanho * fmod(chave * aurea, 1));
}

void espalhamento(contato tabelahash[], contato novo){
    int posicao = acharchave (novo.tel);
    while(tabelahash[posicao].livre != true){
        posicao = acharchave(posicao+1);
    }
    tabelahash[posicao] = novo;
}

contato *busca (contato tabelahash[], int chave){
    int posicao = acharchave(chave);
    while(tabelahash [posicao].livre == false){
        if(tabelahash[posicao].tel==chave){
            return &tabelahash[posicao];
        }else{
            posicao = acharchave(posicao + 1);
        }
    }
    return NULL;
}

void mostraTabela(contato tabelahash[]){
    for(int i=0; i < tamanho; i++){
        if(tabelahash[i].livre == false){
            printf("Posicao %d:\n%s\n%d\n%s\n", i, tabelahash[i].nome, tabelahash[i].tel, tabelahash[i].email);
        }else{
            printf("Posicao %d: Vazio\n", i);
        }
    }
}

void remover(contato tabelahash[], int chave){
    int posicao = acharchave(chave);
    while(tabelahash[posicao].livre == false){
        if(tabelahash[posicao].tel == chave){
            tabelahash[posicao].livre = true;
            printf("Contato removido.\n");
            return;
        }
        posicao = acharchave(posicao+1);
    }
    printf("Contato não encontrado.\n");
}

int main(){
    setlocale (LC_ALL, "Portuguese");

    contato tabelahash[tamanho], novoContato;
    int opcao, chave;
    char nomeDoArquivo[30];
    FILE *arquivo;

    iniciarTabela(tabelahash);

    do{
        printf("Iforme o nome do arquivo de contatos:\n");
        fgets(nomeDoArquivo, sizeof(nomeDoArquivo), stdin);
        nomeDoArquivo[strcspn(nomeDoArquivo, "\n")] = '\0';

        arquivo = fopen(nomeDoArquivo, "r");
    
        if(arquivo == NULL){
            printf("Erro ao abrir o arquivo.\nDeseja tentar novamente? (responda sim ou não)\n");
            char resposta;//declara aqui para q seja criada apenas se necessario
            scanf(" %c", &resposta);
            getchar();
            if(resposta != 's' && resposta != 'S'){
                return 1;//encerra o programa se a resposnta for não
            }
         }
    }while (arquivo == NULL);//continua pedindo o nome do arquivo ate que seja aberto com sucesso 

    while(fscanf(arquivo, "%s %i %s ", novoContato.nome, &novoContato.tel, novoContato.email) != EOF){
        espalhamento(tabelahash, novoContato);
    }

    fclose(arquivo);
    
    do{
        printf("\tMenu:\n"
                "1- Adcionar contato\n"
                "2- Buscar contato\n"
                "3- Mostrar tabela\n"
                "4- Remover contato\n"
                "5- Sair\n"
                "Escolha uma opção: \n");
        scanf("%i", &opcao);

        switch(opcao){
            case 1:
                printf("Informe o nome do contato:\n");
                fgets(novoContato.nome, sizeof(novoContato.nome), stdin);
                //remove o \n 
                novoContato.nome[strcspn(novoContato.nome, "\n")] = '\0';

                
                printf("Informe o telefone do contato:\n");
                scanf("%i", &novoContato.tel);
                //mesmo do anterior
                getchar();
                
                printf("Informe o email do contato:\n");
                fgets(novoContato.email, sizeof(novoContato.email), stdin);
                //remove o \n 
                novoContato.email[strcspn(novoContato.email, "\n")] = '\0';

                espalhamento(tabelahash, novoContato);
                break;
            case 2:
                printf("Informe o telefone do contato que deseja buscar:\n");
                scanf("%i", &chave);
                contato *resultado = busca(tabelahash, chave);
                if(resultado->livre != true){
                printf("Nome: %s\nTelefone: %i\nEmail: %s\n", resultado->nome, resultado->tel, resultado->email);
                }else{
                    printf("Contato não encontrado.\n");
                }
                break;
            case 3:
                printf("\tTabela Hash\n");
                mostraTabela(tabelahash);
                break;
            case 4:
                printf("Informe o telefone do contato que deseja remover:\n");
                scanf("%i", &chave);
                remover(tabelahash, chave);
                break;
            case 5:
                printf("Até a próxima\n");
                break;
            default:
            printf("Opção invalida!\n");

        }
    }while(opcao != 5);

    return 0;
}