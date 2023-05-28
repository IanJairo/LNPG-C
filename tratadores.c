#include "tratadores.h"
#include "menus.h"
#include <stdio.h>
#include "constantes.h"
#include <string.h>
#include <stdlib.h>

// Cases do aluno
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
            // if verificar_matricula(alunos, aluno->matricula)
            // {
            //     printf("Matricula já cadastrada!!\n");
            //     break;
            // }
            // else {
            //     alunos[i] = aluno;
            //     *qtd_atual_aluno++;
            // }*/
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
        // criar a função de atualizar aluno

        int posicao = 0;
        aluno = buscar_aluno(alunos, &posicao);
        if (aluno)
        {
            atualizar_aluno(aluno);
            printf("Atualizado com sucesso!\n\n");
        }
        else
        {
            printf("Aluno não encontrado!!\n");
        }
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

// Cases do professor
void tratador_menu_professor(Professor **professores, int *qtd_atual_professor, Turma **turmas)
{
    int opcao = menu_crud_professor();
    Professor *professor = NULL;
    switch (opcao)
    {
    case 1:
        if (*qtd_atual_professor >= MAX_PROFESSOR)
        {
            printf("Número máximo de professores atingido\n");
        }
        else
        {
            professor = construir_professor();
            if (professor)
            {
                for (int i = 0; i < *qtd_atual_professor; i++)
                {
                    if (strcmp(professores[i]->matricula, professor->matricula) == 0 ||
                        strcmp(professores[i]->cpf, professor->cpf) == 0)
                    {
                        printf("Ja existe um professor com a mesma matricula ou CPF\n");
                        free(professor);
                        return;
                    }
                }
                professores[*qtd_atual_professor] = professor;
                (*qtd_atual_professor)++;
            }
            else
            {
                printf("Falha ao criar professor. Não há memória disponível.\n");
            }
        }
        break;
    case 2:
    {
        int posicao = 0;
        professor = buscar_professor(professores, &posicao);
        if (professor)
        {
            imprimir_professor(professor);
        }
        else
        {
            printf("Professor não encontrado!\n");
        }
    }
    break;
    case 3:
    {
        int posicao = 0;
        professor = buscar_professor(professores, &posicao);
        if (professor)
        {
            atualizar_professor(professor);
            printf("Professor atualizado com sucesso!\n\n");
        }
        else
        {
            printf("Professor não encontrado!\n");
        }
    }
    break;
    case 4:
    {
        int posicao = 0;
        professor = buscar_professor(professores, &posicao);
        if (professor)
        {
            // Verificar se o professor está associado a alguma turma
            int associado = 0;
            for (int i = 0; i < MAX_TURMA; i++)
            {
                if (turmas[i] && strcmp(turmas[i]->professor->matricula, professor->matricula) == 0)
                {
                    associado = 1;
                    break;
                }
            }

            if (associado)
            {
                printf("Nao e possivel excluir o professor. Ele esta associado a uma turma.\n");
            }
            else
            {
                destruirProfessor(professor);
                professores[posicao] = NULL;
                (*qtd_atual_professor)--;
                printf("Professor excluído!\n");
            }
        }
        else
        {
            printf("Professor não encontrado!\n");
        }
    }
    break;
    default:
        printf("Retornando ao menu principal\n");
        break;
    }
}

// Cases da turma
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
            turma = construir_turma();
            if (turma)
            {
                for (int i = 0; i < *qtd_atual_turma; i++)
                {
                    if (strcmp(turmas[i]->codigo, turma->codigo) == 0)
                    {
                        printf("Ja existe uma turma com o mesmo codigo\n");
                        free(turma);
                        return;
                    }
                }
                turmas[*qtd_atual_turma] = turma;
                (*qtd_atual_turma)++;
            }
            else
            {
                printf("Falha ao criar turma. Nao ha memoria disponivel.\n");
            }
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
            printf("Não foi encontrada nenhuma turma com esse código !!\n");
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
                    excluirAluno(turma, aluno);
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
            printf("Turma nao encontrada no sistema!!\n");
        }
        break;
    }
    default:
        printf("Retornando ao menu principal\n");
        break;
    }
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
    printf("Numero\t> ");
    fgets(endereco.numero, 9, stdin);

    return criarEndereco(endereco.logradouro, endereco.bairro, endereco.cidade, endereco.estado, endereco.numero);
}

/*  =================================== ALUNOS ==   */
Aluno *construir_aluno()
{
    Aluno aluno;
    printf("Matricula\t> ");
    fgets(aluno.matricula, 9, stdin);
    printf("CPF\t> ");
    fgets(aluno.cpf, 12, stdin);
    printf("Nome\t> ");
    fgets(aluno.nome, 49, stdin);
    aluno.endereco = construir_endereco();
    return criarAluno(aluno.matricula, aluno.cpf, aluno.nome, aluno.endereco);
}

Aluno *atualizar_aluno(Aluno *aluno)
{
    Aluno novo_aluno;
    printf("CPF\t> ");
    fgets(novo_aluno.cpf, 12, stdin);
    printf("Nome\t> ");
    fgets(novo_aluno.nome, 49, stdin);
    novo_aluno.endereco = construir_endereco();
    return atualizarAluno(aluno, &novo_aluno);

    //     Professor novo_professor;
    //     printf("CPF\t> ");
    //     fgets(novo_professor.cpf, 12, stdin);
    //     printf("Nome\t> ");
    //     fgets(novo_professor.nome, 49, stdin);
    //     novo_professor.endereco = construir_endereco();
    //     return atualizarProfessor(professor, &novo_professor);
    // }
}
Aluno *buscar_aluno(Aluno **alunos, int *posicao)
{
    char matricula[50];
    printf("Matricula > ");
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

Aluno *verificar_matricula(Aluno **alunos, char *matricula)
{
    Aluno *resultado = NULL;
    for (int i = 0; i < MAX_ALUNO; i++)
    {
        if (alunos[i] && !strcmp(matricula, alunos[i]->matricula))
        {
            resultado = alunos[i];
            break;
        }
    }
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

/*  =================================== PROFESSOR ==   */

Professor *construir_professor()
{
    Professor *professor = (Professor *)malloc(sizeof(Professor));
    if (professor)
    {
        printf("Matricula do professor\t>");
        fgets(professor->matricula, 10, stdin);
        printf("CPF do professor\t>");
        fgets(professor->cpf, 13, stdin);
        printf("Nome do professor\t>");
        fgets(professor->nome, 50, stdin);
        professor->endereco = construir_endereco();
    }
    else
    {
        perror("Não há memória disponível. Encerrando\n\n");
    }
    return professor;
}

Professor *atualizar_professor(Professor *professor)
{
    Professor novo_professor;
    printf("CPF\t> ");
    fgets(novo_professor.cpf, 12, stdin);
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
    for (int i = 0; i < MAX_PROFESSOR; i++)
    {
        if (professores[i] && !strcmp(matricula, professores[i]->matricula))
        {
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

/*  =================================== TURMAS ==   */

Turma *construir_turma()
{
    Turma *turma = (Turma *)malloc(sizeof(Turma));
    if (turma)
    {
        printf("Codigo da turma\t> ");
        fgets(turma->codigo, 50, stdin);
        printf("Nome da disciplina\t> ");
        fgets(turma->nome_disciplina, 50, stdin);
        printf("Media\t> ");
        scanf("%f", &(turma->media_turma));
        getchar();
    }
    else
    {
        perror("Não há memória disponível. Encerrando\n\n");
    }
    return turma;
}

Turma *buscar_turma(Turma **turmas, int *posicao)
{
    char codigo[50];
    printf("Codigo da turma > ");
    fgets(codigo, 49, stdin);
    Turma *resultado = NULL;
    int pos_resultado = -1;
    for (int i = 0; i < MAX_TURMA; i++)
    {
        if (turmas[i] && !strcmp(codigo, turmas[i]->codigo))
        {
            resultado = turmas[i];
            pos_resultado = i;
            break;
        }
    }
    *posicao = pos_resultado;
    return resultado;
}

Turma *atualizar_turma(Turma *turma)
{
    Turma nova_turma;
    printf("Nome da Disciplina\t> ");
    fgets(nova_turma.nome_disciplina, 12, stdin);
    printf("Media\t> ");
    scanf("%f", &nova_turma.media_turma);
    return atualizarTurma(turma, &nova_turma);
}

void imprimir_turma(Turma *turma)
{
    printf("== Turma ==\n");
    printf("Codigo: %s", turma->codigo);
    printf("Nome da Disciplina: %s", turma->nome_disciplina);
    printf("Media da Turma: %.2f\n", turma->media_turma);
    printf("Quantidade de alunos: %d\n", turma->qtd_alunos);

    if (turma->professor != NULL)
    {
        printf("Professor: %s", turma->professor->nome);
    }

    if (turma->qtd_alunos != 0)
    {
        printf("---------------------\n");
        for (int i = 0; i < turma->qtd_alunos; i++)
        {
            printf("Nº do aluno: %d\n", i + 1);
            printf("Matrícula do aluno: %s", turma->lista_alunos[i]->matricula);
            printf("Nome do aluno: %s", turma->lista_alunos[i]->nome);
            printf("---------------------\n");
        }
    }
}

void adicionar_aluno(Turma *turma, Aluno *aluno)
{
    adicionarAluno(turma, aluno);
}

/*  =================================== ESTATISTICA ==   */

void tratador_menu_estatistica(Turma **turmas, Professor **professores)
{
    int opcao = menu_estatistica();
    switch (opcao)
    {
    case 1:
        imprimir_nomes_professores(professores);
        break;
    case 2:
        imprimir_professores_sem_turma(professores, turmas);
        break;
    case 3:
        imprimir_media_turmas(turmas);
        break;
    case 4:
        break;
    }
}

void imprimir_nomes_professores(Professor **professores)
{
    if (professores[0] == NULL)
    {
        printf("Nenhum professor cadastrado!\n");
        return;
    }
    printf("=== Professores Cadastrados ===\n\n");

    for (int i = 0; i < MAX_PROFESSOR; i++)
    {
        if (professores[i] == NULL)
        {
            printf("\n");
            return;
        }
        printf("%s", professores[i]->nome);
    }
}

void imprimir_professores_sem_turma(Professor **professores, Turma **turmas)
{
    if (professores[0] == NULL)
    {
        printf("Nenhum professor cadastrado!\n");
        return;
    }
    printf("=== Professores que nao possuem turma ===\n\n");

    int qtd_professores_sem_turma = 0;
    Professor *professores_sem_turma[MAX_PROFESSOR];

    for (int i = 0; i < MAX_PROFESSOR; i++)
    {
        if (professores[i] == NULL)
        {
            break;
        }

        int turma_encontrada = 0;

        for (int j = 0; j < MAX_TURMA; j++)
        {
            if (turmas[j] == NULL)
            {
                break;
            }
            if (turmas[j]->professor == professores[i])
            {
                turma_encontrada = 1;
                break;
            }
        }

        if (!turma_encontrada)
        {
            professores_sem_turma[qtd_professores_sem_turma] = professores[i];
            qtd_professores_sem_turma++;
        }
    }

    if (professores_sem_turma[0] == NULL)
    {
        printf("Todos os professores possuem uma turma!\n\n");
        return;
    }

    for (int i = 0; i < qtd_professores_sem_turma; i++)
    {
        if (professores_sem_turma[i] == NULL)
        {
            break;
        }
        printf("%s", professores_sem_turma[i]->matricula);
    }
}

void imprimir_media_turmas(Turma **turmas)
{
    if (turmas[0] == NULL)
    {
        printf("Nenhuma turma cadastrada!\n\n");
        return;
    }
    float soma = 0.0;
    int qtd_turmas = 0;
    for (int i = 0; i < MAX_TURMA; i++)
    {
        if (turmas[i] == NULL)
        {
            break;
        }
        // explicar isso
        ++qtd_turmas;
        soma += turmas[i]->media_turma;
    }
    printf("Nota media de todas as turmas cadastradas: %.2f\n\n", soma / qtd_turmas);
}