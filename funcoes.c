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
void cadastrar_cliente(Cliente **lista) { //alterar a lista na main e n na cópia
    Cliente *novo = (Cliente*) malloc(sizeof(Cliente)); //endre;co de memoria vazio dado pelo malloc do tamanho de Cliente que tem o nome de novo
    if (!novo) { 
        printf("Erro de memoria!n"); 
        return; 
    }

    novo->nome = (char*) malloc(100 * sizeof(char)); //o espaço vai recer nome e email que digitou
    novo->email = (char*) malloc(100 * sizeof(char));

    printf("CPF: ");
    scanf("%[^\n]", novo->cpf); //salva oq foi digitado dentro do campo cpf do cleinte novo 
    limpar_buffer();
    

    Cliente *aux = *lista;//ve se CPF ja existe e comeca no inicio da lista
    while(aux != NULL) { 
        if(strcmp(aux->cpf, novo->cpf) == 0) { //compara o cpf da lista com oq digitou
            printf("Erro: CPF ja cadastrado!\n"); //0 é que o cpf ja existe
            free(novo->nome); //se tem devolve a memoria reservada
            free(novo->email); 
            free(novo);
            return;
        }
        aux = aux->prox; //ve o resto da lista inteira pra ver se ja tem o cpf
    }

    //o cpf é novo:
    printf("Nome: ");
    scanf("%[^\n]", novo->nome); //le e reserva
    limpar_buffer();
    printf("Email: ");
    scanf("%[^\n]", novo->email); 
    limpar_buffer();
    printf("Telefone: ");
    scanf("%[^\n]", novo->telefone); 
    limpar_buffer();
    printf("Data Nasc (DD/MM/AAAA): ");
    scanf("%[^\n]", novo->data_nasc); 
    limpar_buffer();

    novo->carrinho = NULL; //cliente novo tem carrinho vazio
    novo->prox = *lista; // novo cliente aponta pro incio da lista atual
    *lista = novo;//o cliente novo vai ser o inicio da lista

    printf("Cliente cadastrado com sucesso!\n");
}

void listar_clientes(Cliente *lista) {
    if(lista == NULL) { //lista vazia
        printf("Nenhum cliente cadastrado.\n"); 
        return; 
    }

    //separar memoria e alinhar a esquerda
    //-->planilha
    printf("\n%-15s | %-20s | %-20s\n", "CPF", "Nome", "Email");
    printf("----------------------------------------------------------\n");
    
    while(lista != NULL) {
        printf("%-15s | %-20s | %-20s\n", lista->cpf, lista->nome, lista->email);//mostra o cliente
         lista = lista->prox; //vai pro proximo cliente
    }
}

void buscar_cliente(Cliente *lista) {
    char cpf[15]; //le o cpf que vai ser digitado
    printf("Digite o CPF: ");
    scanf("%[^\n]", cpf); 
    limpar_buffer();

    while(lista != NULL) {
        if(strcmp(lista->cpf, cpf) == 0) { //compara o cpf atual com oq ta procurando
            printf("\nEncontrado:\nNome: %s\nEmail: %s\nTelefone: %s\nNascimento: %s\n", 
                   lista->nome, lista->email, lista->telefone, lista->data_nasc);
            return;
        }
        lista = lista->prox; //se n achar continua a ver a lista
    }
    printf("Cliente nao encontrado.\n");
}

void editar_cliente(Cliente *lista) {
    char cpf[15];
    printf("Digite o CPF do cliente para editar: ");
    scanf("%[^\n]", cpf); 
    limpar_buffer();

    while(lista != NULL) {
        if(strcmp(lista->cpf, cpf) == 0) {
            printf("Editando %s...\n", lista->nome);
            printf("Novo Nome: "); scanf("%[^\n]", lista->nome); 
            limpar_buffer();
            printf("Novo Email: "); scanf("%[^\n]", lista->email); 
            limpar_buffer();
            printf("Novo Telefone: "); scanf("%[^\n]", lista->telefone); 
            limpar_buffer();
            printf("Nova Data Nasc: "); scanf("%[^\n]", lista->data_nasc); 
            limpar_buffer();
            printf("Dados atualizados!\n");
            return;
        }
        lista = lista->prox;
    }
    printf("Cliente nao encontrado.\n");
}

void remover_cliente(Cliente **lista) {
    char cpf[15];
    printf("Digite o CPF para remover: ");
    scanf("%[^\n]", cpf); 
    limpar_buffer();

    //Saber quem tava antes do cliente pra juntar de novo depois de remover
    Cliente *anterior = NULL; //n tem ngm antes do primeiro
    Cliente *atual = *lista; //comeca no inicio da lista

    while(atual != NULL && strcmp(atual->cpf, cpf) != 0) {//ver a lista
        anterior = atual;
        atual = atual->prox;
        //anterior-->atual que vira anterior-->proximo que vira atual
    }

    if(atual == NULL) { //n achou o cpf
        printf("Cliente nao encontrado.\n");
        return;
    }

  
    if(anterior == NULL) { //o cpf ta na primeira posicao
        *lista = atual->prox; //remove pulando o primeiro e aponta ja pro segundo
    } else {
        anterior->prox = atual->prox;//quando o meio sai, 1 e 3 tem que se juntar
    }

    
    ItemCarrinho *c = atual->carrinho;//limpa o carrinho primeiro pro cliente n ser deletado e o carrinho ocupar memoria sem dono
    while(c != NULL) {
        ItemCarrinho *tempC = c;
        c = c->prox;//segura o proximo
        free(tempC);//deleta o atual
    }

    free(atual->nome);//libera da memoria
    free(atual->email);
    free(atual);//libera a estrutura do cliente atual
    printf("Cliente removido com sucesso.\n");
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

//Limpa o lixo do teclado para não pular os próximos scanfs
void limpar_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

//Remove o enter pra n pular a proxima leitura
void pause_system() {
    printf("\nPressione ENTER para continuar...");
    limpar_buffer();
    getchar();
}