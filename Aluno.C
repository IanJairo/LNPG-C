#include <stdio.h>
#include <string.h>

#define MAX_ALUNOS 100

struct Aluno {
    char cpf[12];
    char nome[50];
    char endereco[100];
    int matricula;
};

struct Aluno alunos[MAX_ALUNOS];
int totalAlunos = 0;

int buscarAlunoPorCPF(char cpf[]) {
    int i;
    for (i = 0; i < totalAlunos; i++) {
        if (strcmp(alunos[i].cpf, cpf) == 0) {
            return i;
        }
    }
    return -1;
}

void cadastrarAluno() {
    struct Aluno aluno;

    printf("CPF: ");
    scanf("%s", aluno.cpf);

    // Verificar se o CPF já foi cadastrado
    int posicao = buscarAlunoPorCPF(aluno.cpf);
    if (posicao != -1) {
        printf("CPF já cadastrado.\n");
        return;
    }

    printf("Nome: ");
    scanf(" %[^\n]", aluno.nome);

    printf("Endereco: ");
    scanf(" %[^\n]", aluno.endereco);

    printf("Matricula: ");
    scanf("%d", &aluno.matricula);

    alunos[totalAlunos] = aluno;
    totalAlunos++;

    printf("Aluno cadastrado com sucesso.\n");
}

void listarAlunos() {
    int i;
    for (i = 0; i < totalAlunos; i++) {
        printf("CPF: %s\n", alunos[i].cpf);
        printf("Nome: %s\n", alunos[i].nome);
        printf("Endereco: %s\n", alunos[i].endereco);
        printf("Matricula: %d\n\n", alunos[i].matricula);
    }
}

int main() {
    int opcao;

    do {
        printf("1 - Cadastrar aluno\n");
        printf("2 - Listar alunos\n");
        printf("0 - Sair\n");
        printf("Opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                cadastrarAluno();
                break;
            case 2:
                listarAlunos();
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
