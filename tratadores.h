#ifndef _TRATADORES_H_
#define _TRATADORES_H_

#include "dados.h"
void tratador_menu_aluno(Aluno **alunos, int *qtd_atual_aluno);
void tratador_menu_estatisticas(Turma **turmas, Professor **professores);



/*

    Alunos

*/

Endereco *construir_endereco();
Aluno *construir_aluno();
Aluno *buscar_aluno(Aluno **alunos, int *posicao);
void imprimir_aluno(Aluno *aluno);
void imprimir_endereco(Endereco *endereco);



/*

    Turmas

*/

Turma *construir_turma();
Turma *buscar_turma(Turma **turmas, int *posicao);
Turma *atualizar_turma(Turma *turma);
void imprimir_turma(Turma *turma);

#endif