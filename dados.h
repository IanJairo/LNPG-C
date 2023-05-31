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
//Cria um novo objeto "Aluno" com os dados fornecidos e retorna um ponteiro para o objeto criado.
Aluno *criarAluno(char *matricula,
                  char *cpf,
                  char *nome,
                  Endereco *end);

/*Atualiza as informações de um objeto "Aluno" existente com os dados de outro objeto "Aluno"
 e retorna um ponteiro para o "aluno" atualizado.*/
Aluno *atualizarAluno(Aluno *aluno, Aluno *novo_aluno);

//Libera a memória alocada para um objeto "Aluno" e realiza qualquer limpeza necessária.
void destruirAluno(Aluno *aluno);
//Libera a memória alocada para um objeto "Endereco" e realiza qualquer limpeza necessária.
void destruirEndereco(Endereco *);

/*   CRUD PROFESSORES    */

//Cria um novo objeto "Professor" com os dados fornecidos e retorna um ponteiro para o objeto criado.
Professor *criarProfessor(char *matricula, char *cpf, char *nome, Endereco *end);
/*Atualiza as informações de um objeto "Professor" existente com os dados de outro objeto "Professor" 
e retorna um ponteiro para o "professor" atualizado.*/
Professor *atualizarProfessor(Professor *professor, Professor *novo_professor);
//Libera a memória alocada para um objeto "Professor" e realiza qualquer limpeza necessária.
void destruirProfessor(Professor *professor);

/*   CRUD TURMAS    */

//Atualiza as informações de uma turma existente com os dados de outra turma e retorna um ponteiro para a turma atualizada.
Turma *atualizarTurma(Turma *turma, Turma *nova_turma);
//Cria uma nova turma com os dados fornecidos e retorna um ponteiro para a turma criada.
Turma *criarTurma(char *codigo_turma,
                  char *nome_disciplina,
                  float media_turma);
//Adiciona um aluno à turma especificada e retorna um ponteiro para a turma atualizada.
Turma *adicionarAluno(Turma *turma, Aluno *aluno);
//Remove um aluno da turma especificada e retorna um ponteiro para a turma atualizada.
Turma *excluirAluno(Turma *turma, Aluno *aluno);
//Libera a memória alocada para uma turma e realiza qualquer limpeza necessária.
void destruirTurma(Turma *turma);
//Adiciona um professor à turma especificada e retorna um ponteiro para a turma atualizada.
Turma *adicionarProfessor(Turma *turma, Professor *professor);

/*
Persistencia de dados
*/

// ALUNOS
/*Recupera os dados dos alunos armazenados em um arquivo e os armazena 
em um array de ponteiros para objetos "Aluno". Atualiza a quantidade atual de alunos.*/
void recuperarAlunosDoArquivo(Aluno *alunos[], int *qtd_atual_aluno);
/*Salva os dados dos alunos contidos em um array de ponteiros para objetos 
"Aluno" em um arquivo. Recebe a quantidade atual de alunos como parâmetro.*/
void salvarAlunosNoArquivo(Aluno *alunos[], int qtd_atual_aluno);

// PROFESSORES
/*Recupera os dados dos professores armazenados em um arquivo e os armazena em um array 
de ponteiros para objetos "Professor". Atualiza a quantidade atual de professores.*/
void recuperarProfessoresDoArquivo(Professor *professores[], int *qtd_atual_professor);
/* Salva os dados dos professores contidos em um array de ponteiros para objetos "Professor"
em um arquivo. Recebe a quantidade atual de professores como parâmetro.*/
void salvarProfessoresNoArquivo(Professor *professores[], int qtd_atual_professor);

#endif // Fim do bloco condicional
