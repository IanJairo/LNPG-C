#include "menus.h"
#include <stdio.h>

int menu_principal()
{
    int opcao = 0;
    printf("========================================\n");
    printf("============ Menu principal ============\n");
    printf("========================================\n\n");

    printf("1 - Central do Aluno\n");
    printf("2 - Central do Professor\n");
    printf("3 - Central da Turma\n");
    printf("4 - Sair\n");

    do
    {

        printf("Selecione a central: ");
        scanf("%d", &opcao);
        getchar();

        if (opcao > 0 && opcao < 5)
        {
            return opcao;
        }
        printf("Opcao inválida!! Tente novamente\n\n");

    } while (1);
}

int menu_crud_aluno()
{
    int opcao = 0;

    printf("==========================================\n");
    printf("============ Central do Aluno ============\n");
    printf("==========================================\n\n");
    printf("1 - Adicionar aluno\n");
    printf("2 - Buscar aluno\n");
    printf("3 - Atualizar aluno\n");
    printf("4 - Excluir aluno\n");
    printf("5 - Voltar menu anterior\n");
    
    do
    {
        printf("Opcao: ");
        scanf("%d", &opcao);
        getchar();
        if (opcao > 0 && opcao < 6)
        {
            return opcao;
        }
        printf("Opcao inválida!! Tente novamente\n\n");

    } while (1);
}

int menu_crud_professor()
{
    int opcao = 0;

    printf("==============================================\n");
    printf("============ Central do Professor ============\n");
    printf("==============================================\n\n");
    printf("1 - Adicionar professor\n");
    printf("2 - Buscar professor\n");
    printf("3 - Atualizar professor\n");
    printf("4 - Excluir professor\n");
    printf("5 - Voltar menu anterior\n");

    do
    {
        printf("Opcao: ");
        scanf("%d", &opcao);
        getchar();
        if (opcao > 0 && opcao < 6)
        {
            return opcao;
        }
        printf("Opcao inválida!! Tente novamente\n\n");

    } while (1);
}

int menu_crud_turma()
{
    int opcao = 0;

    printf("==========================================\n");
    printf("============ Central da Turma ============\n");
    printf("==========================================\n\n");
    printf("1 - Adicionar turma\n");
    printf("2 - Buscar turma\n");
    printf("3 - Atualizar turma\n");
    printf("4 - Excluir turma\n");
    printf("5 - Voltar menu anterior\n");
    do
    {
        printf("Opcao: ");
        scanf("%d", &opcao);
        getchar();
        if (opcao > 0 && opcao < 6)
        {
            return opcao;
        }
        printf("Opcao inválida!! Tente novamente\n\n");

    } while (1);
}