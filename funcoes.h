#ifndef FUNCOES_H
#define FUNCOES_H

#include "struct_func.h"

//ASSINATURA DAS FUNCOES

void limpar_buffer();
void pause_system();
int menu_principal();
void main_trabalho();
void gerenciar_clientes(Cliente **lista);
void gerenciar_produtos(Produto **lista);
void modo_compra(Cliente **c, Produto **p);
void liberar_memoria(Cliente *c, Produto *p);

//Funcoes de Cliente
void cadastrar_cliente(Cliente **lista);
void listar_clientes(Cliente *lista);
void buscar_cliente(Cliente *lista);
void editar_cliente(Cliente *lista);
void remover_cliente(Cliente **lista);


//Funcao de Produto

void cadastrar_produto(Produto **lista);
void listar_produtos(Produto *lista);
void buscar_produto(Produto *lista);

#endif




