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
    printf("4 - Central de estatisticas\n");
    printf("5 - Sair\n");

    do // Loop do-while até digitar opção válida
    {

        printf("Selecione a central: ");
        scanf("%d", &opcao); // recebe input
        getchar(); // limpa buffer

        if (opcao > 0 && opcao < 6) // Se o n° digitado está entre 1 e 5
        {
            return opcao;
        }
        printf("Opcao inválida!! Tente novamente\n\n"); 

    } while (1);
}

int menu_crud_aluno() // Função para CRUD do aluno
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

    do // Loop do-while até digitar opção válida
    {
        printf("Opcao: ");
        scanf("%d", &opcao); // recebe input
        getchar(); // limpa buffer
        if (opcao > 0 && opcao < 6) // Se o n° digitado está entre 1 e 5
        {
            return opcao;
        }
        printf("Opcao invalida! Tente novamente\n\n");

    } while (1);
}

int menu_crud_professor() // Função para CRUD do professor
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

    do // Loop do-while até digitar opção válida
    {
        printf("Opcao: ");
        scanf("%d", &opcao); // recebe input
        getchar(); // limpa buffer
        if (opcao > 0 && opcao < 6) // Se o n° digitado está entre 1 e 5
        {
            return opcao;
        }
        printf("Opcao invalida! Tente novamente\n\n");

    } while (1);
}

int menu_crud_turma() // Função CRUD da turma
{
    int opcao = 0;

    printf("==========================================\n");
    printf("============ Central da Turma ============\n");
    printf("==========================================\n\n");
    printf("1 - Adicionar turma\n");
    printf("2 - Buscar turma\n");
    printf("3 - Atualizar turma\n");
    printf("4 - Excluir turma\n\n");

    printf("== Vinculo do Aluno ==\n");
    printf("5 - Adicionar aluno\n");
    printf("6 - Remover aluno\n\n");

    printf("== Vinculo do Professor ==\n");
    printf("7 - Adicionar professor\n");
    printf("8 - Remover professor\n\n");
    
    printf("9 - Voltar menu anterior\n\n");
    
    do
    {
        printf("Opcao: ");
        scanf("%d", &opcao); // recebe input
        getchar(); // limpa buffer
        if (opcao > 0 && opcao < 10) // Se o n° digitado está entre 1 e 9
        {
            return opcao;
        }
        printf("Opcao invalida! Tente novamente\n\n");

    } while (1);
}

int menu_estatistica() // Função para o menu de estatistica
{
    int opcao = 0;
    printf("==========================================\n");
    printf("======== Central de estatisticas =========\n");
    printf("==========================================\n\n");
    printf("1 - Exibir nome dos professores\n");
    printf("2 - Exibir matriculas dos professores que nao possuem turmas\n");
    printf("3 - Calculo da media de todas as turmas\n");
    printf("4 - Voltar ao menu anterior\n");
    
    do // Loop do-while até digitar opção válida
    {
        printf("Opcao: ");
        scanf("%d", &opcao); // recebe input
        getchar(); // limpa buffer
        if (opcao > 0 && opcao < 5) // Se o n° digitado está entre 1 e 4
        {
            return opcao;
        }
        printf("Opcao invalida! Tente novamente\n\n");

    } while (1);
}

/*
Nota-se que todas as funções possuem os mesmos comandos, com a mesma função, porém, para menus diferentes.
*/
