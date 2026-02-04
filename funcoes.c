#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

void gerenciar_clientes(Cliente **lista_c) {//pq reomver e cadastrar precisa alterar o inicio da lista
    int op;
    do {
        printf("\n--- GESTAO DE CLIENTES ---\n");
        printf("1. Cadastrar Cliente\n");
        printf("2. Listar Clientes\n");
        printf("3. Buscar Cliente (CPF)\n");
        printf("4. Editar Cliente\n");
        printf("5. Remover Cliente\n");
        printf("0. Voltar\n");
        printf("Escolha: ");
        scanf("%d", &op);
        limpar_buffer();

        switch(op) {
            case 1: cadastrar_cliente(lista_c); break;//mantem duplo
            case 2: listar_clientes(*lista_c); break;//so precisa de um ponteiro, n vai adicionar nem remover
            case 3: buscar_cliente(*lista_c); break;
            case 4: editar_cliente(*lista_c); break;
            case 5: remover_cliente(lista_c); break;
            case 0: break;
            default: printf("Opcao invalida.\n");
        }
        if(op != 0) 
        pause_system();//espera o enter
    } while(op != 0);
}

void gerenciar_produtos(Produto **lista_p) {
    int op;
    do {
        printf("\n--- GESTAO DE PRODUTOS ---\n");
        printf("1. Cadastrar Produto\n");
        printf("2. Listar Produtos\n");
        printf("3. Buscar Produto (Codigo)\n");
        printf("4. Editar Produto\n");
        printf("5. Remover Produto\n");
        printf("0. Voltar\n");
        printf("Escolha: ");
        scanf("%d", &op);
        limpar_buffer();

        switch(op) {
            case 1: cadastrar_produto(lista_p); break; //ponteiro duplo
            case 2: listar_produtos(*lista_p); break; //ponteiro simples
            case 3: buscar_produto(*lista_p); break; //apenas a busca
            case 4: editar_produto(*lista_p); break; //edição de produto e um ponteiro simples 
            case 5: remover_produto(lista_p); break; // aqui passa um duplo tambem
            case 0: break;
            default: printf("Opcao invalida.\n");
        }
        if(op != 0) pause_system();
    } while(op != 0);
}

void modo_compra(Cliente **lista_c, Produto **lista_p) {
    char cpf[15];
    printf("\n--- MODO COMPRA ---\n");
    printf("Digite o CPF do cliente para acessar o carrinho: ");
    scanf("%[^\n]", cpf);
    limpar_buffer();
    //ponteiro auxiliar que começa no primeiro cliente da lista
    Cliente *atual = *lista_c;
    while(atual != NULL && strcmp(atual->cpf, cpf) != 0) {
        atual = atual->prox;
    }
    // ee saiu do loop e for null, chegou ao fim sem encontrar nada
    if (atual == NULL) {
        printf("Cliente nao encontrado!\n");
        pause_system();
        return;
    }

    int op;
    do {
        // quando estiver tudo certo sera redirecionado para o menu
        printf("\n--- CARRINHO DE: %s ---\n", atual->nome);
        printf("1. Incluir Produto no Carrinho\n");
        printf("2. Listar Carrinho (Ver Totais)\n");
        printf("3. Retirar Produto do Carrinho\n");
        printf("0. Voltar\n");
        printf("Escolha: ");
        scanf("%d", &op);
        limpar_buffer();

        switch(op) {
            case 1: adicionar_ao_carrinho(&atual, *lista_p); break;// aqui vai passar o cliente atual e a lista de produtos, *lista_p 
            case 2: listar_carrinho(atual); break;
            case 3: remover_do_carrinho(atual); break;
            case 0: break;
            default: printf("Opcao invalida.\n");
        }
        if(op != 0) pause_system();
    } while(op != 0);
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
    novo_item->prox = cliente->carrinho;
    cliente->carrinho = novo_item;

    printf("Item adicionado ao carrinho!\n");
}

void listar_carrinho(Cliente *cliente) {
    ItemCarrinho *item = cliente->carrinho;
    if(!item) { printf("Carrinho vazio.\n"); return; }

    float total = 0;
    int qtd_itens = 0;

    printf("\n--- Carrinho de Compras ---\n");
    printf("%-20s | %-5s | %-10s | %-10s\n", "Produto", "Qtd", "Unit", "Subtotal");
    printf("--------------------------------------------------------\n");

    while(item != NULL) {
        // olha se o ponteiro para o produto ainda é valido
        if(item->produto != NULL) {
            // Acessa os dados seguindo o ponteiro, item,produto e preco
            float subtotal = item->produto->preco * item->quantidade_compra;
            
            printf("%-20s | %-5d | R$%-8.2f | R$%-8.2f\n", 
                   item->produto->nome, 
                   item->quantidade_compra, 
                   item->produto->preco, 
                   subtotal);
            
            total += subtotal;
            qtd_itens++;
        }
        item = item->prox;
    }
    printf("--------------------------------------------------------\n");
    printf("ITENS DIFERENTES: %d\n", qtd_itens);
    printf("VALOR TOTAL: R$ %.2f\n", total);
}

void remover_do_carrinho(Cliente *cliente) {
    int cod;
    printf("Digite o codigo do produto para retirar do carrinho: ");
    scanf("%d", &cod); limpar_buffer();

    ItemCarrinho *ant = NULL;
    ItemCarrinho *atual = cliente->carrinho;

    // olha a lista do carrinho procurando o produto pelo código
    while(atual != NULL) {
        //verifica o atual->produto antes de acessar "codigo" para evitar erros
        if(atual->produto != NULL && atual->produto->codigo == cod) {
            break;
        }
        ant = atual;
        atual = atual->prox;
    }

    if(atual == NULL) {
        printf("Item nao encontrado no carrinho.\n");
        return;
    }

    if(ant == NULL) cliente->carrinho = atual->prox;
    else ant->prox = atual->prox; 

    // O produto continua existindo na loja, só não está mais no carrinho, caso contrario poderia apagar da loja inteira.
    free(atual);
    printf("Item removido do carrinho.\n");
}

//Pra compilar só, colocar as funcoes de verdade aqui depois

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