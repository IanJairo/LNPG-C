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

void destruirAluno(Aluno *aluno)
{
    if (aluno)
    {
        Endereco *end = aluno->endereco;
        destruirEndereco(end);
        free(aluno);
    }
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

void destruirEndereco(Endereco *endereco)
{
    if (endereco)
        free(endereco);
}

// Professor *atualiuzarProfessor(Professor *professor, Professor *novo_professor) {
//     if (professor && novo_professor) {
//         strcpy(professor->cpf, novo_professor->cpf);
//         strcpy(professor->nome, novo_professor->nome);
//         professor->endereco = novo_professor->endereco;
//     }
//     return professor;
// }