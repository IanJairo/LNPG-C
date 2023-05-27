#include "tratadores.h"
#include "menus.h"
#include <stdio.h>
#include "constantes.h"
#include <string.h>

// Funções do aluno
void tratador_menu_aluno(Aluno **alunos, int *qtd_atual_aluno)
{
    int opcao = menu_crud_aluno();
    Aluno *aluno = NULL;
    switch (opcao)
    {
    case 1:
        if (*qtd_atual_aluno >= MAX_ALUNO)
        {
            printf("Número máximo de alunos atingido\n");
        }
        else
        {
            // Passo 1: buscar posicao disponível
            int i = 0;
            for (; i < *qtd_atual_aluno; i++)
            {
                if (alunos[i] != NULL)
                {
                    // significa que esta posição está livre para uso
                    break;
                }
            }
            Aluno *aluno = construir_aluno();
            alunos[i] = aluno;
            *qtd_atual_aluno++;
        }
        break;
    case 2:
    {
        int posicao = 0;
        aluno = buscar_aluno(alunos, &posicao);
        if (aluno)
        {
            imprimir_aluno(aluno);
        }
        else
        {
            printf("Aluno não encontrado!!\n");
        }
    }
    break;
    case 3:
    {
        printf("Implementar a atualização de aluno\n");
    }

    break;
    case 4:
    {
        int posicao = 0;
        aluno = buscar_aluno(alunos, &posicao);
        if (aluno)
        {
            destruirAluno(aluno);
            alunos[posicao] = NULL;
            printf("Aluno destruido\n");
        }
        else
        {
            printf("Aluno não encontrado!!\n");
        }
    }

    break;
    default:
        printf("Retornando ao menu principal\n");
        break;
    }
}

void tratador_menu_professor(Professor **professores, int *qtd_atual_professor)
{
    int opcao = menu_crud_professor();
    Professor *professor = NULL;
    switch (opcao){
        case 1:
            if(*qtd_atual_professor >= MAX_PROFESSOR){
                printf("Número máximo de professores atingido\n");
            }else{
                int i = 0;
                for(; i <= *qtd_atual_professor; i++){
                    if(professores[i] == NULL){
                        break;
                    }
                }
                Professor *professor = construir_professor();
                professores[i] = professor;
                *qtd_atual_professor = *qtd_atual_professor+1;
            }
            break;
        case 2:{
            int posicao = 0;
            professor = buscar_professor(professores, &posicao);
            if(professor){
                imprimir_professor(professor);
            }else{
                printf("Professor não encontrado!\n");
            }
        }
        break;
        case 3:{
            int posicao = 0;
            professor = buscar_professor(professores, &posicao);
            if(professor){
                atualizar_professor(professor);
            }else{
                printf("Professor não encontrado!\n");
            }
        }
        break;
        case 4:{
            int posicao = 0;
            professor = buscar_professor(professores, &posicao);
            if(professor){
                destruirProfessor(professor);
                professores[posicao] = NULL;
                *qtd_atual_professor = *qtd_atual_professor-1;
                printf("Professor exlcluído!\n");
            }else{
                printf("Professor não encontrado!\n");
            }
        }
        break;
        default:
            printf("Retornando ao menu principal\n");
            break;
    }
}

Professor *construir_professor()
{
    Professor professor;
    printf("Matricula do professor\t>");
    fgets(professor.matricula, 9, stdin);
    printf("CPF do professor\t>");
    fgets(professor.cpf, 13, stdin);
    printf("Nome do professor\t>");
    fgets(professor.nome, 49, stdin);
    professor.endereco = construir_endereco();
    return criarProfessor(professor.matricula, professor.cpf, professor.nome, professor.endereco);
}
Professor *atualizar_professor(Professor *professor)
{
    Professor novo_professor;
    printf("CPF\t> ");
    fgets(novo_professor.cpf, 13, stdin);
    printf("Nome\t> ");
    fgets(novo_professor.nome, 49, stdin);
    novo_professor.endereco = construir_endereco();
    return atualizarProfessor(professor, &novo_professor);
}

Professor *buscar_professor(Professor **professores, int *posicao)
{
    char matricula[50];
    printf("Matricula do professor> ");
    fgets(matricula, 49, stdin);
    Professor *resultado = NULL;
    int pos_resultado = -1;
    for(int i = 0; i < MAX_PROFESSOR; i++){
        if(professores[i] && !strcmp(matricula, professores[i]->matricula)){
            resultado = professores[i];
            break;
        }
    }
    *posicao = pos_resultado;
    return resultado;
}

void imprimir_professor(Professor *professor)
{
    printf("Matricula do professor: %s", professor->matricula);
    printf("Nome do professor: %s", professor->nome);
    printf("CPF do professor: %s", professor->cpf);
    imprimir_endereco(professor->endereco);
}

Endereco *construir_endereco()
{
    Endereco endereco;

    printf("Logradouro\t> ");
    fgets(endereco.logradouro, 49, stdin);
    printf("Bairro\t> ");
    fgets(endereco.bairro, 49, stdin);
    printf("Cidade\t> ");
    fgets(endereco.cidade, 49, stdin);
    printf("Estado\t> ");
    fgets(endereco.estado, 9, stdin);
    printf("Número\t> ");
    fgets(endereco.numero, 9, stdin);

    return criarEndereco(endereco.logradouro, endereco.bairro, endereco.cidade, endereco.estado, endereco.numero);
}

Aluno *construir_aluno()
{
    Aluno aluno;
    printf("Matrícula\t> ");
    fgets(aluno.matricula, 9, stdin);
    printf("CPF\t> ");
    fgets(aluno.cpf, 13, stdin);
    printf("Nome\t> ");
    fgets(aluno.nome, 49, stdin);
    aluno.endereco = construir_endereco();
    return criarAluno(aluno.matricula, aluno.cpf, aluno.nome, aluno.endereco);
}

Aluno *buscar_aluno(Aluno **alunos, int *posicao)
{
    char matricula[50];
    printf("Matrícula > ");
    fgets(matricula, 49, stdin);
    Aluno *resultado = NULL;
    int pos_resultado = -1;
    for (int i = 0; i < MAX_ALUNO; i++)
    {
        // Vamos testar se o aluno existe e se a matricula e a buscada
        // strcmp compara strings. Se for 0 indica que são iguais
        if (alunos[i] && !strcmp(matricula, alunos[i]->matricula))
        {
            resultado = alunos[i];
            break;
        }
    }
    *posicao = pos_resultado;
    return resultado;
}

void imprimir_aluno(Aluno *aluno)
{
    printf("Matrícula: %s", aluno->matricula);
    printf("Nome: %s", aluno->nome);
    printf("CPF: %s", aluno->cpf);
    imprimir_endereco(aluno->endereco);
}

void imprimir_endereco(Endereco *endereco)
{
    printf("Logradouro: %s", endereco->logradouro);
    printf("Número: %s", endereco->numero);
    printf("Bairro: %s", endereco->bairro);
    printf("Cidade: %s", endereco->cidade);
    printf("Estado: %s", endereco->estado);
}

// FUNÇÕES DA TURMA
void tratador_menu_turma(Turma **turmas, Aluno **alunos, Professor **professores, int *qtd_atual_turma)
{
    int opcao = menu_crud_turma();
    Turma *turma = NULL;
    Aluno *aluno = NULL;
    Professor *professor = NULL;

    switch (opcao)
    {
    case 1:

        if (*qtd_atual_turma >= MAX_TURMA)
        {
            printf("Número máximo de turmas atingido\n");
        }
        else
        {
            int i = 0;
            for (; i <= *qtd_atual_turma; i++)
            {
                if (turmas[i] == NULL)
                {
                    break;
                }
            }
            Turma *turma = construir_turma();
            turmas[i] = turma;
            *qtd_atual_turma = *qtd_atual_turma + 1;
        }
        break;
    case 2:
    {
        int posicao = 0;
        turma = buscar_turma(turmas, &posicao);
        if (turma)
        {
            imprimir_turma(turma);
        }
        else
        {
            printf("Turma não encontrada!!\n");
        }
        break;
    }
    case 3:
    {
        int posicao = 0;
        turma = buscar_turma(turmas, &posicao);
        if (turma)
        {
            atualizar_turma(turma);
            printf("Turma atualizada com sucesso!\n");
        }
        else
        {
            printf("Turma não encontrada!!\n");
        }
        break;
    }
    case 4:
    {
        int posicao = 0;
        turma = buscar_turma(turmas, &posicao);
        if (turma)
        {
            destruirTurma(turma);
            turmas[posicao] = NULL;
            *qtd_atual_turma = *qtd_atual_turma - 1;
            printf("Turma destruida\n");
        }
        else
        {
            printf("Turma não encontrada!!\n");
        }
        break;
    }
    case 5:
    {
        int posicao = 0;
        turma = buscar_turma(turmas, &posicao);
        if (turma)
        {
            posicao = 0;
            aluno = buscar_aluno(alunos, &posicao);

            if (aluno)
            {
                adicionarAluno(turma, aluno);
                printf("O cadastro do aluno foi um sucesso!\n");
            }
            else
            {
                printf("Nao foi encontrado nenhum aluno!!\n");
            }
        }
        else
        {
            printf("Não foi encontrada nenhuma turma com !!\n");
        }
        break;
    }
    case 6:
    {

        int posicao = 0;
        turma = buscar_turma(turmas, &posicao);

        // Verifica se a turma existe
        if (turma) 
        {
            // Verifica se a turma possui alunos
            if (turma->lista_alunos)
            {
                // Busca o aluno
                posicao = 0;
                aluno = buscar_aluno(turma->lista_alunos, &posicao);

                // Verifica se o aluno existe
                if (aluno)
                {
                    // Remove o aluno da turma
                    removerAluno(turma, aluno);
                    printf("Aluno removido com sucesso!\n");
                }
                else
                {
                    printf("Aluno não encontrado!!\n");
                }
            }
            else
            {
                printf("Turma não possui alunos cadastrados!!\n");
            }
        }
        break;
    }
    case 7:
    {
        int posicao = 0;
        turma = buscar_turma(turmas, &posicao);
        if (turma)
        {
            posicao = 0;
            professor = buscar_professor(professores, &posicao);

            if (professor)
            {
                adicionarProfessor(turma, professor);
                printf("Professor adicionado a turma com sucesso!\n");
            }
            else
            {
                printf("Professor não encontrado no sistema!!\n");
            }
        }
        else
        {
            printf("Turma não encontrada no sistema!!\n");
        }
        break;
    }
    case 8:
    {
        int posicao = 0;
        turma = buscar_turma(turmas, &posicao);
        if (turma)
        {
            if (turma->professor)
            {
                turma->professor = NULL;
                printf("Professor removido com sucesso!\n");
            }
            else
            {
                printf("Turma não possui professor cadastrado!!\n");
            }
        }
        else
        {
            printf("Turma não encontrada no sistema!!\n");
        }
        break;
    }
    default:
        printf("Retornando ao menu principal\n");
        break;
    }
}
