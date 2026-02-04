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

void listar_produtos(Produto *lista) {

    // verifica se a lista estiver vazia, se tiver ele sai 
    if(!lista) { printf("Nenhum produto cadastrado.\n"); return; }
    //osinal '-'alinha o texto pra ficar bonitinho
    printf("\n%-6s | %-20s | %-10s | %-5s\n", "Cod", "Nome", "Preco", "Qtd");

    printf("----------------------------------------------------\n");

    //quando tiver o produto na lista ele mostra e avança
    while(lista != NULL) {

        printf("%-6d | %-20s | R$%-8.2f | %-5d\n",
            lista->codigo, lista->nome, lista->preco, lista->quantidade);
        lista = lista->prox;

    }

}

void buscar_produto(Produto *lista) {
    
    //vai olhar a lista item por item, e verifica se está tudo certo 
    int cod;
    printf("Digite o codigo: ");
    scanf("%d", &cod); limpar_buffer();

    while(lista != NULL) {

        if(lista->codigo == cod) {

            printf("\nProduto: %s\nPreco: %.2f\nEstoque: %d\n",
                lista->nome, lista->preco, lista->quantidade);
            return;
        }
        //se não for o item, ele pula e vai pro outro
        lista = lista->prox;
    }

    printf("Produto nao encontrado.\n");
}

void editar_produto(Produto *lista) {
    int cod;
    printf("Digite o codigo do produto para editar: ");
    scanf("%d", &cod); limpar_buffer();

    while(lista != NULL) {
        if(lista->codigo == cod) {
            printf("Editando %s...\n", lista->nome);
            // atualiza os dados menos o codigo pq ele e unico
            printf("Novo Nome: "); scanf("%[^\n]", lista->nome); limpar_buffer();
            printf("Novo Preco: "); scanf("%f", &lista->preco);
            printf("Nova Quantidade: "); scanf("%d", &lista->quantidade); limpar_buffer();
            printf("Produto atualizado!\n");
            return;
        }
        lista = lista->prox;
    }
    printf("Produto nao encontrado.\n");
}

void remover_produto(Produto **lista) {
    int cod;
    printf("Digite o codigo para remover: ");
    scanf("%d", &cod); limpar_buffer();
    // o'ant' guarda no anterior para  refazer a ligação
    // ja o 'atual' percorre a lista procurando o produto
    Produto *ant = NULL;
    Produto *atual = *lista;
    // enquanto não acabar a lista e não achar o codigo, vai salvar e pular
    while(atual != NULL && atual->codigo != cod) {
        ant = atual;
        atual = atual->prox;
    }
    // se no final da "atual" for NULL, não achou nada
    if(atual == NULL) {
        printf("Produto nao encontrado.\n");
        return;
    }
    // aqui ele exclui o produto e pula pro proximo
    if(ant == NULL) *lista = atual->prox;
    //e nesse ele pula o intem que sera excluido
    else ant->prox = atual->prox;

    // Como foi usado o malloc para o nome e struct, precisa dar o free nos dois pra fazer a limpeza 
    free(atual->nome);
    free(atual);
    printf("Produto removido.\n");
}


//FUNÇÕES Do Carrinho
void adicionar_ao_carrinho(Cliente *cliente, Produto *lista_prod) {
    int cod, qtd;
    printf("Digite o codigo do produto: ");
    scanf("%d", &cod);

    //vai buscar o produto na lista geral
    Produto *p = lista_prod;
    while(p != NULL && p->codigo != cod) {
        p = p->prox;
    }

    if(p == NULL) {
        printf("Produto nao existe!\n"); // mostra se não existir
        return;
    }

    printf("Produto encontrado: %s (R$ %.2f)\n", p->nome, p->preco);
    printf("Quantidade desejada: ");
    scanf("%d", &qtd);
    limpar_buffer();

    //aqui aloca a estrutura do itemcarrinho, que e diferente do produto
    ItemCarrinho *novo_item = (ItemCarrinho*) malloc(sizeof(ItemCarrinho));
    //apontamos para o produto original pra economizar nA memória e manter os dados no eixo
    novo_item->produto = p;
    novo_item->quantidade_compra = qtd;
    novo_item->prox = NULL;
    cliente->carrinho = novo_item;

    printf("Item adicionado ao carrinho!\n");
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