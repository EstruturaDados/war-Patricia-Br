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

// Funções
void limparBufferEntrada() {
  int c;
  while ((c = getchar()) != '\n' && c != EOF);
}

void cadastrarTerritorios(struct Territorio *listaTerritorios, int *quantTerritorios, int max_tropas){
    printf("\nVamos cadastrar os %d territórios iniciais do nosso mundo.\n", max_tropas);

    //cadastro dos territorios
    for (int i = 0; i < max_tropas; i++){
        printf("\n------ Cadastrando territorio %d ------\n", i + 1);
        
        int indice = *quantTerritorios;

        printf("Nome do Território: ");
        fgets(listaTerritorios[indice].nome, TAM_STRING, stdin);
        
        printf("Cor do Exercito (ex: Azul,Verde): ");
        fgets(listaTerritorios[indice].cor, TAM_STRING_COR, stdin);
        
        printf("Número de tropas: ");
        scanf("%d", &listaTerritorios[indice].tropas);
        
        listaTerritorios[indice].nome[strcspn(listaTerritorios[indice].nome, "\n")] = '\0';
        listaTerritorios[indice].cor[strcspn(listaTerritorios[indice].cor, "\n")] = '\0';
        
        limparBufferEntrada();
        (*quantTerritorios)++;
    };

    printf("\n*** Cadastro inicial concluido com sucesso! ***\n");
}

void exibindoMenuAtaque(struct Territorio *listaTerritorios, int *quantTerritorios, int *opcao, int max_tropas, int exercitoAtacante, int missao){

    printf("\n============= MAPA DO MUNDO - ESTADO ATUAL =============\n");
    for (int i = 0; i < *quantTerritorios; i++){
        printf("%d. %s (Exército %s, Tropas: %d)\n", i + 1, listaTerritorios[i].nome, listaTerritorios[i].cor, listaTerritorios[i].tropas);
    };
    printf("========================================================\n");

    printf("\n+=+=+- SUA MISSÃO: EXÉRCITO %s -+=+=+\n", listaTerritorios[exercitoAtacante].cor);
    printf("      Destruir o exército (%s)    \n", listaTerritorios[missao].cor);
    
    // escolha de ataque entre os territorios
    printf("\n--- MENU DE AÇÕES ---\n");
    // escolha do territorio atacante
    // printf("Escolha  o território atacante (1 a %d, ou 0 para sair): ", max_tropas);
    printf("1. Atacar\n");
    printf("2. Verificar missão\n");
    printf("0. Sair\n");
    printf("Escolha sua opção: ");
    scanf("%d", opcao);
    limparBufferEntrada();
}

void atacar(struct Territorio *atacante, struct Territorio *defensor){
    // sorteio dos dados de batalha do atacante e defensor
    int atacante_sort = (rand() % 6) + 1;
    int defensor_sort = (rand() % 6) + 1;

    printf("Ataque (%s): %d | Defesa (%s): %d\n\n", atacante->nome, atacante_sort, defensor->nome, defensor_sort);

    // verificação e atualização de situação de ataque atual
    if (atacante_sort == defensor_sort){
        printf("EMPATE! Nenhuma tropa é perdida\n");

    }else if (strcmp(atacante->cor, defensor->cor) == 0){
        printf("x-x-x-x ATAQUE INTERROMPIDO x-x-x-x\natacante e defensor são aliados\n\n");
        printf("================================================\n\n");
    }else if (defensor->tropas == 0){
        printf(">>>> CONQUISTA <<<<\nO território (%s) foi dominado pelo Exército %s\n", defensor->nome, atacante->cor);

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

    int quantTerritorios = 0;
    int max_tropas;
    int entradaValida = 0;
    int opcao;
    int defensor;
    int atacante;
    
    printf("\n============================================================\n");
    printf("            WAR ESTRUTURADO - CADASTRO INICIAL   \n");
    printf("============================================================\n");
    
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
    struct Territorio *listaTerritorios = (struct Territorio *) calloc(max_tropas, sizeof(struct Territorio));

    if(listaTerritorios == NULL){
        printf("ERRO: Falha ao alocar memória");
        return 1;
    }

    cadastrarTerritorios(listaTerritorios, &quantTerritorios, max_tropas);
    
    int exercitoAtacante = rand() % max_tropas;
    int missao;
    do{
        missao = rand() % max_tropas;  
    } while (missao == exercitoAtacante);
    
    // laço principal
    do{
        //exibição de todos os territorios cadastrados a cada repetição do laço
        exibindoMenuAtaque(listaTerritorios, &quantTerritorios, &opcao, max_tropas, exercitoAtacante, missao);

        // validação de entradas de dados do usuario
        switch (opcao){
        case 1:
            printf("\n--- FASE DE ATAQUE ---\n");
            
            do{
                if (atacante == defensor){
                    printf("\nErro: atacante e defensor são iguais\n\n");
                }
                
                printf("Escolha o território atacante (1 a %d): ", max_tropas);
                scanf("%d", &atacante);
                limparBufferEntrada();
    
                printf("Escolha o território defensor (1 a %d): ", max_tropas);
                scanf("%d", &defensor);
                limparBufferEntrada();
                
            } while (atacante == defensor);

            printf("\n================================================\n\n");
            printf("--- RESULTADO DA BATALHA ---\n\n");
        
            atacar(&listaTerritorios[atacante-1], &listaTerritorios[defensor-1]);            

            printf("================================================\n\n");
            printf("pressione enter para o próximo turno...");
            getchar();
            break;

        case 2:
            if (listaTerritorios[missao].tropas == 0){
                printf("\nParabéns!!! Sua missão foi concluída\n\n");
            } else{
                printf("\nVoce ainda não cumpriu sua missão. Continue a lutar\n\n");
            }
            
            printf("pressione enter para o próximo turno...");
            getchar();
            break;

        
        case 0:
            printf("\nJogo encerrado e memória liberada. Até a proxima\n"); 
            break;
        
        default:
            printf("\nOpção invalida! tente novamente");
            printf("\npressione enter para sair...");
            getchar();
            limparBufferEntrada();
            break;
        }

    } while (opcao != 0);

    // libera memoria ao encerrar o jogo
    liberarMemoria(listaTerritorios);

    return 0;
}
