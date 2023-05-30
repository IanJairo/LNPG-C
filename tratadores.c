// Inclusão de códigos e bibliotecas que serão utilizados aqui
#include "tratadores.h"
#include "menus.h"
#include <stdio.h>
#include "constantes.h"
#include <string.h>
#include <stdlib.h>

// Cria função para saber se o aluno já se encontra na turma
int alunoEstaNaTurma(Aluno *aluno, Turma *turma)
{
    for (int i = 0; i < turma->qtd_alunos; i++)
    {
        if (strcmp(aluno->matricula, turma->lista_alunos[i]->matricula) == 0) // Comparação entre a matrícula em sistema, e a que foi digitada
        {
            return 1; // Aluno está na turma
        }
    }
    return 0; // Aluno não está na turma
}

/*
        --------Cases do aluno----------
*/
void tratador_menu_aluno(Aluno **alunos, int *qtd_atual_aluno, Turma **turmas)
{
    int qtd_alunos;

    int opcao = menu_crud_aluno();
    Aluno *aluno = NULL;
    switch (opcao) // De acordo com a opção escolhida, teremos alguns casos:
    {
    case 1:
    {

        if (*qtd_atual_aluno >= MAX_ALUNO)
        {
            printf("Número máximo de alunos atingido\n"); // Mensagem impressa apenas quando o limite é atingido (definido em constantes.h)
        }
        else
        {
            aluno = construir_aluno();
            if (aluno) // Verifica se aluno é nulo
            {
                for (int i = 0; i < *qtd_atual_aluno; i++)
                {
                    if (strcmp(alunos[i]->matricula, aluno->matricula) == 0) // Compara as matrículas
                    {
                        printf("Já existe um aluno com a mesma matrícula\n");
                        free(aluno); // Libera o espaço na memória que aluno ocupava
                        return;
                    }
                }
                for (int i = 0; i < *qtd_atual_aluno; i++) // Compara os CPFs
                {
                    if (strcmp(alunos[i]->cpf, aluno->cpf) == 0)
                    {
                        printf("Já existe um aluno com o mesmo CPF\n");
                        free(aluno); // Libera o espaço na memória que aluno ocupava
                        return;
                    }
                }
                // Adição de aluno:
                alunos[*qtd_atual_aluno] = aluno;
                (*qtd_atual_aluno)++;
                printf("Aluno adicionado com sucesso\n");
            }
            else
            {
                printf("Falha ao criar aluno. Não há memória disponível.\n"); // Caso não der certo a inclusão
            }
        }
        break;
    }

    case 2:
    {
        int posicao = 0;
        aluno = buscar_aluno(alunos, &posicao);
        if (aluno) // Confere se aluno é nulo
        {
            imprimir_aluno(aluno); // imprimir_aluno recebe aluno como parametro
        }
        else
        {
            printf("Aluno não encontrado!!\n"); // Caso seja nulo, exibe essa mensagem
        }

        break;
    }
    case 3:
    {
        int posicao = 0;
        aluno = buscar_aluno(alunos, &posicao);
        if (aluno) // Confere se aluno é nulo
        {
            atualizar_aluno(aluno);                // atualizar_aluno recebe aluno como parametro
            printf("Atualizado com sucesso!\n\n"); // Mensagem mostrada quando a atualização acontece
        }
        else
        {
            printf("Aluno não encontrado!!\n"); // Quando seja nulo, exibe essa mensagem
        }
        break;
    }

    case 4:
    {
        int posicao = 0;
        aluno = buscar_aluno(alunos, &posicao);
        if (aluno) // Confere se aluno é nulo
        {
            // Verificar se o aluno está associado a alguma turma
            int associado = 0;
            for (int i = 0; i < MAX_TURMA; i++) // Para todo aluno encontrado, é somado +1 aluno.
            {
                if (turmas[i] && alunoEstaNaTurma(aluno, turmas[i]))
                {
                    associado = 1; // Se turma e aluno coexistirem, associado recebe 1.
                    break;
                }
            }
            /*
                    -------Tratamento de exceção, não pode excluir aluno associado a uma turma--------------
            */
            if (associado) // Confere se associado é nulo
            {
                printf("Não é possível excluir o aluno. Ele está associado a uma turma.\n"); // Caso não, temos um aluno associado a uma turma
            }
            else
            {
                destruirAluno(aluno);
                alunos[posicao] = NULL;
                printf("Aluno excluído!\n"); // Caso sim, chama a função de deleção de aluno, e o excluí
            }
        }
        else
        {
            printf("Aluno não encontrado!\n"); // Caso o aluno sequer tenha sido cadastrado, exibe essa mensagem
        }
        break;
    }
    default:

        printf("Retornando ao menu principal\n");
        break;
    }
}
/*
        --------------Função de Perscistir Aluno em arquivo----------------
*/
void persistir_alunos_em_arquivo(Aluno **alunos, int qtd_atual_aluno, const char *nome_arquivo)
{
    FILE *arquivo = fopen(nome_arquivo, "w");
    if (arquivo == NULL) // Confere se arquivo é nulo
    {
        printf("Erro ao abrir o arquivo.\n"); // Exibe essa mensagem, quando for nulo
        return;
    }

    for (int i = 0; i < qtd_atual_aluno; i++) // Para cada aluno cadastrado, seus dados são reescritos no .txt
    {
        Aluno *aluno = alunos[i];
        fprintf(arquivo, "Matrícula: %s\n", aluno->matricula);
        fprintf(arquivo, "CPF: %s\n", aluno->cpf);
        fprintf(arquivo, "Nome: %s\n", aluno->nome);
        // fprintf(arquivo, "Endereço: %s\n", aluno->endereco->logradouro);
        // fprintf(arquivo, "Cidade: %s\n", aluno->endereco->cidade);
        // fprintf(arquivo, "Estado: %s\n", aluno->endereco->estado);
        fprintf(arquivo, "\n");
    }

    fclose(arquivo);                                       // Função para fechar o arquivo
    printf("Dados dos alunos foram salvos no arquivo.\n"); // Mensagem exibida quando os dados são salvos
}

/*
        --------Cases do Professor----------
*/
void tratador_menu_professor(Professor **professores, int *qtd_atual_professor, Turma **turmas)
{
    int opcao = menu_crud_professor();
    Professor *professor = NULL;
    switch (opcao) // De acordo com a opção escolhida teremos alguns casos:
    {
    case 1:
        if (*qtd_atual_professor >= MAX_PROFESSOR)
        {
            printf("Número máximo de professores atingido\n"); // Limite definido no constantes.h foi atingido
        }
        else
        {
            professor = construir_professor();
            if (professor) // Confere se professor é nulo
            {
                for (int i = 0; i < *qtd_atual_professor; i++) // Para cada professor incluso atribui a qtd atual +1
                {                                              //---Tratamento de exeções, não cadastrar 2 professores com mesmo cpf ou matrícula
                    if (strcmp(professores[i]->matricula, professor->matricula) == 0 ||
                        strcmp(professores[i]->cpf, professor->cpf) == 0) // Confere matrículas, CPF no sistema e confere com o que foi digitado
                    {
                        printf("Ja existe um professor com a mesma matricula ou CPF\n"); // Emmite essa mensagem quando a condição é obedecida
                        free(professor);                                                 // Libera o espaço de professor na memória
                        return;
                    }
                }
                professores[*qtd_atual_professor] = professor;
                (*qtd_atual_professor)++; // Caso nulo, é incrementado mais um professor a qtd atual.
            }
            else
            {
                printf("Falha ao criar professor. Não há memória disponível.\n"); // Caso não tenha espaço na memória, ou ocorra algum erro
            }
        }
        break;
    case 2:
    {
        int posicao = 0;
        professor = buscar_professor(professores, &posicao);
        if (professor) // Confere se professor é nulo
        {
            imprimir_professor(professor); // Chama a função que recebe como parâmetro professor
        }
        else
        {
            printf("Professor não encontrado!\n"); // Caso seja nulo, exibe essa mensagem
        }
    }
    break;
    case 3:
    {
        int posicao = 0;
        professor = buscar_professor(professores, &posicao);
        if (professor) // Confere se professor é nulo
        {
            atualizar_professor(professor);                  // Chama a função para atualizar o professor, e passa o valor de professor como parametro
            printf("Professor atualizado com sucesso!\n\n"); // Exibe essa mensagem com a execução da função
        }
        else
        {
            printf("Professor não encontrado!\n"); // Caso seja nulo, exibe essa mensagem
        }
    }
    break;
    case 4:
    {
        int posicao = 0;
        professor = buscar_professor(professores, &posicao);
        if (professor)
        {
            // Verifica se o professor está associado a alguma turma
            int associado = 0;
            for (int i = 0; i < MAX_TURMA; i++) // Para todo professor encontrado é somado +1
            {
                if (turmas[i] && strcmp(turmas[i]->professor->matricula, professor->matricula) == 0)
                {
                    associado = 1; // Turma e aluno coexistem e estão associados
                    break;
                }
            }
            /*
                -------Tratamento de Exeções, não é possível excluir professor associado a turma
            */
            if (associado) // Confere se associado é nulo
            {
                printf("Nao e possivel excluir o professor. Ele esta associado a uma turma.\n");
            } // Caso não, não permite a exclusão e mostra essa mensagem
            else
            {
                destruirProfessor(professor);
                professores[posicao] = NULL;
                (*qtd_atual_professor)--;
                printf("Professor excluído!\n"); // Caso sim, chama função de deleção do professor
            }
        }
        else
        {
            printf("Professor não encontrado!\n"); // Caso o professor sequer tenha sido cadastrado
        }
    }
    break;
    default:
        printf("Retornando ao menu principal\n"); // Caso nenhum dos cases seja correspondido
        break;
    }
}

/*
    --------Cases da turma--------
*/
void tratador_menu_turma(Turma **turmas, Aluno **alunos, Professor **professores, int *qtd_atual_turma)
{
    int opcao = menu_crud_turma();
    Turma *turma = NULL;
    Aluno *aluno = NULL;
    Professor *professor = NULL;

    switch (opcao) // De acordo com a opção escolhida temos alguns casos:
    {
    case 1:
        if (*qtd_atual_turma >= MAX_TURMA)
        {
            printf("Número máximo de turmas atingido\n"); // Limite definido no constantes.h foi atingido
        }
        else
        {
            turma = construir_turma();
            if (turma) // Confere se turma é nulo
            {
                for (int i = 0; i < *qtd_atual_turma; i++)             // Para cada turma inclusa atribui a qtd atual +1
                {                                                      // Tratamento de excessões: não permitir o cadastro de 2 turmas iguais
                    if (strcmp(turmas[i]->codigo, turma->codigo) == 0) // Confere código da turma
                    {
                        printf("Ja existe uma turma com o mesmo codigo\n"); // Retorna caso já exista o código
                        free(turma);                                        // Libera espaço de turma na memória
                        return;
                    }
                }
                turmas[*qtd_atual_turma] = turma;
                (*qtd_atual_turma)++; // Caso nulo, mais uma turma é incrementada a qtd atual
            }
            else
            {
                printf("Falha ao criar turma. Nao ha memoria disponivel.\n"); //  Caso não tenha espaço na memória, ou ocorra algum erro
            }
        }
        break;
    case 2:
    {
        int posicao = 0;
        turma = buscar_turma(turmas, &posicao);
        if (turma) // Confere se turma é nulo
        {
            imprimir_turma(turma); // Chama a função que recebe como parêmetro turma
        }
        else
        {
            printf("Turma não encontrada!!\n"); // Caso seja nulo, exibe essa mensagem
        }
        break;
    }
    case 3:
    {
        int posicao = 0;
        turma = buscar_turma(turmas, &posicao);
        if (turma) // Confere se turma é nulo
        {
            atualizar_turma(turma); // Chama a função para atualizar a turma, e passa o valor de turma como parametro
            printf("Turma atualizada com sucesso!\n");
        }
        else
        {
            printf("Turma não encontrada!!\n"); // Caso seja nulo, exibe essa mensagem
        }
        break;
    }
    case 4:
    {
        int posicao = 0;
        turma = buscar_turma(turmas, &posicao);
        if (turma) // Confere se turma é nulo
        {          // Caso sim, chama a função para deleção da turma
            destruirTurma(turma);
            turmas[posicao] = NULL;
            *qtd_atual_turma = *qtd_atual_turma - 1; // Subtrai 1 da qtd atual
            printf("Turma destruida\n");             // Exibe essa mensagem
        }
        else
        {
            printf("Turma não encontrada!!\n"); // Caso a turma sequer tenha sido cadastrada
        }
        break;
    }
    case 5:
    {
        int posicao = 0;
        turma = buscar_turma(turmas, &posicao);
        if (turma) // Confere se turma é nulo
        {
            posicao = 0;
            aluno = buscar_aluno(alunos, &posicao); // Chama a função buscar_aluno para encontrar um aluno na turma

            if (aluno) // Confere se aluno é nulo
            {
                adicionarAluno(turma, aluno);                    // Chama a função para adicionar aluno, dentro da turma
                printf("O cadastro do aluno foi um sucesso!\n"); // Exibe essa mensagem, quando tem sucesso
            }
            else
            {
                printf("Nao foi encontrado nenhum aluno!!\n"); // Caso não tenha o aluno na turma
            }
        }
        else
        {
            printf("Não foi encontrada nenhuma turma com esse código !!\n"); // Caso sequer o código exista
        }
        break;
    }
    case 6:
    {

        int posicao = 0;
        turma = buscar_turma(turmas, &posicao);

        // Confere se a turma é nulo
        if (turma)
        {
            // Verifica se a turma possui alunos
            if (turma->lista_alunos)
            {
                // Caso sim, busca o aluno
                posicao = 0;
                aluno = buscar_aluno(turma->lista_alunos, &posicao);

                // Verifica se o aluno é nulo
                if (aluno)
                {
                    // Chama função para exclusão do aluno da turma
                    excluirAluno(turma, aluno);
                    printf("Aluno removido com sucesso!\n");
                }
                else
                {
                    printf("Aluno não encontrado!!\n"); // Caso o aluno digitado não seja encontrado
                }
            }
            else
            {
                printf("Turma não possui alunos cadastrados!!\n"); // Caso sequer a turma tenha alunos
            }
        }
        break;
    }
    case 7:
    {
        int posicao = 0;
        turma = buscar_turma(turmas, &posicao);
        if (turma) // Confere se turma é nulo
        {
            // Verifica se a turma possuí professores
            posicao = 0;
            professor = buscar_professor(professores, &posicao);

            if (professor) // Confere se o professor é nulo
            {
                adicionarProfessor(turma, professor);                  // Chama a função para adicionar professor, na turma
                printf("Professor adicionado a turma com sucesso!\n"); // Exibe essa mensagem
            }
            else
            {
                printf("Professor não encontrado no sistema!!\n"); // Caso não haja o professor dentro da turma
            }
        }
        else
        {
            printf("Turma não encontrada no sistema!!\n"); // Caso sequer a turma esteja cadastrada
        }
        break;
    }
    case 8:
    {
        int posicao = 0;
        turma = buscar_turma(turmas, &posicao);
        if (turma) // Confere se turma é nulo
        {
            if (turma->professor) // Confere se professor em turma é nulo
            {
                turma->professor = NULL;
                printf("Professor removido com sucesso!\n"); // Remove professor passando seu valor para nulo
            }
            else
            {
                printf("Turma não possui professor cadastrado!!\n"); // Caso não possua professor cadastrado
            }
        }
        else
        {
            printf("Turma nao encontrada no sistema!!\n"); // Caso sequer tenha turma no sistema
        }
        break;
    }
    default:
        printf("Retornando ao menu principal\n"); // Caso nenhum dos cases seja correspondido
        break;
    }
}
/*   Armazenamento do Endereço   */
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

/*   Armazenamento do Aluno   */
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

    // return criarAluno(aluno.matricula, aluno.cpf, aluno.nome);
    // return criarAluno(aluno.matricula, aluno.cpf, aluno.nome, aluno.endereco);
}
/*   Atualização do Aluno   */
Aluno *atualizar_aluno(Aluno *aluno)
{
    Aluno novo_aluno;
    printf("CPF\t> ");
    fgets(novo_aluno.cpf, 12, stdin);
    printf("Nome\t> ");
    fgets(novo_aluno.nome, 49, stdin);
    // novo_aluno.endereco = construir_endereco();
    return atualizarAluno(aluno, &novo_aluno);
}
/*   Buscar o Aluno   */
Aluno *buscar_aluno(Aluno **alunos, int *posicao)
{
    char matricula[50];
    printf("Matricula > \n"); // Adiciona a quebra de linha
    fflush(stdout);           // Limpa o buffer de saída antes da leitura
    fgets(matricula, 49, stdin);
    Aluno *resultado = NULL;
    int pos_resultado = -1;
    for (int i = 0; i < MAX_ALUNO; i++)
    {
        // Vamos testar se o aluno existe e se a matricula é a buscada
        // strcmp compara strings. Se for 0 indica que são iguais
        // Testa se o aluno existe e se a matricula é igual a buscada
        if (alunos[i] && !strcmp(matricula, alunos[i]->matricula))
        {
            resultado = alunos[i];
            break;
        }
    }
    *posicao = pos_resultado;
    return resultado;
}
/*   Print do Aluno   */
void imprimir_aluno(Aluno *aluno)
{
    printf("Matrícula: %s\n", aluno->matricula);
    printf("Nome: %s\n", aluno->nome);
    printf("CPF: %s\n", aluno->cpf);
    imprimir_endereco(aluno->endereco);
}
/*   Print  do Endereço   */
void imprimir_endereco(Endereco *endereco)
{
    printf("Logradouro: %s\n", endereco->logradouro);
    printf("Número: %s\n", endereco->numero);
    printf("Bairro: %s\n", endereco->bairro);
    printf("Cidade: %s\n", endereco->cidade);
    printf("Estado: %s\n", endereco->estado);
}

/*   Armazenamento do Professor   */

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
/*   Atualização do Professor   */
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
/*   Buscar o Professor   */
Professor *buscar_professor(Professor **professores, int *posicao)
{
    char matricula[50];
    printf("Matricula do professor> ");
    fgets(matricula, 49, stdin);
    Professor *resultado = NULL;
    int pos_resultado = -1;
    for (int i = 0; i < MAX_PROFESSOR; i++)
    { // Testa se o professor existe e se tem a matrícula buscada
        if (professores[i] && !strcmp(matricula, professores[i]->matricula))
        {
            resultado = professores[i];
            break;
        }
    }
    *posicao = pos_resultado;
    return resultado;
}
/*   Print do Professor   */
void imprimir_professor(Professor *professor)
{
    printf("Matricula do professor: %s", professor->matricula);
    printf("Nome do professor: %s", professor->nome);
    printf("CPF do professor: %s", professor->cpf);
    imprimir_endereco(professor->endereco);
}

/*   Armazenamento da Turma   */
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
/*   Buscar a Turma   */
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
/*   Atualizar a Turma   */
Turma *atualizar_turma(Turma *turma)
{
    Turma nova_turma;
    printf("Nome da Disciplina\t> ");
    fgets(nova_turma.nome_disciplina, 12, stdin);
    printf("Media\t> ");
    scanf("%f", &nova_turma.media_turma);
    return atualizarTurma(turma, &nova_turma);
}
/*   Print da Turma   */
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

/*   Armazenamento das Estatísticas   */
void tratador_menu_estatistica(Turma **turmas, Professor **professores)
{
    int opcao = menu_estatistica();
    switch (opcao) // Para cada opção escolhida, temos casos:
    {
    case 1:
        imprimir_nomes_professores(professores); // Imprimir nomes dos professores recebe professores
        break;
    case 2:
        imprimir_professores_sem_turma(professores, turmas); // Imprimir nomes dos professores sem trumas recebe professores e turmas
        break;
    case 3:
        imprimir_media_turmas(turmas); // Imprimir media das turmas recebe media
        break;
    case 4:
        break;
    }
}
/* Define a função IMPRIMIR_NOMES_PROFESSORES */
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
/*  Define a função IMPRIMIR_PROFESSORES_SEM_TURMA  */
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
/* Define a função IMPRIMIR_MEDIA_TURMAS */
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
        ++qtd_turmas;
        soma += turmas[i]->media_turma;
    }
    printf("Nota media de todas as turmas cadastradas: %.2f\n\n", soma / qtd_turmas);
}
