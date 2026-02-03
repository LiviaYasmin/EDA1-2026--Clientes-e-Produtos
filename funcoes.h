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

#endif



