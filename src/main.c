#include <stdio.h>
#include <stdlib.h>

#include "veiculo/veiculo.h"

void menu() {
    int escolha;
    do {
        system("cls");
        printf("Escolha uma opcao:\n");
        printf("1. Adicionar Veiculo\n");
        printf("2. Listar Veiculos\n");
        printf("3. Atualizar Veiculo\n");
        printf("0. Sair\n");

        scanf("%d", &escolha);
        switch(escolha) {
            case 1: {
                system("cls");
                char tipo[20], status[10];
                float capacidade;
                printf("Tipo (ex: Caminhao): ");
                scanf("%s", tipo);
                printf("Capacidade (em kg): ");
                scanf("%f", &capacidade);
                printf("Status (livre/ocupado): ");
                scanf("%s", status);
                adicionarVeiculo(tipo, capacidade, status);
                break;
            }
            case 2:
                system("cls");
                listarVeiculos();
            break;
            case 3:
                system("cls");
                int id;
                printf("ID do veiculo a ser atualizado: ");
                scanf("%d", &id);
                atualizarVeiculo(id);
            break;
            case 0:
                printf("Saindo...\n");
            return;
            default:
                printf("Opcao invalida\n");
        }
    } while(1);
}

int main() {
    menu();
    return 0;
}
