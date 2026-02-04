#include <stdio.h>
#include <stdlib.h>

#include "funcoes.h"




void main_trabalho() {
    Cliente *lista_clientes = NULL;
    Produto *lista_produtos = NULL;
    int opcao;

    do {
        opcao = menu_principal();
        switch (opcao) {
            case 1:
                gerenciar_clientes(&lista_clientes);
                break;
            case 2:
                gerenciar_produtos(&lista_produtos);
                break;
            case 3:
                modo_compra(&lista_clientes, &lista_produtos);
                break;
            case 0:
                liberar_memoria(lista_clientes, lista_produtos);
                printf("Sistema encerrado com sucesso.\n");
                break;
            default:
                printf("\nOpcao invalida! Tente novamente.\n");
                pause_system();
        }
    } while (opcao != 0);
}


/* ===================================================================
   MENU
   =================================================================== */
int menu_principal() {
    int op;
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
    printf("\n=== MENU ===\n");
    printf("1. Gerenciamento de Clientes\n");
    printf("2. Gerenciamento de Produtos\n");
    printf("3. Modo Compra (Carrinho)\n");
    printf("0. Sair\n");
    printf("Escolha: ");
    scanf("%d", &op);
    limpar_buffer();
    return op;
}


/* ===================================================================
   FUNÇÕES DE CLIENTE
   =================================================================== */
void cadastrar_cliente(Cliente **lista) {
    Cliente *novo = (Cliente*) malloc(sizeof(Cliente));
    if (!novo) { printf("Erro de memoria!n"); return; }

    novo->nome = (char*) malloc(100 * sizeof(char));
    novo->email = (char*) malloc(100 * sizeof(char));

    printf("CPF: ");
    scanf("%[^\n]", novo->cpf); limpar_buffer();
    
    /* Verifica se CPF ja existe */
    Cliente *aux = *lista;
    while(aux != NULL) {
        if(strcmp(aux->cpf, novo->cpf) == 0) {
            printf("Erro: CPF ja cadastrado!n");
            free(novo->nome); free(novo->email); free(novo);
            return;
        }
        aux = aux->prox;
    }

    printf("Nome: ");
    scanf("%[^\n]", novo->nome); limpar_buffer();
    printf("Email: ");
    scanf("%[^\n]", novo->email); limpar_buffer();
    printf("Telefone: ");
    scanf("%[^\n]", novo->telefone); limpar_buffer();
    printf("Data Nasc (DD/MM/AAAA): ");
    scanf("%[^\n]", novo->data_nasc); limpar_buffer();

    novo->carrinho = NULL;
    novo->prox = *lista; // Inserção no início
    *lista = novo;

    printf("Cliente cadastrado com sucesso!n");
}





//FUNÇÕES Do PRODUTO
//reserva um espaco na memória usando o malloc para guardar o produto e o nome
void cadastrar_produto(Produto **lista) {
    Produto *novo = (Produto*) malloc(sizeof(Produto));
    novo->nome = (char*) malloc(100 * sizeof(char));

    printf("Codigo (unico): ");
    scanf("%d", &novo->codigo); limpar_buffer();
    //o codigo vai verifica a lista e se ja esxite cadastro
    Produto *aux = *lista;
    while(aux != NULL) {
    // se ja existir ele "joga fora" e libera a memória pra não ter dois ao mesmo tempo
        if(aux->codigo == novo->codigo) {
            printf("Erro: Codigo ja existe!\n");
            free(novo->nome); free(novo);
            return;
        }
        aux = aux->prox;
    }

    // se o produto e unico, ele chega aqui e pede o resto
    printf("Nome do Produto: ");
    scanf("%[^\n]", novo->nome); limpar_buffer();
    printf("Preco: ");
    scanf("%f", &novo->preco);
    printf("Quantidade em Estoque: ");
    scanf("%d", &novo->quantidade); limpar_buffer();

    //aqui se codigo for novo, ele colooca o produto na primeira posição da lista pra ser o primeiro.
    novo->prox = *lista;
    *lista = novo;
    printf("Produto cadastrado!\n");
}

//Pra compilar só, colocar as funcoes de verdade aqui depois
void gerenciar_clientes(Cliente **lista) {
    printf("\nGerenciamento de Clientes em desenvolvimento...\n");
    pause_system();
}

void gerenciar_produtos(Produto **lista) {
    printf("\nGerenciamento de Produtos em desenvolvimento...\n");
    pause_system();
}

void modo_compra(Cliente **c, Produto **p) {
    printf("\nModo Compra / Carrinho em desenvolvimento...\n");
    pause_system();
}

void liberar_memoria(Cliente *c, Produto *p) {
    printf("\nLimpando ponteiros e encerrando o sistema...\n");
}

// Limpa o lixo do teclado para não pular os próximos scanfs
void limpar_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Faz o programa esperar o usuário antes de limpar a tela
void pause_system() {
    printf("\nPressione ENTER para continuar...");
    limpar_buffer();
    getchar();
}