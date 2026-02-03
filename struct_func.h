#ifndef STRUCT_FUNC_H //se n definiu 
#define STRUCT_FUNC_H //define agora

//Cliente possui uma lista interna de Itens do Carrinho
//Cada Item do Carrinho aponta pra um Produto que ja existe

/* Estrutura para o Produto */
typedef struct Produto {
    int codigo;
    char *nome; // ter nomes de tamanho variavel
    float preco;
    int quantidade;
    struct Produto *prox; //proximo prdouto da lista
} Produto;

/* Estrutura para os itens do Carrinho (Lista encadeada dentro do Cliente) */
typedef struct ItemCarrinho {
    Produto *produto;       //ponteiro para o produto original, assim quando mudar no estoque muda no carrinho tbm
    int quantidade_compra;
    struct ItemCarrinho *prox;
} ItemCarrinho;

/* Estrutura para o Cliente */
typedef struct Cliente {
    char cpf[15];
    char *nome;
    char *email;
    char telefone[20]; 
    char data_nasc[12]; 
    ItemCarrinho *carrinho; //cabeca da lista
    struct Cliente *prox;
} Cliente;

#endif