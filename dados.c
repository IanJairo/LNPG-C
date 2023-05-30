#include "dados.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

Aluno *criarAluno(char *matricula,
                  char *cpf,
                  char *nome,
                  Endereco *end)

{
    Aluno *aluno = (Aluno *)malloc(sizeof(Aluno));
    if (aluno)
    {
        strcpy(aluno->matricula, matricula); // Copia matricula para aluno->matricula
        strcpy(aluno->cpf, cpf);
        strcpy(aluno->nome, nome);
        aluno->endereco = end;
    }
    else
    {
        perror("Não há memória disponível. Encerrando\n\n");
    }
    return aluno;
}

Aluno *atualizarAluno(Aluno *aluno, Aluno *novo_aluno)
{
    if (aluno && novo_aluno)
    {
        strcpy(aluno->cpf, novo_aluno->cpf);
        strcpy(aluno->nome, novo_aluno->nome);
        aluno->endereco = novo_aluno->endereco;
    }
    return aluno;
}

void destruirAluno(Aluno *aluno)
{
    if (aluno)
    {
        Endereco *end = aluno->endereco;
        destruirEndereco(end);
        free(aluno);
    }
}

Endereco *criarEndereco(char *logradouro,
                        char *bairro,
                        char *cidade,
                        char *estado,
                        char *numero)
{
    Endereco *endereco = (Endereco *)malloc(sizeof(Endereco));
    if (endereco)
    {
        strcpy(endereco->logradouro, logradouro);
        strcpy(endereco->bairro, bairro);
        strcpy(endereco->cidade, cidade);
        strcpy(endereco->estado, estado);
        strcpy(endereco->numero, numero);
    }
    else
    {
        perror("Não há memória disponível. Encerrando\n\n");
    }
    return endereco;
}

void destruirEndereco(Endereco *endereco)
{
    if (endereco)
        free(endereco);
}

/*
----Professor----
*/

Professor *criarProfessor(char *matricula, char *nome, char *cpf, Endereco *end)

{
    Professor *professor = (Professor *)malloc(sizeof(Professor));
    if (professor)
    {
        memset(professor, 0, sizeof(Professor));
        strcpy(professor->matricula, matricula);
        strcpy(professor->cpf, cpf);
        strcpy(professor->nome, nome);
        professor->endereco = end;
    }
    else
    {
        perror("Não há memória disponível. Encerrando\n\n");
    }
    return professor;
}

Professor *atualizarProfessor(Professor *professor, Professor *novo_professor)
{
    if (professor && novo_professor)
    {
        strcpy(professor->cpf, novo_professor->cpf);
        strcpy(professor->nome, novo_professor->nome);
        professor->endereco = novo_professor->endereco;
    }
}

void destruirProfessor(Professor *professor)
{
    if (professor)
    {
        Endereco *end = professor->endereco;
        destruirEndereco(end);
        free(professor);
    }
}

/*
---- Turma ----
 */

Turma *atualizarTurma(Turma *turma, Turma *nova_turma)
{
    if (turma && nova_turma)
    {
        strcpy(turma->nome_disciplina, nova_turma->nome_disciplina);
        turma->media_turma = nova_turma->media_turma;
    }
    return turma;
}

Turma *criarTurma(char *codigo_turma,
                  char *nome_disciplina,
                  float media_turma)
{
    Turma *turma = (Turma *)malloc(sizeof(Turma));
    if (turma)
    {
        strcpy(turma->codigo, codigo_turma);
        strcpy(turma->nome_disciplina, nome_disciplina);
        turma->professor = NULL;
        turma->media_turma = media_turma;
        turma->qtd_alunos = 0;
    }
    else
    {
        perror("Não há memória disponível. Encerrando\n\n");
    }

    return turma;
}

Turma *adicionarAluno(Turma *turma, Aluno *aluno)
{
    if (turma && aluno)
    {
        turma->lista_alunos[turma->qtd_alunos] = aluno;
        turma->qtd_alunos += 1;
    }
    return turma;
}

// adicionar a função excluirAluno dentro da turma

Turma *excluirAluno(Turma *turma, Aluno *aluno)
{
    if (turma && aluno)
    {
        int i = 0;
        for (i = 0; i < turma->qtd_alunos; i++)
        {
            if (turma->lista_alunos[i] == aluno)
            {
                turma->lista_alunos[i] = NULL;
                turma->qtd_alunos -= 1;
                return turma;
            }
        }
    }
    return NULL;
}

void destruirTurma(Turma *turma)
{
    if (turma)
        free(turma);
}

Turma *adicionarProfessor(Turma *turma, Professor *professor)
{
    turma->professor = (Professor *)realloc(turma->professor, sizeof(Professor));
    if (turma && professor)
    {
        turma->professor = professor;
    }

    return turma;
}

/*

    PERISISTENCIA DE DADOS DOS ALUNOS

*/

// Função de encerramento para salvar os alunos em um arquivo binário
void salvarAlunosNoArquivo(Aluno *alunos[], int qtd_atual_aluno)
{
    FILE *arquivo = fopen("alunos.bin", "wb");
    if (arquivo == NULL)
    {
        printf("Erro ao abrir o arquivo alunos.bin\n");
        exit(1);
    }

    for (int i = 0; i < qtd_atual_aluno; i++)
    {
        fwrite(alunos[i], sizeof(Aluno), 1, arquivo);
        fwrite(alunos[i]->endereco, sizeof(Endereco), 1, arquivo);
    }

    fclose(arquivo);
}

void recuperarAlunosDoArquivo(Aluno *alunos[], int *qtd_atual_aluno)
{
    FILE *arquivo = fopen("alunos.bin", "rb");
    if (arquivo == NULL)
    {
        printf("Erro ao abrir o arquivo alunos.bin\n");
        exit(1);
    }

    fseek(arquivo, 0L, SEEK_END);
    int tamanho = ftell(arquivo) / sizeof(Aluno);
    printf("Número de alunos = %d\n", tamanho);
    rewind(arquivo);

    for (int i = 0; i < tamanho; i++)
    {
        alunos[i] = malloc(sizeof(Aluno));

        if (alunos[i] == NULL)
        {
            printf("Erro na alocação de memória para o aluno\n");
            exit(1);
        }

        fread(alunos[i], sizeof(Aluno), 1, arquivo);

        // Aloca memória para a estrutura endereco
        alunos[i]->endereco = malloc(sizeof(Endereco));

        if (alunos[i]->endereco == NULL)
        {
            printf("Erro na alocação de memória para o endereço do aluno\n");
            exit(1);
        }

        fread(alunos[i]->endereco, sizeof(Endereco), 1, arquivo);

    }

    *qtd_atual_aluno = tamanho;
    fclose(arquivo);
}

/*

    PERISISTENCIA DE DADOS DOS PROFESSORES

*/

void salvarProfessoresNoArquivo(Professor *professores[], int qtd_atual_professor)
{
    FILE *arquivo = fopen("professores.bin", "wb");
    if (arquivo == NULL)
    {
        printf("Erro ao abrir o arquivo professores.bin\n");
        exit(1);
    }

    for (int i = 0; i < qtd_atual_professor; i++)
    {
        fwrite(professores[i], sizeof(Professor), 1, arquivo);
        fwrite(professores[i]->endereco, sizeof(Endereco), 1, arquivo);
    }

    fclose(arquivo);
}


// Função de inicialização para recuperar os professores de um arquivo binário
void recuperarProfessoresDoArquivo(Professor *Professores[], int *qtd_atual_professor)
{
    FILE *arquivo = fopen("professores.bin", "rb");
    if (arquivo == NULL)
    {
        printf("Erro ao abrir o arquivo professores.bin\n");
        exit(1);
    }

    fseek(arquivo, 0L, SEEK_END);
    int tamanho = ftell(arquivo) / sizeof(Professor);
    printf("Número de professores = %d\n", tamanho);
    rewind(arquivo);

    for (int i = 0; i < tamanho; i++)
    {
        Professores[i] = malloc(sizeof(Professor));

        if (Professores[i] == NULL)
        {
            printf("Erro na alocação de memória para o professor\n");
            exit(1);
        }

        fread(Professores[i], sizeof(Professor), 1, arquivo);

        // Aloca memória para a estrutura endereco
        Professores[i]->endereco = malloc(sizeof(Endereco));

        if (Professores[i]->endereco == NULL)
        {
            printf("Erro na alocação de memória para o endereço do professor\n");
            exit(1);
        }

        fread(Professores[i]->endereco, sizeof(Endereco), 1, arquivo);
    }

    *qtd_atual_professor = tamanho;
    fclose(arquivo);
}
