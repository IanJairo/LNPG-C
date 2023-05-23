#include "menus.h"
#include "tratadores.h"
#include <stdio.h>

int main(int argc, char const *argv[])
{
    int op_menu_principal = 0;

    do
    {
        op_menu_principal = menu_principal();
        switch (op_menu_principal)
        {
        case 1:
            tratador_menu_aluno();
            break;
        case 2:
            tratador_menu_professor();
            break;
        case 3:
            tratador_menu_turma();
            break;
        case 4:
            printf("Finalizando app...\n\n");
        }
    } while (op_menu_principal != 4);
    return 0;
}
