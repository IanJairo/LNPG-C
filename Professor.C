#include <stdio.h>
#include <string.h>

#define MAX_PROFESSORES 100
#define MAX_TURMAS 100

struct Turma {
    int codigo;
    char disciplina[50];
};

struct Professor {
    int matricula;
    char nome[50];
    struct Turma turma;
};

struct Professor professores[MAX_PROFESSORES];
int totalProfessores = 0;

int buscarProfessorPorMatricula(int matricula) {
    int i;
    for (i = 0; i < totalProfessores; i++) {
        if (professores[i].matricula == matricula) {
            return i;
        }
    }
    return -1;
}

void cadastrarProfessor() {
    if (totalProfessores >= MAX_PROFESSORES) {
        printf("Limite de professores atingido.\n");
        return;
    }

    struct Professor professor;

    printf("Matricula: ");
    scanf("%d", &professor.matricula);

    // Verificar se a matricula já foi cadastrada
    int posicao = buscarProfessorPorMatricula(professor.matricula);
    if (posicao != -1) {
        printf("Matricula já cadastrada.\n");
        return;
    }

    printf("Nome: ");
    scanf(" %[^\n]", professor.nome);

    printf("Código da Turma: ");
    scanf("%d", &professor.turma.codigo);

    printf("Disciplina: ");
    scanf(" %[^\n]", professor.turma.disciplina);

    professores[totalProfessores] = professor;
    totalProfessores++;

    printf("Professor cadastrado com sucesso.\n");
}

void listarProfessores() {
    int i;
    for (i = 0; i < totalProfessores; i++) {
        printf("Matricula: %d\n", professores[i].matricula);
        printf("Nome: %s\n", professores[i].nome);
        printf("Código da Turma: %d\n", professores[i].turma.codigo);
        printf("Disciplina: %s\n\n", professores[i].turma.disciplina);
    }
}

void deletarProfessor() {
    int matricula;
    int i, posicao = -1;

    printf("Matricula do professor a ser deletado: ");
    scanf("%d", &matricula);

    for (i = 0; i < totalProfessores; i++) {
        if (professores[i].matricula == matricula) {
            posicao = i;
            break;
        }
    }

    if (posicao == -1) {
        printf("Professor não encontrado.\n");
        return;
    }

    for (i = posicao; i < totalProfessores - 1; i++) {
        professores[i] = professores[i + 1];
    }

    totalProfessores--;

    printf("Professor deletado com sucesso.\n");
}

void atualizarProfessor() {
    int matricula;
    int i, posicao = -1;

    printf("Matricula do professor a ser atualizado: ");
    scanf("%d", &matricula);

    for (i = 0; i < totalProfessores; i++) {
        if (professores[i].matricula == matricula) {
            posicao = i;
            break;
        }
    }

    if (posicao == -1) {
        printf("Professor não encontrado.\n");
        return;
    }

    printf("Matricula: ");
    scanf("%d", &professores[posicao].matricula);

    printf("Nome: ");
    scanf(" %[^\n]", professores[posicao].nome);

    printf("Código da Turma: ");
    scanf("%d", &professores[posicao].turma.codigo);

    printf("Disciplina: ");
    scanf(" %[^\n]", professores[posicao].turma.disciplina);

    printf("Professor atualizado com sucesso.\n");
}

int main() {
    int opcao;

    do {
        printf("1 - Cadastrar professor\n");
        printf("2 - Listar professores\n");
        printf("3 - Deletar professor\n");
        printf("4 - Atualizar professor\n");
        printf("0 - Sair\n");
        printf("Opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                cadastrarProfessor();
                break;
            case 2:
                listarProfessores();
                break;
            case 3:
                deletarProfessor();
                break;
            case 4:
                atualizarProfessor();
                break;
            case 0:
                printf("Encerrando o programa.\n");
                break;
            default:
                printf("Opcao invalida.\n");
                break;
        }
    } while (opcao != 0);

    return 0;
}
