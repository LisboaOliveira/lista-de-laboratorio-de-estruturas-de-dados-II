#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <math.h>

#define tamanho 199
#define aurea 0.618033

typedef struct Contatos{
 char *nome;
 char *tel;
 char *email;
 int livre;
}contato;

void iniciarTabela (contato tabelahash[]);

char acharchave(char chave[50]);

void espalhamento(contato tabelahash[], contato novo);

contato busca(contato tabelahash[], char chave[50]);

void mostraTabela(contato tabelahash[]);

void remover(contato tabelahash[], char chave[50]);

void removerNovaLinha(char *str);

int lerarquivo(contato tabelahash[], contato novoContato);

int main()
{
    setlocale(LC_ALL, "Portuguese");

    contato tabelahash[tamanho], novoContato;
    int opcao;
    char chave[50];

    iniciarTabela(tabelahash);

    lerarquivo(tabelahash, novoContato);
    
    do
    {
        printf("\tMenu:\n"
               "1- Adcionar contato\n"
               "2- Buscar contato\n"
               "3- Mostrar tabela\n"
               "4- Remover contato\n"
               "5- Sair\n"
               "Escolha uma opção: \n");
        scanf("%i", &opcao);
        getchar();

        switch (opcao)
        {
        case 1:
            printf("Informe o nome do contato:\n");
            novoContato.nome = (char *)malloc(50 * sizeof(char)); // Aloca memória para o nome
            fgets(novoContato.nome, 50, stdin); // Lê o nome do novo contato
            novoContato.nome[strcspn(novoContato.nome, "\n")] = '\0'; // Remove o caractere de nova linha

            printf("Informe o telefone do contato:\n");
            novoContato.tel = (char *)malloc(20 * sizeof(char)); // Aloca memória para o telefone
            fgets(novoContato.tel, 20, stdin); // Lê o telefone do novo contato
            novoContato.tel[strcspn(novoContato.tel, "\n")] = '\0'; // Remove o caractere de nova linha

            printf("Informe o email do contato:\n");
            novoContato.email = (char *)malloc(50 * sizeof(char)); // Aloca memória para o email
            fgets(novoContato.email, 50, stdin); // Lê o email do novo contato
            novoContato.email[strcspn(novoContato.email, "\n")] = '\0'; // Remove o caractere de nova linha

            espalhamento(tabelahash, novoContato);

            
            break;
        case 2:
            printf("Informe o nome do contato que deseja buscar:\n");
            fgets(chave, sizeof(chave), stdin);
            // remove o \n
            chave[strcspn(chave, "\n")] = '\0';

            contato resultado;
            resultado = busca(tabelahash, chave);

            if (strcmp(resultado.nome, chave) == 0){
                printf("Nome: %s\nTelefone: %s\nEmail: %s\n", resultado.nome, resultado.tel, resultado.email);
            }
            else
            {
                printf("Contato não encontrado.\n");
            }
            break;
        case 3:
            printf("\tTabela Hash\n");
            mostraTabela(tabelahash);
            break;
        case 4:
            printf("Informe o nome do contato que deseja remover:\n");
            fgets(chave, sizeof(chave), stdin);
            // remove o \n
            chave[strcspn(chave, "\n")] = '\0';

            remover(tabelahash, chave);
            break;
        case 5:
            printf("Até a próxima\n");
            break;
        default:
            printf("Opção invalida!\n");
        }
    
    } while (opcao != 5);

    return 0;
}

void iniciarTabela (contato tabelahash[]){
    for(int i=0; i < tamanho; i++){
        tabelahash[i].nome = "";
        tabelahash[i].tel = "";
        tabelahash[i].email = "";
        tabelahash[i].livre = 0;
    }
}

char acharchave(char chave[50]){
    int posicao = 0;
    for (int i = 0; chave[i] != '\0'; i++)
    {
        posicao += chave[i];
    }
    
    return (posicao * aurea)/tamanho;
}

void espalhamento(contato tabelahash[], contato novo){
    int posicao = acharchave (novo.nome);
    int ciclo = 0;
    int primeirachave = posicao;

    while(1){
        if (tabelahash[posicao].livre == 0){
            // Alocar memória dinamicamente para os campos nome, tel e email
            tabelahash[posicao].nome = (char *)malloc((strlen(novo.nome) + 1) * sizeof(char));
            tabelahash[posicao].tel = (char *)malloc((strlen(novo.tel) + 1) * sizeof(char));
            tabelahash[posicao].email = (char *)malloc((strlen(novo.email) + 1) * sizeof(char));

            strcpy(tabelahash[posicao].nome, novo.nome);
            strcpy(tabelahash[posicao].tel, novo.tel);
            strcpy(tabelahash[posicao].email, novo.email);

            tabelahash[posicao].livre = 1;
            break;
        }else{
            posicao++;
            if (posicao >= tamanho && ciclo == 0){
                posicao = 0;
                ciclo = 1; // Marcar que já completou um ciclo
            }
            if (posicao == primeirachave && ciclo == 1){
                break; // Sai se completar um ciclo sem encontrar a chave
            }
        }
    }
}

contato busca(contato tabelahash[], char chave[50]){
    int ciclo = 0;
    int posicao = acharchave(chave);
    int primeirachave = posicao;

    while (tabelahash[posicao].livre != 0){
        if (strcmp(tabelahash[posicao].nome, chave) == 0){
            return tabelahash[posicao];
        }else{
            posicao++;
            if (posicao >= tamanho && ciclo == 0){
                posicao = 0;
                ciclo = 1; // Marcar que já completou um ciclo
            }
            if (posicao == primeirachave && ciclo == 1){
                break; // Sai se completar um ciclo sem encontrar a chave
            }
        }
    }
    contato vazio = { .nome = "", .tel = "", .email = "", .livre = 0 };
    return vazio;
}

void mostraTabela(contato tabelahash[]){
    for (int i = 0; i < tamanho; i++)
    {
        if (tabelahash[i].livre != 0)
        {
            printf("Posicao %d:\n%s\n%s\n%s\n", i, tabelahash[i].nome, tabelahash[i].tel, tabelahash[i].email);
        }
        else
        {
            printf("Posicao %d: Vazio\n", i);
        }
    }
}

void remover(contato tabelahash[], char chave[50]){3
    int posicao = acharchave(chave);
    while (tabelahash[posicao].livre != 0)
    {
        if (strcmp(tabelahash[posicao].nome, chave) == 0)
        {
            tabelahash[posicao].livre = 0;
            printf("Contato removido.\n");
            return;
        }
        posicao = (acharchave(chave) + 1);
    }
    printf("Contato não encontrado.\n");
}

void removerNovaLinha(char *str){
    str[strcspn(str, "\n")] = '\0';
}

int lerarquivo(contato tabelahash[], contato novoContato){
    char nomeDoArquivo[30], linha[60];
    int controle = 0;
    FILE *arquivo;
    
    do
    {
        printf("Informe o nome do arquivo de contatos:\n");
        fgets(nomeDoArquivo, sizeof(nomeDoArquivo), stdin);
        nomeDoArquivo[strcspn(nomeDoArquivo, "\n")] = '\0';

        arquivo = fopen(nomeDoArquivo, "r");

        if (arquivo == NULL){
            printf("Erro ao abrir o arquivo.\nDeseja tentar novamente? (responda sim ou não)\n");
            char resposta; // declara aqui para q seja criada apenas se necessario
            scanf(" %c", &resposta);
            getchar();
            if (resposta != 's' && resposta != 'S'){
                printf("thau...");
                return 1; // encerra o programa se a resposnta for não
            }
        }
    } while (arquivo == NULL); // continua pedindo o nome do arquivo ate que seja aberto com sucesso

    while(fgets(linha, sizeof(linha), arquivo)){
        if (controle <= (tamanho - 1)/ 2){
            if(strstr(linha, "Nome: ") == linha){
            removerNovaLinha(linha);
            novoContato.nome = (char *)malloc((strlen(linha + strlen("Nome: ")) + 1) * sizeof(char));
            strcpy(novoContato.nome, linha + strlen("Nome: "));

            }
            if(strstr(linha, "Telefone: ") == linha){
            removerNovaLinha(linha);
            novoContato.tel = (char *)malloc((strlen(linha + strlen("Telefone: ")) + 1) * sizeof(char));
            strcpy(novoContato.tel, linha + strlen("Telefone: "));
            }
            if(strstr(linha, "Email: ") == linha){
            removerNovaLinha(linha);
            novoContato.email = (char *)malloc((strlen(linha + strlen("Email: ")) + 1) * sizeof(char));
            strcpy(novoContato.email, linha + strlen("Email: "));
            espalhamento(tabelahash, novoContato);
            }
            controle++;
        }
    }

    fclose(arquivo);
    return 0;
}