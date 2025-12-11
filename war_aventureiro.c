// ============================================================================
//         PROJETO WAR ESTRUTURADO - DESAFIO DE CÓDIGO
// ============================================================================
//        
// ============================================================================
//
// ============================================================================

// Inclusão das bibliotecas padrão necessárias para entrada/saída, alocação de memória, manipulação de strings e tempo.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

// --- Constantes Globais ---
// Definem valores fixos para o número de territórios, missões e tamanho máximo de strings, facilitando a manutenção.
#define TAM_STRING 30
#define TAM_STRING_COR 10

// --- Estrutura de Dados ---
// Define a estrutura para um território, contendo seu nome, a cor do exército que o domina e o número de tropas.
struct Territorio{
    char nome[TAM_STRING];
    char cor[TAM_STRING_COR];
    int tropas;
};

// --- Protótipos das Funções ---
void limparBufferEntrada() {
  int c;
  while ((c = getchar()) != '\n' && c != EOF);
}

void atacar(struct Territorio *atacante, struct Territorio *defensor){
    // sorteio dos dados de batalha do atacante e defensor
    int atacante_sort = (rand() % 6) + 1;
    int defensor_sort = (rand() % 6) + 1;

    printf("O atacante %s rolou um dado e tirou: %d\n", atacante->nome, atacante_sort);
    printf("O defensor %s rolou um dado e tirou: %d\n\n", defensor->nome, defensor_sort);

    // verificação e atualização de situação de ataque atual
    if (atacante_sort == defensor_sort){
        printf("EMPATE! Nenhuma tropa é perdida\n");

    }else if (strcmp(atacante->cor, defensor->cor) == 0){
        printf("x-x-x-x ATAQUE INTERROMPIDO x-x-x-x\natacante e defensor são aliados\n\n");
        printf("================================================\n\n");
    }else if (defensor->tropas == 0){
        printf(">>>> CONQUISTA <<<<\nO território (%s) foi dominado pelo Exército %s\n", defensor->nome, atacante->nome);

        strcpy(defensor->cor, atacante->cor);

        int metadeTropas = atacante->tropas / 2;

        defensor->tropas = metadeTropas;

    } else if (atacante_sort > defensor_sort){
        printf("*** VITÓRIA DO ATAQUE! defensor perde 1 tropa ***\n");
        defensor->tropas--;

    }else{
        printf("*** VITÓRIA DO DEFENSOR! atacante perde 1 tropa ***\n");
        atacante->tropas--;
    } 
}

void liberarMemoria(struct Territorio *listaTerritorios){
    free(listaTerritorios);
}

// --- Função Principal (main) ---
// Função principal que orquestra o fluxo do jogo, chamando as outras funções em ordem.
int main() {
    srand(time(NULL));

    struct Territorio *listaTerritorios;
    int quantTerritorios = 0;
    int max_tropas;
    
    printf("\n============================================================\n");
    printf("            WAR ESTRUTURADO - CADASTRO INICIAL   \n");
    printf("============================================================\n");
    
    int entradaValida = 0;
    
    do{
        printf("Digite o total de territorios que deseja cadastrar: ");
        
        if (scanf("%d", &max_tropas) == 0){
            printf("\nERRO: Digite apenas números\n\n");
            limparBufferEntrada();

        } else if(max_tropas <= 1){
            printf("\nNúmero precisa ser maior que 1.\n\n");
    
        } else{
            entradaValida = 1;
            limparBufferEntrada();
        }
    } while (entradaValida == 0);
    
    //usamos calloc para o array de livros. calloc(num_elementos, tamanho_de_cada_elemento)
    //Vantagem: inicializa toda a memoria com zeros.
    listaTerritorios = (struct Territorio *) calloc(max_tropas, sizeof(struct Territorio));

    if(listaTerritorios == NULL){
        printf("ERRO: Falha ao alocar memória");
        return 1;
    }

    printf("\nVamos cadastrar os %d territórios iniciais do nosso mundo.\n\n", max_tropas);

    //cadastro dos territorios
    for (int i = 0; i < max_tropas; i++){
        printf("\n--- Cadastrando territorio %d ---", i + 1);
        
        printf("\nNome do Território: ");
        fgets(listaTerritorios[i].nome, TAM_STRING, stdin);
        
        printf("\nCor do Exercito (ex: Azul,Verde): ");
        fgets(listaTerritorios[i].cor, TAM_STRING_COR, stdin);
        
        printf("\nNúmero de tropas: ");
        scanf("%d", &listaTerritorios[i].tropas);

        listaTerritorios[quantTerritorios].nome[strcspn(listaTerritorios[quantTerritorios].nome, "\n")] = '\0';
        listaTerritorios[quantTerritorios].cor[strcspn(listaTerritorios[quantTerritorios].cor, "\n")] = '\0';
        
        limparBufferEntrada();
        quantTerritorios++;
    };

    printf("\n*** Cadastro inicial concluido com sucesso! ***\n");
    printf("\n=====================================================\n");
    printf("            MAPA DO MUNDO - ESTADO ATUAL   \n");
    printf("=====================================================\n\n");

    int opcao;
    int defensor;
        
    // laço principal
    do{
        //exibição de todos os territorios cadastrados a cada repetição do laço
        for (int i = 0; i < quantTerritorios; i++){
            printf("%d. %s (Exército %s, Tropas: %d)\n", i + 1, listaTerritorios[i].nome, listaTerritorios[i].cor, listaTerritorios[i].tropas);
        };
        
        // escolha de ataque entre os territorios
        printf("\n--- FASE DE ATAQUE ---\n");
        // escolha do territorio atacante
        printf("Escolha  o território atacante (1 a 5, ou 0 para sair): ");
        scanf("%d", &opcao);
        limparBufferEntrada();

        // validação de entradas de dados do usuario
        if (opcao == 0){
            printf("Jogo encerrado e memória liberada. Até a proxima\n"); 
            break;
        }else if (opcao < 1 || opcao > 5 || isalpha(opcao)){
            printf("\nOpção invalida! tente novamente");
            printf("\npressione enter para sair...");
            getchar();
            break;
        } else{

            // escolha do territorio defensor
            printf("Escolha o território defensor (1 a 5): ");
            scanf("%d", &defensor);
            limparBufferEntrada();

            printf("================================================\n\n");
            printf("--- RESULTADO DA BATALHA ---\n\n");
        
            atacar(&listaTerritorios[opcao-1], &listaTerritorios[defensor-1]);            

            printf("================================================\n\n");
            printf("pressione enter para o próximo turno...");
            getchar();
        }    

    } while (opcao != 0);

    // libera memoria ao encerrar o jogo
    liberarMemoria(listaTerritorios);

    return 0;
}