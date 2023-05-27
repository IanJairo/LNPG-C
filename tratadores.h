#ifndef _TRATADORES_H_
#define _TRATADORES_H_

#include "dados.h"

void tratador_menu_aluno(Aluno **alunos, int *qtd_atual_aluno);


// ALUNO

Aluno *buscar_aluno(Aluno **alunos, int *posicao);

void imprimir_aluno(Aluno *aluno);

Aluno *atualizar_aluno();

Endereco *construir_endereco();

Aluno *construir_aluno();


void imprimir_endereco(Endereco *endereco);


#endif