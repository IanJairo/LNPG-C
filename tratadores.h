// Esse arquivo é usado para declarar interfaces de funções, estruturas, constantes e outras definições que serão compartilhadas entre vários arquivos fonte (arquivos .c) do projeto.


#ifndef _TRATADORES_H_ // Verifica se _TRATADORES_H_ não foi definido
#define _TRATADORES_H_  // Define _TRATADORES_H_ 

#include "dados.h" // Traz o código dados.h
// Lista de funções para tratadores de erros:
void tratador_menu_aluno(Aluno **alunos, int *qtd_atual_aluno, Turma **turmas);
void tratador_menu_professor(Professor **professores, int *qtd_atual_professor, Turma **turmas);
void tratador_menu_turma(Turma **turmas, Aluno **alunos, Professor **professores, int *qtd_atual_turma);
void tratador_menu_estatistica(Turma **turmas, Professor **professores);


/*

    Alunos

*/

Endereco *construir_endereco();
Aluno *construir_aluno();
Aluno *atualizar_aluno(Aluno *aluno);
Aluno *buscar_aluno(Aluno **alunos, int *posicao);
void imprimir_aluno(Aluno *aluno);
void imprimir_endereco(Endereco *endereco);
Aluno *verificar_matricula(Aluno **alunos, char *matricula);
void persistir_alunos_em_arquivo(Aluno **alunos, int qtd_atual_aluno, const char *nome_arquivo);
/*

    Turmas

*/

Turma *construir_turma();
Turma *buscar_turma(Turma **turmas, int *posicao);
Turma *atualizar_turma(Turma *turma);
void imprimir_turma(Turma *turma);


/*
    Professor
*/

Professor *construir_professor();
Professor *atualizar_professor(Professor *professor);
Professor *buscar_professor(Professor **professores, int *posicao);
void imprimir_professor(Professor *professor);


/*
    Estatistica
*/

void imprimir_nomes_professores(Professor **professores);
void imprimir_professores_sem_turma(Professor **professores, Turma **turmas);
void imprimir_media_turmas(Turma **turmas);

#endif // Fim do bloco condicional
