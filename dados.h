#ifndef _DADOS_H_ // Verifica se _DADOS_H_
#define _DADOS_H_ // Define _DADOS_H_

typedef struct // Criação de um novo tipo de dados e armazenamento em uma STRUCT
{
    char logradouro[50]; // Definindo uma matriz de tamanho máximo 50 caracteres
    char bairro[50];     // Definindo uma matriz de tamanho máximo 50 caracteres
    char cidade[50];     // Definindo uma matriz de tamanho máximo 50 caracteres
    char estado[10];     // Definindo uma matriz de tamanho máximo 10 caracteres
    char numero[10];     // Definindo uma matriz de tamanho máximo 10 caracteres
} Endereco;
/*
    Fazemos a mesma coisa para as outras 3 structs a seguir
*/
typedef struct
{
    char matricula[10];
    char cpf[12];
    char nome[50];
    Endereco *endereco;
} Aluno;

typedef struct
{
    char matricula[10];
    char cpf[13];
    char nome[50];
    Endereco *endereco;
} Professor;
typedef struct
{
    char codigo[50];
    char nome_disciplina[50];
    Professor *professor;
    Aluno *lista_alunos[100];
    float media_turma;
    int qtd_alunos;
} Turma;

Endereco *criarEndereco(char *logradouro,
                        char *bairro,
                        char *cidade,
                        char *estado,
                        char *numero);

/*   CRUD ALUNOS    */
Aluno *criarAluno(char *matricula,
                  char *cpf,
                  char *nome,
                  Endereco *end);

Aluno *atualizarAluno(Aluno *aluno, Aluno *novo_aluno);

void destruirAluno(Aluno *aluno);
void destruirEndereco(Endereco *);

/*   CRUD PROFESSORES    */

Professor *criarProfessor(char *matricula, char *cpf, char *nome, Endereco *end);

Professor *atualizarProfessor(Professor *professor, Professor *novo_professor);

void destruirProfessor(Professor *professor);

/*   CRUD TURMAS    */
Turma *atualizarTurma(Turma *turma, Turma *nova_turma);

Turma *criarTurma(char *codigo_turma,
                  char *nome_disciplina,
                  float media_turma);

Turma *adicionarAluno(Turma *turma, Aluno *aluno);
Turma *excluirAluno(Turma *turma, Aluno *aluno);

void destruirTurma(Turma *turma);

Turma *adicionarProfessor(Turma *turma, Professor *professor);

/*



Persistencia de dados

*/

// ALUNOS
void recuperarAlunosDoArquivo(Aluno *alunos[], int *qtd_atual_aluno);
void salvarAlunosNoArquivo(Aluno *alunos[], int qtd_atual_aluno);

#endif // Fim do bloco condicional
