// Inclusão de códigos e bibliotecas que serão utilizados aqui
#include "tratadores.h"
#include "menus.h"
#include <stdio.h>
#include "constantes.h"
#include <string.h>
#include <stdlib.h>

int alunoEstaNaTurma(Aluno *aluno, Turma *turma) // Validação: Aluno participa de uma turma
{
    for (int i = 0; i < turma->qtd_alunos; i++) // Percorre cada aluno na turma
    {
        if (strcmp(aluno->matricula, turma->lista_alunos[i]->matricula) == 0) // Veerifica se a matricula do aluno está na lista de alunos matriculados
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

    int opcao = menu_crud_aluno(); // Pega o retorno da função CRUD aluno
    Aluno *aluno = NULL;
    switch (opcao) // Switch de escolhas do usuário no menu CRUD
    {
    case 1: // Adicionar aluno
    {

        if (*qtd_atual_aluno >= MAX_ALUNO) // Confere se a qtd atual de alunos é maior que o máximo de alunos
        {
            printf("Número máximo de alunos atingido\n");
        }
        else
        {
            aluno = construir_aluno(); // Construir aluno recebe aluno como parâmetro
            if (aluno) // Verifica se aluno é nulo
            {
                for (int i = 0; i < *qtd_atual_aluno; i++) // Validação de exceção: não permitir o cadastro de 2 alunos com mesmo cpf ou matrícula
                {
                    if (strcmp(alunos[i]->matricula, aluno->matricula) == 0 || strcmp(alunos[i]->cpf, aluno->cpf)) // Compara as matrículas e os CPFs
                    {
                        printf("Já existe um aluno com a mesma matrícula\n");
                        free(aluno); // Libera o espaço na memória que aluno ocupava
                        return;
                    }
                }
                // Adição de aluno:
                alunos[*qtd_atual_aluno] = aluno; // Alunos recebe aluno
                (*qtd_atual_aluno)++;            // Incrementa mais um aluno a qtd atual
                printf("Aluno adicionado com sucesso\n");
            }
            else
            {
                printf("Falha ao criar aluno. Não há memória disponível.\n"); // Caso não der certo a inclusão
            }
        }
        break;
    }

    case 2: // Buscar aluno
    {
        int posicao = 0; // Contador de posições em turma
        aluno = buscar_aluno(alunos, &posicao); // Buscar aluno recebe aluno e posição como parâmetro
        if (aluno) // Confere se aluno é nulo
        {
            imprimir_aluno(aluno);
        }
        else
        {
            printf("Aluno não encontrado!!\n");
        }

        break;
    }
    case 3: // Atualizar aluno
    {
        int posicao = 0; 
        aluno = buscar_aluno(alunos, &posicao); // Busca aluno e a posição dele
        if (aluno) 
        {
            atualizar_aluno(aluno);
            printf("Atualizado com sucesso!\n\n");
        }
        else
        {
            printf("Aluno não encontrado!!\n");
        }
        break;
    }

    case 4: // Excluir aluno
    {
        int posicao = 0;
        aluno = buscar_aluno(alunos, &posicao); // Busca aluno e a posição dele
        if (aluno)
        {
            // Verificar se o aluno está associado a alguma turma
            int associado = 0; // Validação de associado
            for (int i = 0; i < MAX_TURMA; i++) // Percorre todo o vetor de turmas
            {
                if (turmas[i] && alunoEstaNaTurma(aluno, turmas[i])) // Confere se aluno está na turma
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
                printf("Não é possível excluir o aluno. Ele está associado a uma turma.\n");
            }
            else
            {
                destruirAluno(aluno); 
                alunos[posicao] = NULL; // Libera a variavél possição instanciada no início
                printf("Aluno excluído!\n");
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
    FILE *arquivo = fopen(nome_arquivo, "w"); // Abre o arquivo para escrita (w)
    if (arquivo == NULL) // Confere se arquivo é nulo
    {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    for (int i = 0; i < qtd_atual_aluno; i++) // Para cada aluno cadastrado, seus dados são reescritos no .txt
    {
        Aluno *aluno = alunos[i];
        fprintf(arquivo, "Matrícula: %s\n", aluno->matricula); // Escreve no arquivo cada dado como string
        fprintf(arquivo, "CPF: %s\n", aluno->cpf); 
        fprintf(arquivo, "Nome: %s\n", aluno->nome);
        // fprintf(arquivo, "Endereço: %s\n", aluno->endereco->logradouro);
        // fprintf(arquivo, "Cidade: %s\n", aluno->endereco->cidade);
        // fprintf(arquivo, "Estado: %s\n", aluno->endereco->estado);
        fprintf(arquivo, "\n");
    }

    fclose(arquivo);  // Fecha o arquivo
    printf("Dados dos alunos foram salvos no arquivo.\n");
}

/*
        --------Cases do Professor----------
*/
void tratador_menu_professor(Professor **professores, int *qtd_atual_professor, Turma **turmas)
{
    int opcao = menu_crud_professor(); // Recebe o retorno da função CRUD professor
    Professor *professor = NULL;
    switch (opcao) // Switch de escolhas do usuário no menu CRUD
    {
    case 1: // Adicionar Professor
        if (*qtd_atual_professor >= MAX_PROFESSOR) // Verifica se o limite foi atingido
        {
            printf("Número máximo de professores atingido\n"); 
        }
        else
        {
            professor = construir_professor(); // Constroi professor
            if (professor)
            {
                for (int i = 0; i < *qtd_atual_professor; i++) // percorre cada professor cadastrado
                {                                              //---Tratamento de exeções, não cadastrar 2 professores com mesmo cpf ou matrícula
                    if (strcmp(professores[i]->matricula, professor->matricula) == 0 ||
                        strcmp(professores[i]->cpf, professor->cpf) == 0) // Confere matrículas, CPF no sistema e confere com o que foi digitado
                    {
                        printf("Ja existe um professor com a mesma matricula ou CPF\n"); 
                        free(professor);
                        return;
                    }
                } 
                professores[*qtd_atual_professor] = professor; // Se não for repetido, adiciona o professor
                (*qtd_atual_professor)++;
            }
            else
            {
                printf("Falha ao criar professor. Não há memória disponível.\n");
            }
        }
        break;
    case 2: // Buscar professor
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
    case 3: // Atualizar professor
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
    case 4: // Excluir professor
    {
        int posicao = 0;
        professor = buscar_professor(professores, &posicao);
        if (professor)
        {
            // Verifica se o professor está associado a alguma turma
            int associado = 0;
            for (int i = 0; i < MAX_TURMA; i++) // Percorre todos os professores cadastrados
            {
                if (turmas[i] && strcmp(turmas[i]->professor->matricula, professor->matricula) == 0) // Verifica se a matrícula do professor esta cadastrada em alguma turma
                {
                    associado = 1;
                    break;
                }
            }
            /*
                -------Tratamento de Exeções, não é possível excluir professor associado a turma
            */
            if (associado) // Confere se o professor está associado, se sim, não permite a exclusão
            {
                printf("Nao e possivel excluir o professor. Ele esta associado a uma turma.\n");
            }
            else
            {
                destruirProfessor(professor); // Se não, exclui professor, libera espaço alocado e decrementa contador
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

/*
    --------Cases da turma--------
*/
void tratador_menu_turma(Turma **turmas, Aluno **alunos, Professor **professores, int *qtd_atual_turma)
{
    int opcao = menu_crud_turma(); // Recebe o retorno da função CRUD turma
    Turma *turma = NULL; // Instancia turma e aluno para associação
    Aluno *aluno = NULL;
    Professor *professor = NULL;

    switch (opcao) // Switch de opções do usuário no menu CRUD
    {
    case 1: // Adicionar turma
        if (*qtd_atual_turma >= MAX_TURMA) // verifica se o limite foi atingido
        {
            printf("Número máximo de turmas atingido\n");
        }
        else
        {
            turma = construir_turma();
            if (turma)
            {
                for (int i = 0; i < *qtd_atual_turma; i++)   // Percorre todas as turmas cadastradas
                {                                                      // Tratamento de excessões: não permitir o cadastro de 2 turmas iguais
                    if (strcmp(turmas[i]->codigo, turma->codigo) == 0) // Confere código da turma com o que foi digitado, se ja existe em turmas
                    {
                        printf("Ja existe uma turma com o mesmo codigo\n");
                        free(turma);                                        
                        return;
                    }
                }
                turmas[*qtd_atual_turma] = turma; // Incrementa turma
                (*qtd_atual_turma)++; 
            }
            else
            {
                printf("Falha ao criar turma. Nao ha memoria disponivel.\n");
            }
        }
        break;
    case 2: // Buscar turma
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
    case 3: // Atualizar turma
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
    case 4: // Excluir turma
    {
        int posicao = 0;
        turma = buscar_turma(turmas, &posicao); // Busca turma e a posição dela
        if (turma) 
        {          // Caso encontre
            destruirTurma(turma);
            turmas[posicao] = NULL; // Libera a posição no vetor
            *qtd_atual_turma = *qtd_atual_turma - 1; // Subtrai 1 da qtd atual
            printf("Turma destruida\n");
        }
        else
        {
            printf("Turma não encontrada!!\n");
        }
        break;
    }
    case 5: // Adicionar aluno na turma
    {
        int posicao = 0;
        turma = buscar_turma(turmas, &posicao); // Busca turma e a posição
        if (turma) 
        {
            posicao = 0;
            aluno = buscar_aluno(alunos, &posicao); // Chama a função buscar_aluno para encontrar os dados do aluno

            if (aluno) // Confere se encontrou aluno
            {
                adicionarAluno(turma, aluno);                    // Chama a função para adicionar aluno, dentro da turma
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
    case 6: // Excluir aluno da turma
    {

        int posicao = 0;
        turma = buscar_turma(turmas, &posicao); // busca turma e a posição

        if (turma)
        {
            // Verifica se a turma possui alunos
            if (turma->lista_alunos)
            {
                // Caso sim, busca o aluno
                posicao = 0;
                aluno = buscar_aluno(turma->lista_alunos, &posicao); // Busca aluno dentro da lista alunos da turma

                if (aluno)
                {
                    // Se encontrou o aluno, exclui ele da turma
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
                printf("Turma não possui alunos cadastrados!!\n"); // Caso sequer a turma tenha alunos  
            }
        }
        break;
    }
    case 7: // Adicionar professor na turma
    {
        int posicao = 0;
        turma = buscar_turma(turmas, &posicao); // Busca turma e a posição
        if (turma) 
        {
            // Verifica se a turma possuí professores
            posicao = 0;
            professor = buscar_professor(professores, &posicao); // Busca professor dentro da lista de professores

            if (professor) // Confere se o professor é nulo
            {
                adicionarProfessor(turma, professor);                  // Chama a função para adicionar professor, na turma
                printf("Professor adicionado a turma com sucesso!\n");
            }
            else
            {
                printf("Professor não encontrado no sistema!!\n");
            }
        }
        else
        {
            printf("Turma não encontrada no sistema!!\n"); // Caso sequer a turma esteja cadastrada
        }
        break;
    }
    case 8: // Remover professor da turma
    {
        int posicao = 0;
        turma = buscar_turma(turmas, &posicao); // Busca turma e a posição
        if (turma) 
        {
            if (turma->professor) // Confere se a turma tem professor
            {
                turma->professor = NULL;
                printf("Professor removido com sucesso!\n"); // Remove professor passando seu valor para nulo
            }
            else
            {
                printf("Turma não possui professor cadastrado!!\n");
            }
        }
        else
        {
            printf("Turma nao encontrada no sistema!!\n"); // Caso sequer tenha turma no sistema
        }
        break;
    }
    default:  // Caso nenhum dos cases seja correspondido
        printf("Retornando ao menu principal\n"); 
        break;
    }

}
/*   Armazenamento do Endereço   */
Endereco *construir_endereco()
{
    Endereco endereco;  // Prepara os dados de endereço do aluno, cada propriedade em uma linha

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

    return criarEndereco(endereco.logradouro, endereco.bairro, endereco.cidade, endereco.estado, endereco.numero); // retorna o endereço para ser salvo no arquivo
}

/*   Armazenamento do Aluno   */
Aluno *construir_aluno()
{
    Aluno aluno;  // Prepara os dados do aluno, cada propriedade em uma linha
    printf("Matricula\t> ");
    fgets(aluno.matricula, 9, stdin);
    printf("CPF\t> ");
    fgets(aluno.cpf, 12, stdin);
    printf("Nome\t> ");
    fgets(aluno.nome, 49, stdin);
    aluno.endereco = construir_endereco();

    return criarAluno(aluno.matricula, aluno.cpf, aluno.nome, aluno.endereco); // Retorna o aluno para ser salvo no arquivo

    // return criarAluno(aluno.matricula, aluno.cpf, aluno.nome);
    // return criarAluno(aluno.matricula, aluno.cpf, aluno.nome, aluno.endereco);
}

/*   Atualização do Aluno   */
Aluno *atualizar_aluno(Aluno *aluno)
{
    Aluno novo_aluno;  // Atualiza os dados do aluno, retornando um novo aluno com os dados atualizados para ser escrito sobre o anterior
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
    fgets(matricula, 49, stdin); // Lê a matrícula digitada pelo usuário
    Aluno *resultado = NULL; // Instancia resultado e posição
    int pos_resultado = -1;
    for (int i = 0; i < MAX_ALUNO; i++) // Percorre todos os alunos cadastrados
    {
        // strcmp compara strings. Se for 0 indica que são iguais
        if (alunos[i] && !strcmp(matricula, alunos[i]->matricula)) // Confere se a matricula digitada confere com a de algum aluno registrado
        {
            resultado = alunos[i]; // Se sim, resultado recebe o aluno
            break;
        }
    }
    *posicao = pos_resultado; // Posição recebe a posição do aluno por ponteiro
    return resultado; // Retorna o aluno encontrado
}
/*   Print do Aluno   */
void imprimir_aluno(Aluno *aluno) // Printa os dados do aluno
{
    printf("Matrícula: %s\n", aluno->matricula);  // Printa cada dado
    printf("Nome: %s\n", aluno->nome);
    printf("CPF: %s\n", aluno->cpf);
    imprimir_endereco(aluno->endereco); // Chama a função para printar endereço, já que é uma struct a parte
}
/*   Print  do Endereço   */
void imprimir_endereco(Endereco *endereco) // Imprime os dados do endereço
{
    printf("Logradouro: %s\n", endereco->logradouro); // Printa cada dado
    printf("Número: %s\n", endereco->numero);
    printf("Bairro: %s\n", endereco->bairro);
    printf("Cidade: %s\n", endereco->cidade);
    printf("Estado: %s\n", endereco->estado);
}

/*   Armazenamento do Professor   */

Professor *construir_professor()
{
    Professor *professor = (Professor *)malloc(sizeof(Professor)); // Aloca espaço na memória para o professor
    if (professor)
    {
        printf("Matricula do professor\t>"); // Pede ao usuário os dados do professor e armazena na struct professor
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
    return professor; // Retorna o professor para ser salvo no arquivo
}
/*   Atualização do Professor   */
Professor *atualizar_professor(Professor *professor) // Atualiza os dados do professor, retornando um novo professor com os dados atualizados para ser escrito sobre o anterior
{
    Professor novo_professor; // Cria uma struct novo professor
    printf("CPF\t> ");
    fgets(novo_professor.cpf, 12, stdin);
    printf("Nome\t> ");
    fgets(novo_professor.nome, 49, stdin);
    novo_professor.endereco = construir_endereco();
    return atualizarProfessor(professor, &novo_professor); // Retorna professor com os dados de novo professor
}
/*   Buscar o Professor   */
Professor *buscar_professor(Professor **professores, int *posicao)
{
    char matricula[50]; // Pede a matrícula do professor
    printf("Matricula do professor> ");
    fgets(matricula, 49, stdin);
    Professor *resultado = NULL; // Instancia resultado e posição
    int pos_resultado = -1; 
    for (int i = 0; i < MAX_PROFESSOR; i++) // Percorre todos os professores cadastrados
    {
        if (professores[i] && !strcmp(matricula, professores[i]->matricula)) // Confere se a matricula digitada confere com a de algum professor registrado
        {
            resultado = professores[i];
            break;
        }
    }
    *posicao = pos_resultado; // Incrementa a posição e retorna o professor encontrado
    return resultado;
}
/*   Print do Professor   */
void imprimir_professor(Professor *professor)
{
    printf("Matricula do professor: %s", professor->matricula); // Printa cada dado
    printf("Nome do professor: %s", professor->nome);
    printf("CPF do professor: %s", professor->cpf);
    imprimir_endereco(professor->endereco);
}

/*   Armazenamento da Turma   */
Turma *construir_turma()
{
    Turma *turma = (Turma *)malloc(sizeof(Turma)); // Aloca espaço na memória para a turma
    if (turma)
    {
        printf("Codigo da turma\t> "); // Pede ao usuário os dados da turma e armazena na struct turma
        fgets(turma->codigo, 50, stdin);
        printf("Nome da disciplina\t> ");
        fgets(turma->nome_disciplina, 50, stdin);
        printf("Media\t> ");
        scanf("%f", &(turma->media_turma));
        getchar(); // Limpa o buffer de entrada
    }
    else
    {
        perror("Não há memória disponível. Encerrando\n\n");
    }
    return turma; // Retorna a turma para ser salva no arquivo
}
/*   Buscar a Turma   */
Turma *buscar_turma(Turma **turmas, int *posicao)
{
    char codigo[50]; // Pede o código da turma
    printf("Codigo da turma > ");
    fgets(codigo, 49, stdin);
    Turma *resultado = NULL; // Instancia resultado e posição
    int pos_resultado = -1;
    for (int i = 0; i < MAX_TURMA; i++) // Percorre todas as turmas cadastradas
    {
        if (turmas[i] && !strcmp(codigo, turmas[i]->codigo)) // Confere se o código digitado confere com o de alguma turma registrada
        {
            resultado = turmas[i];
            pos_resultado = i;
            break;
        }
    }
    *posicao = pos_resultado; // Incrementa a posição e retorna a turma encontrada
    return resultado;
}
/*   Atualizar a Turma   */
Turma *atualizar_turma(Turma *turma)
{
    Turma nova_turma; // Atualiza os dados da turma, retornando uma nova turma com os dados atualizados para ser escrito sobre a anterior
    printf("Nome da Disciplina\t> ");
    fgets(nova_turma.nome_disciplina, 12, stdin);
    printf("Media\t> ");
    scanf("%f", &nova_turma.media_turma);
    return atualizarTurma(turma, &nova_turma); // Retorna a turma com os dados de nova turma
}
/*   Print da Turma   */
void imprimir_turma(Turma *turma)
{
    printf("== Turma ==\n"); // Printa cada dado
    printf("Codigo: %s", turma->codigo);
    printf("Nome da Disciplina: %s", turma->nome_disciplina);
    printf("Media da Turma: %.2f\n", turma->media_turma);
    printf("Quantidade de alunos: %d\n", turma->qtd_alunos);

    if (turma->professor != NULL) // Printa o professor, se tiver
    {
        printf("Professor: %s", turma->professor->nome);
    }

    if (turma->qtd_alunos != 0) // Printa matricula, numero e nome de todos os alunos, se tiver
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
    switch (opcao) // Switch de opções do usuário no menu estatística
    {
    case 1: // Imprimir nomes dos professores
        imprimir_nomes_professores(professores); 
        break;
    case 2: // Imprimir nomes dos professores sem turma
        imprimir_professores_sem_turma(professores, turmas);
        break;
    case 3: // Imprimir média das turmas
        imprimir_media_turmas(turmas);
        break;
    case 4: // Fecha o menu
        break;
    }
}
/* Define a função IMPRIMIR_NOMES_PROFESSORES */
void imprimir_nomes_professores(Professor **professores)
{
    if (professores[0] == NULL) // Confere se o professor é nulo
    {
        printf("Nenhum professor cadastrado!\n");
        return;
    }
    printf("=== Professores Cadastrados ===\n\n");

    for (int i = 0; i < MAX_PROFESSOR; i++) // Percorre todos os professores cadastrados
    {
        if (professores[i] == NULL)
        {
            printf("\n");
            return;
        }
        printf("%s", professores[i]->nome); // Printa o nome de cada professor
    }
}
/*  Define a função IMPRIMIR_PROFESSORES_SEM_TURMA  */
void imprimir_professores_sem_turma(Professor **professores, Turma **turmas)
{
    if (professores[0] == NULL) // Confere se o professor é nulo
    {
        printf("Nenhum professor cadastrado!\n");
        return;
    }
    printf("=== Professores que nao possuem turma ===\n\n");

    int qtd_professores_sem_turma = 0; // Instancia a quantidade de professores sem turma
    Professor *professores_sem_turma[MAX_PROFESSOR]; // Instancia o vetor de professores sem turma

    for (int i = 0; i < MAX_PROFESSOR; i++) // Percorre todos os professores cadastrados
    {
        if (professores[i] == NULL)
        {
            break;
        }

        int turma_encontrada = 0;

        for (int j = 0; j < MAX_TURMA; j++) // Percorre todas as turmas cadastradas
        {
            if (turmas[j] == NULL) // Confere se a turma é nula
            {
                break;
            }
            if (turmas[j]->professor == professores[i]) // Confere se o professor está cadastrado em alguma turma
            {
                turma_encontrada = 1;
                break;
            }
        }

        if (!turma_encontrada) // Se a turma não for encontrada, adiciona o professor no vetor de professores sem turma e incrementa o contator
        { 
            professores_sem_turma[qtd_professores_sem_turma] = professores[i];
            qtd_professores_sem_turma++;
        }
    }

    if (professores_sem_turma[0] == NULL) // Se não houver professores sem turma
    {
        printf("Todos os professores possuem uma turma!\n\n");
        return;
    }

    for (int i = 0; i < qtd_professores_sem_turma; i++) // Para cada professor sem turma, printa sua matrícula
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
    float soma = 0.0; // Instancia a soma das médias, e a quantidade de turmas
    int qtd_turmas = 0;
    for (int i = 0; i < MAX_TURMA; i++) // Percorre todas as turmas
    {
        if (turmas[i] == NULL) // Confere se a turma é nula
        {
            break;
        }
        ++qtd_turmas; // Incrementa a quantidade de turmas
        soma += turmas[i]->media_turma; // Soma as médias de cada turma
    }
    printf("Nota media de todas as turmas cadastradas: %.2f\n\n", soma / qtd_turmas); // Printa a média das turmas
}
