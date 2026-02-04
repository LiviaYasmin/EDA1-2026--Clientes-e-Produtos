#ifndef FUNCOES_H
#define FUNCOES_H

#include "struct_func.h"

//ASSINATURA DAS FUNCOES


//MENU
int menu_principal();
void gerenciar_clientes(Cliente **lista_c);

//FUNCOES CLIENTE
void cadastrar_cliente(Cliente **lista);
void listar_clientes(Cliente *lista);
void buscar_cliente(Cliente *lista);
void editar_cliente(Cliente *lista);
void remover_cliente(Cliente **lista);

//FUNCOES PRODUTO
void cadastrar_produto(Produto **lista);
void listar_produtos(Produto *lista);
void buscar_produto(Produto *lista);
void editar_produto(Produto *lista);
void remover_produto(Produto **lista);


void limpar_buffer();
void pause_system();
#endif




