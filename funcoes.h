#ifndef FUNCOES_H
#define FUNCOES_H

#include "struct_func.h"


void main_trabalho();

//-------------------------------------------------------------------
//MENU
int menu_principal();
void gerenciar_clientes(Cliente **lista_c);
void gerenciar_produtos(Produto **lista_p);
void modo_compra(Cliente **lista_c, Produto **lista_p);

//-------------------------------------------------------------------
//FUNCOES DO CLIENTE
void cadastrar_cliente(Cliente **lista);
void listar_clientes(Cliente *lista);
void buscar_cliente(Cliente *lista);
void editar_cliente(Cliente *lista);
void remover_cliente(Cliente **lista);

//-------------------------------------------------------------------
//FUNCOES DO PRODUTO
void cadastrar_produto(Produto **lista);
void listar_produtos(Produto *lista);
void buscar_produto(Produto *lista);
void editar_produto(Produto *lista);
void remover_produto(Produto **lista);

//-------------------------------------------------------------------
//FUNCOES DO CARRINHO
void adicionar_ao_carrinho(Cliente *cliente, Produto *lista_prod);
void listar_carrinho(Cliente *cliente);
void remover_do_carrinho(Cliente *cliente);
//-------------------------------------------------------------------

void liberar_memoria(Cliente *lista_c, Produto *lista_p);
void limpar_buffer();
void pause_system();

#endif