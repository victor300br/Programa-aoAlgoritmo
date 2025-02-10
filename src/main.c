#include <stdio.h>
#include <stdlib.h>

#include "veiculo/veiculo.h"
#include "entrega/entrega.h"
#include "funcionario/funcionario.h"
#include "cliente/cliente.h"

void menu() {
    int escolha;
    do {
        system("cls");
        printf("Escolha uma opcao:\n");
        printf("1. Adicionar Veiculo\n");
        printf("2. Listar Veiculos\n");
        printf("3. Atualizar Veiculo\n");
        printf("4. Adicionar Entrega\n");
        printf("5. Listar Entregas\n");
        printf("6. Atualizar Entrega\n");
        printf("7. Adicionar Funcionario\n");
        printf("8. Listar Funcionarios\n");
        printf("9. Atualizar Funcionario\n");
        printf("10. Adicionar Cliente\n");
        printf("11. Listar Clientes\n");
        printf("12. Atualizar Cliente\n");
        printf("0. Sair\n");

        scanf("%d", &escolha);
        switch (escolha) {
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
                int idVeiculo;
                printf("ID do veiculo a ser atualizado: ");
                scanf("%d", &idVeiculo);
                atualizarVeiculo(idVeiculo);
                break;
            case 4: {
                system("cls");
                char origem[50], destino[50];
                float tempoEstimado;
                printf("Origem: ");
                scanf("%s", origem);
                printf("Destino: ");
                scanf("%s", destino);
                printf("Tempo estimado: ");
                scanf("%f", &tempoEstimado);
                adicionarEntrega(origem, destino, tempoEstimado);

                break;
            }
            case 5:
                system("cls");
                listarEntregas();
                break;
            case 6:
                system("cls");
                int idEntrega;
                printf("ID da entrega a ser atualizada: ");
                scanf("%d", &idEntrega);
                atualizarEntrega(idEntrega);
                break;
            case 7: {
                system("cls");
                char nome[100];
                printf("Nome do funcionário: ");
                scanf(" %[^\n]", nome);
                adicionarFuncionario(nome);
                break;
            }
            case 8:
                system("cls");
                listarFuncionarios();
                break;
            case 9:
                system("cls");
                int idFuncionario;
                printf("ID do funcionário a ser atualizado: ");
                scanf("%d", &idFuncionario);
                atualizarFuncionario(idFuncionario);
                break;
            case 10: {
                system("cls");
                char nome[100], endereco[200], tipoServico[20];
                printf("Nome do Cliente: ");
                scanf(" %[^\n]", nome);
                printf("Endereço: ");
                scanf(" %[^\n]", endereco);
                printf("Tipo de Serviço (econômico/padrão/premium): ");
                scanf(" %[^\n]", tipoServico);
                adicionarCliente(nome, endereco, tipoServico);
                break;
            }
            case 11:
                system("cls");
                listarClientes();
                break;
            case 12:
                system("cls");
                int idCliente;
                printf("ID do cliente a ser atualizado: ");
                scanf("%d", &idCliente);
                atualizarCliente(idCliente);
                break;
            case 0:
                printf("Saindo...\n");
                return;
            default:
                printf("Opcao invalida\n");
        }
    } while (1);
}

int main() {
    menu();
    return 0;
}
