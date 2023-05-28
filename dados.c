#include "dados.h" // Inclusão do .h definido anteriormente
// Inclusões de bibliotecas:
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/*
----Aluno-----
*/

Aluno *criarAluno(char *matricula,
                  char *cpf,
                  char *nome,
                  Endereco *end) // Foi criada a função com seus respectivos parâmetros.
{
    Aluno *aluno = (Aluno *)malloc(sizeof(Aluno));
    if (aluno)
    {
        strcpy(aluno->matricula, matricula); // Copia matricula para aluno->matricula
        strcpy(aluno->cpf, cpf); // Copia cpf para aluno->cpf
        strcpy(aluno->nome, nome); // Copia nome para aluno->nome
        aluno->endereco = end; // Atribui o valor do ponteiro end ao endereco vinculado a aluno
    }
    else
    {
        perror("Não há memória disponível. Encerrando\n\n"); // Caso der erro, o programa encerra.
    }
    return aluno;
}

Aluno *atualizarAluno(Aluno *aluno, Aluno *novo_aluno) //Adicinando a função de atualizar aluno.
{
    if (aluno && novo_aluno) // Verifica aluno e novo_aluno são nulos
    {
        strcpy(aluno->cpf, novo_aluno->cpf); // Copia cpf de novo_aluno para cpf de aluno
        strcpy(aluno->nome, novo_aluno->nome); // Copia nome de novo_aluno para nome de aluno
        aluno->endereco = novo_aluno->endereco;  // Atribui o valor do endereco do novo_aluno para aluno
    }
    return aluno;
}


//Adicionando função de Criar endereço
void destruirAluno(Aluno *aluno) 
{
    if (aluno) // Verifica se "aluno" não é nulo
    {
        Endereco *end = aluno->endereco; 
        destruirEndereco(end); // Libera a memória (remove) onde o end. associado ao aluno estava armazenado
        free(aluno); // Libera a memória do objeto "aluno"
    }
}

Endereco *criarEndereco(char *logradouro,
                        char *bairro,
                        char *cidade,
                        char *estado,
                        char *numero) // Foi criada a função com seus respectivos parâmetros.
{
    Endereco *endereco = (Endereco *)malloc(sizeof(Endereco)); 
    if (endereco) // Verificação de alocação de espaço na memória
    {
        strcpy(endereco->logradouro, logradouro);  // Copia logradouro para endereco->logradouro
        strcpy(endereco->bairro, bairro); // Copia bairro para endereco->bairro
        strcpy(endereco->cidade, cidade); // Copia cidade para endereco->cidade
        strcpy(endereco->estado, estado); // Copia estado para endereco->estado
        strcpy(endereco->numero, numero); //Copia numero para endereco->numero
    }
    else
    {
        perror("Não há memória disponível. Encerrando\n\n"); // Caso der erro, o programa encerra.
    }
    return endereco;
}
//Adicionando função de remoção do endereço
void destruirEndereco(Endereco *endereco)
{
    if (endereco) // Verifica se o objeto "endereco" não é nulo 
        free(endereco); // Se não for libera o esp. na memória do objeto "endereco"
}

/*
----Professor----
*/

Professor *criarProfessor(char *matricula,
                          char *nome, 
                          char *cpf,
                          Endereco *end) // Foi criada a função com seus respectivos parâmetros. 

{
    Professor *professor = (Professor *)malloc(sizeof(Professor));
    if(professor){ // Verificação de alocação de espaço na memória 
        memset(professor, 0, sizeof(Professor)); // Prenche os esp. na memória com 0, para começar nulo
        strcpy(professor->matricula, matricula); // Copia matricula para professor->matricula
        strcpy(professor->cpf, cpf); // Copia cpf para professor->cpf
        strcpy(professor->nome, nome); // Copia nome para professor->nome
        professor->endereco = end; // Atribui o valor do ponteiro end ao endereco vinculado a professor
    }else{
        perror("Não há memória disponível. Encerrando\n\n"); // Caso der erro, o programa encerra.
    }
    return professor;
}
// Adicionando a função de atualizar professor
Professor *atualizarProfessor(Professor *professor, Professor *novo_professor)
{
    if(professor && novo_professor){ // Verifica se ambos são nulos
        strcpy(professor->cpf, novo_professor->cpf); // Copia cpf do novo_professor para professor
        strcpy(professor->nome, novo_professor->nome); // Copia nome do novo_professor para professor
        professor->endereco = novo_professor->endereco; // Atribui o valor de endereco ao novo_professor para professor
    }
}
// Adicionando a função de remover professor
void destruirProfessor(Professor *professor)
{
    if(professor){ // Verifica se o objeto "professor" não é nulo
        Endereco *end = professor->endereco; // Copia endereco para professor, e atribui ao ponteiro *end
        destruirEndereco(end); // Chama a função para exclusão do *end
        free(professor); // Libera a memória do objeto "professor"
    }
}
/* 
---- Turma ----
 */
// Adicionando a função de atualizar turma
Turma *atualizarTurma(Turma *turma, Turma *nova_turma) 
{
    if (turma && nova_turma) // Verifica se são nulos ambos os parâmetros
    {
        strcpy(turma->nome_disciplina, nova_turma->nome_disciplina); // Copia nome_disciplina de nova_turma para nome_disciplina de turma 
        turma->media_turma = nova_turma->media_turma; // Atribui o valor media_turma de nova_turma para turma 
    }
    return turma;
}
// Adicionando a função de criar turma
Turma *criarTurma(char *codigo_turma,
                  char *nome_disciplina,
                  float media_turma) // Foi criada a função com seus respectivos parâmetros. 
{
    Turma *turma = (Turma *)malloc(sizeof(Turma)); 
    if(turma) // Verifica se o objeto é nulo
    {
        strcpy(turma->codigo, codigo_turma); // Copia codigo para turma->codigo turma
        strcpy(turma->nome_disciplina, nome_disciplina); // Copia nome_disciplina para turma->nome_disciplina 
        turma->professor = NULL; // Deixa turma como nulo
        turma->media_turma = media_turma; // Atribui o valor de media_turma para turma, e deixa esse novo valor como media_turma
        turma->qtd_alunos = 0; // Deixa quantidade de alunos =0
    }
    else 
    {
        perror("Não há memória disponível. Encerrando\n\n"); // Caso der erro, o programa encerra.
    }

    return turma;
}
// Adicionando a função de colocar um aluno dentro de uma turma
Turma *adicionarAluno(Turma *turma, Aluno *aluno) 
{
    if (turma && aluno) // Verifica se ambos são nulos 
    {
        turma->lista_alunos[turma->qtd_alunos] = aluno; // Adiciona aluno a lista de alunos da turma
        turma->qtd_alunos += 1; // Incrementa a quantidade de alunos +1
    }
    return turma;
}

// Adicionar a função de excluir Aluno dentro da turma
Turma *excluirAluno(Turma *turma, Aluno  *aluno)
{
    if (turma && aluno) // Verifica se ambos são nulos
    {
        int i = 0;
        for (i = 0; i < turma->qtd_alunos; i++) // Cria um for para passar por toda a turma 
        {
            if (turma->lista_alunos[i] == aluno) // Verifica se o aluno a ser excluído é igual o da posição atual
            {
                turma->lista_alunos[i] = NULL; // Remove o aluno da lista de aluno na posição específica
                turma->qtd_alunos -= 1; // Incrementa a quantidade de alunos a subtração de 1 aluno
                return turma;
            }
        }
    }
    return NULL;
}
// Adiciona a função de excluir TURMA
void destruirTurma(Turma *turma)
{
    if (turma) // Verifica se o valor é nulo
        free(turma); // Libera o esp. na memória que turma estava ocupando
}
// Adiciona a função de incluir um professor dentro da turma
Turma *adicionarProfessor(Turma *turma, Professor *professor)
{
    turma->professor = (Professor *)realloc(turma->professor, sizeof(Professor)); // Realoca a memória
    if (turma && professor) // Verifica se ambos são nulos
    {
        turma->professor = professor; // Atribui o valor do professor para turma
    }

    return turma;
}
