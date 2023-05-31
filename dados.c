#include "dados.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

Aluno *criarAluno(char *matricula,
                  char *cpf,
                  char *nome,
                  Endereco *end)

{
    Aluno *aluno = (Aluno *)malloc(sizeof(Aluno)); // Aloca memória para um objeto "Aluno"
    if (aluno)                                     // Verifica se a alocação de memória foi bem-sucedida
    {
        strcpy(aluno->matricula, matricula); // Copia a string "matricula" para o campo "matricula" do objeto "aluno" através da função strcpy
        strcpy(aluno->cpf, cpf);             // Copia a string "cpf" para o campo "cpf" do objeto "aluno"
        strcpy(aluno->nome, nome);           // Copia a string "nome" para o campo "nome" do objeto "aluno"
        aluno->endereco = end;               // Atribui o ponteiro "end" ao campo "endereco" do objeto "aluno"
    }
    else
    {
        perror("Não há memória disponível. Encerrando\n\n"); // Imprime uma mensagem de erro se a alocação de memória falhar
    }
    return aluno; // Retorna o ponteiro para o objeto "aluno" criado
}
Aluno *atualizarAluno(Aluno *aluno, Aluno *novo_aluno)
{
    if (aluno && novo_aluno) // Verifica se os ponteiros "aluno" e "novo_aluno" são válidos (não nulos)
    {
        strcpy(aluno->cpf, novo_aluno->cpf); // realiza o mesmo procedimento do bloco anterior
        strcpy(aluno->nome, novo_aluno->nome);
        aluno->endereco = novo_aluno->endereco;
    }
    return aluno; // Retorna o ponteiro para o objeto "aluno" (atualizado ou não)
}

void destruirAluno(Aluno *aluno)
{
    if (aluno) // Verifica se o ponteiro "aluno" é válido (não nulo)
    {
        Endereco *end = aluno->endereco; // Atribui o valor do campo "endereco" do objeto "aluno" a um novo ponteiro "end"
        destruirEndereco(end);           // Chama a função "destruirEndereco" para liberar a memória alocada para o objeto "endereco"
        free(aluno);                     // Libera a memória alocada para o objeto "aluno" utilizando a função "free"
    }
}

Endereco *criarEndereco(char *logradouro,
                        char *bairro,
                        char *cidade,
                        char *estado,
                        char *numero)
{
    Endereco *endereco = (Endereco *)malloc(sizeof(Endereco)); // Aloca memória para um objeto "Endereco"
    if (endereco)                                              // Verifica se a alocação de memória foi bem-sucedida
    {
        strcpy(endereco->logradouro, logradouro); // realiza o mesmo procedimento explicado anteriormente
        strcpy(endereco->bairro, bairro);
        strcpy(endereco->cidade, cidade);
        strcpy(endereco->estado, estado);
        strcpy(endereco->numero, numero);
    }
    else
    {
        perror("Não há memória disponível. Encerrando\n\n");
    }
    return endereco; // Retorna o ponteiro para o objeto "endereco" criado
}

void destruirEndereco(Endereco *endereco)
{
    if (endereco)       // Verifica se o ponteiro "endereco" é válido (não nulo)
        free(endereco); // Libera a memória alocada para o objeto "endereco" utilizando a função "free"
}

/*
----Professor----
*/

// Aqui é realizado o mesmo processo explicado na função "criarAluno"
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
// Aqui é realizado o mesmo processo explicado na função "atualizarAluno"
Professor *atualizarProfessor(Professor *professor, Professor *novo_professor)
{
    if (professor && novo_professor)
    {
        strcpy(professor->cpf, novo_professor->cpf);
        strcpy(professor->nome, novo_professor->nome);
        professor->endereco = novo_professor->endereco;
    }
}
// Aqui ocorre o mesmo processo explicado na função "destruirProfessor"
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
    if (turma && nova_turma) // Verifica se os ponteiros "turma" e "nova_turma" são válidos (não nulos)
    {
        strcpy(turma->nome_disciplina, nova_turma->nome_disciplina); // Copia a string "nome_disciplina" do objeto "nova_turma" para o campo "nome_disciplina" do objeto "turma"
        turma->media_turma = nova_turma->media_turma;                // Atribui o valor do campo "media_turma" do objeto "nova_turma" ao campo "media_turma" do objeto "turma"
    }
    return turma; // Retorna o ponteiro para o objeto "turma" (atualizado ou não)
}

Turma *criarTurma(char *codigo_turma, char *nome_disciplina, float media_turma)
{
    Turma *turma = (Turma *)malloc(sizeof(Turma)); // Aloca memória para um objeto "Turma"
    if (turma)                                     // Verifica se a alocação de memória foi bem-sucedida
    {
        strcpy(turma->codigo, codigo_turma);             // Copia a string "codigo_turma" para o campo "codigo" do objeto "turma"
        strcpy(turma->nome_disciplina, nome_disciplina); // Copia a string "nome_disciplina" para o campo "nome_disciplina" do objeto "turma"
        turma->professor = NULL;                         // Atribui o valor nulo ao campo "professor" do objeto "turma"
        turma->media_turma = media_turma;                // Atribui o valor "media_turma" ao campo "media_turma" do objeto "turma"
        turma->qtd_alunos = 0;                           // Atribui o valor zero ao campo "qtd_alunos" do objeto "turma"
    }
    else
    {
        perror("Não há memória disponível. Encerrando\n\n");
    }

    return turma; // Retorna o ponteiro para o objeto "turma" criado
}

Turma *adicionarAluno(Turma *turma, Aluno *aluno)
{
    if (turma && aluno) // Verifica se os ponteiros "turma" e "aluno" são válidos (não nulos)
    {
        turma->lista_alunos[turma->qtd_alunos] = aluno; // Adiciona o ponteiro do aluno à lista de alunos da turma, na posição "qtd_alunos"
        turma->qtd_alunos += 1;                         // Incrementa a quantidade de alunos na turma
    }
    return turma; // Retorna o ponteiro para a turma (atualizada ou não)
}

Turma *excluirAluno(Turma *turma, Aluno *aluno)
{
    if (turma && aluno) // Verifica se os ponteiros "turma" e "aluno" são válidos (não nulos)
    {
        int i = 0;
        for (i = 0; i < turma->qtd_alunos; i++) // Percorre a lista de alunos da turma
        {
            if (turma->lista_alunos[i] == aluno) // Verifica se o ponteiro de aluno é igual ao ponteiro encontrado na lista
            {
                turma->lista_alunos[i] = NULL; // Remove o aluno da lista, atribuindo NULL à posição correspondente
                turma->qtd_alunos -= 1;        // Decrementa a quantidade de alunos na turma
                return turma;                  // Retorna o ponteiro para a turma (atualizada)
            }
        }
    }
    return NULL; // Retorna NULL se a turma ou o aluno não forem válidos ou se o aluno não for encontrado na lista
}

void destruirTurma(Turma *turma)
{
    if (turma)       // Verifica se o ponteiro "turma" é válido (não nulo)
        free(turma); // Libera a memória alocada para o objeto "turma" utilizando a função "free"
}

Turma *adicionarProfessor(Turma *turma, Professor *professor)
{
    turma->professor = (Professor *)realloc(turma->professor, sizeof(Professor));
    if (turma && professor) // Verifica se os ponteiros "turma" e "professor" são válidos (não nulos)
    {
        turma->professor = professor; // Atribui o ponteiro do professor ao campo "professor" da turma
    }
    return turma; // Retorna o ponteiro para a turma (atualizada ou não)
}

/*

    PERISISTENCIA DE DADOS DOS ALUNOS

*/

// Função de encerramento para salvar os alunos em um arquivo binário
void salvarAlunosNoArquivo(Aluno *alunos[], int qtd_atual_aluno)
{
    FILE *arquivo = fopen("arquivos/alunos.bin", "wb"); // Abre o arquivo "alunos.bin" em modo de escrita binária
    if (arquivo == NULL)                       // Verifica se houve erro na abertura do arquivo
    {
        printf("Erro ao abrir o arquivo alunos.bin\n");
        exit(1);
    }

    for (int i = 0; i < qtd_atual_aluno; i++) // Percorre o array de alunos
    {
        fwrite(alunos[i], sizeof(Aluno), 1, arquivo);              // Escreve o conteúdo do aluno no arquivo
        fwrite(alunos[i]->endereco, sizeof(Endereco), 1, arquivo); // Escreve o conteúdo do endereço do aluno no arquivo
    }

    fclose(arquivo); // Fecha o arquivo
}

void recuperarAlunosDoArquivo(Aluno *alunos[], int *qtd_atual_aluno)
{
    FILE *arquivo = fopen("arquivos/alunos.bin", "rb"); // Abre o arquivo "alunos.bin" em modo de leitura binária
    if (arquivo == NULL)                       // Verifica se houve erro na abertura do arquivo
    {
        printf("Erro ao abrir o arquivo alunos.bin\n");
        exit(1);
    }

    fseek(arquivo, 0L, SEEK_END);                 // Posiciona o ponteiro de leitura no final do arquivo
    int tamanho = ftell(arquivo) / sizeof(Aluno); // Calcula o número de registros de alunos no arquivo
    rewind(arquivo);                              // Reposiciona o ponteiro de leitura no início do arquivo

    for (int i = 0; i < tamanho; i++) // Percorre o número de registros de alunos no arquivo
    {
        alunos[i] = malloc(sizeof(Aluno)); // Aloca memória para armazenar um aluno

        if (alunos[i] == NULL) // Verifica se houve erro na alocação de memória
        {
            printf("Erro na alocação de memória para o aluno\n");
            exit(1);
        }
        fread(alunos[i], sizeof(Aluno), 1, arquivo);    // Lê o conteúdo do registro de aluno no arquivo
        alunos[i]->endereco = malloc(sizeof(Endereco)); // Aloca memória para armazenar o endereço do aluno

        if (alunos[i]->endereco == NULL) // Verifica se houve erro na alocação de memória
        {
            printf("Erro na alocação de memória para o endereço do aluno\n");
            exit(1);
        }
        fread(alunos[i]->endereco, sizeof(Endereco), 1, arquivo); // Lê o conteúdo do registro de endereço do aluno no arquivo
    }
    *qtd_atual_aluno = tamanho; // Atualiza a quantidade atual de alunos
    fclose(arquivo);            // Fecha o arquivo
}
/*

    PERISISTENCIA DE DADOS DOS PROFESSORES

*/
// Segue a mesma ideia de salvarAlunosNoArquivo
void salvarProfessoresNoArquivo(Professor *professores[], int qtd_atual_professor)
{
    FILE *arquivo = fopen("arquivos/professores.bin", "wb");
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
// Segue a mesma ideia da recuperação de dados do aluno
void recuperarProfessoresDoArquivo(Professor *Professores[], int *qtd_atual_professor)
{
    FILE *arquivo = fopen("arquivos/professores.bin", "rb");
    if (arquivo == NULL)
    {
        printf("Erro ao abrir o arquivo professores.bin\n");
        exit(1);
    }

    fseek(arquivo, 0L, SEEK_END);
    int tamanho = ftell(arquivo) / sizeof(Professor);
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

/*


Persistencia de dados das turmas

*/
void salvarTurmasNoArquivo(Turma *turmas[], int qtd_atual_turma)
{
    FILE *arquivo = fopen("arquivos/turmas.bin", "wb");
    if (arquivo == NULL)
    {
        printf("Erro ao abrir o arquivo turmas.bin\n");
        exit(1);
    }

    for (int i = 0; i < qtd_atual_turma; i++)
    {
        fwrite(turmas[i], sizeof(Turma), 1, arquivo);

        if (turmas[i]->professor != NULL)
        {
            fwrite(turmas[i]->professor, sizeof(Professor), 1, arquivo);

            if (turmas[i]->professor->endereco != NULL)
            {
                fwrite(turmas[i]->professor->endereco, sizeof(Endereco), 1, arquivo);
            }
        }

        if (turmas[i]->qtd_alunos > 0)
        {
            for (int j = 0; j < turmas[i]->qtd_alunos; j++)
            {
                fwrite(turmas[i]->lista_alunos[j], sizeof(Aluno), 1, arquivo);

                if (turmas[i]->lista_alunos[j]->endereco != NULL)
                {
                    fwrite(turmas[i]->lista_alunos[j]->endereco, sizeof(Endereco), 1, arquivo);
                }
            }
        }
    }

    fclose(arquivo);
}

void recuperarTurmasDoArquivo(Turma *turmas[], int *qtd_atual_turma)
{
    FILE *arquivo = fopen("arquivos/turmas.bin", "rb");
    if (arquivo == NULL)
    {
        printf("Erro ao abrir o arquivo turmas.bin\n");
        exit(1);
    }

    fseek(arquivo, 0L, SEEK_END);
    int tamanho = ftell(arquivo) / sizeof(Turma);
    rewind(arquivo);

    for (int i = 0; i < tamanho; i++)
    {
        turmas[i] = malloc(sizeof(Turma));

        if (turmas[i] == NULL)
        {
            printf("Erro na alocação de memória para a turma\n");
            exit(1);
        }

        fread(turmas[i], sizeof(Turma), 1, arquivo);

        if (turmas[i]->professor != NULL)
        {
            turmas[i]->professor = malloc(sizeof(Professor));

            if (turmas[i]->professor == NULL)
            {
                printf("Erro na alocação de memória para o professor\n");
                exit(1);
            }

            fread(turmas[i]->professor, sizeof(Professor), 1, arquivo);

            turmas[i]->professor->endereco = malloc(sizeof(Endereco));

            if (turmas[i]->professor->endereco == NULL)
            {
                printf("Erro na alocação de memória para o endereço do professor\n");
                exit(1);
            }

            fread(turmas[i]->professor->endereco, sizeof(Endereco), 1, arquivo);
        }

        if (turmas[i]->qtd_alunos > 0)
        {
            for (int j = 0; j < turmas[i]->qtd_alunos; j++)
            {
                turmas[i]->lista_alunos[j] = malloc(sizeof(Aluno));

                if (turmas[i]->lista_alunos[j] == NULL)
                {
                    printf("Erro na alocação de memória para o aluno\n");
                    exit(1);
                }

                fread(turmas[i]->lista_alunos[j], sizeof(Aluno), 1, arquivo);

                turmas[i]->lista_alunos[j]->endereco = malloc(sizeof(Endereco));

                if (turmas[i]->lista_alunos[j]->endereco == NULL)
                {
                    printf("Erro na alocação de memória para o endereço do aluno\n");
                    exit(1);
                }

                fread(turmas[i]->lista_alunos[j]->endereco, sizeof(Endereco), 1, arquivo);
            }
        }
    }

    *qtd_atual_turma = tamanho;

    fclose(arquivo);
}
