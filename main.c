// Importando códigos feitos anteriormente para rodarmos em nosso MAIN()
#include "menus.h" 
#include "tratadores.h"
#include "dados.h"
#include <stdio.h>
#include "constantes.h"
#include <stdlib.h>
#include <string.h>



int main(int argc, char const *argv[])
{
    int qtd_atual_aluno = 0;
    int qtd_atual_professor = 0;
    int qtd_atual_turma = 0;
    int op_menu_principal = 0;
    Professor *professores[MAX_PROFESSOR] = {NULL};
    Turma *turmas[MAX_TURMA] = {NULL};
    Aluno *alunos[MAX_ALUNO] = {NULL};

    // Recuperar os alunos do arquivo
    recuperarAlunosDoArquivo(alunos, &qtd_atual_aluno);

    do //Loop do-while
    {
        op_menu_principal = menu_principal();
        switch (op_menu_principal) // Caso op_menu_principal igual a 1,2,3,4 ou 5: 
        {
        case 1: 
            tratador_menu_aluno(alunos, &qtd_atual_aluno, turmas);
            break;
        case 2:
            tratador_menu_professor(professores, &qtd_atual_professor, turmas);
            break;
        case 3:
            tratador_menu_turma(turmas, alunos, professores, &qtd_atual_turma);
            break;
        case 4:
            tratador_menu_estatistica(turmas, professores);
            break;
        case 5:
            printf("Finalizando app...\n\n");
            // Registrar a função de encerramento para salvar os alunos no arquivo binário
            salvarAlunosNoArquivo(alunos, qtd_atual_aluno);

            break;
        }
    } while (op_menu_principal != 5);

    return 0;
}
