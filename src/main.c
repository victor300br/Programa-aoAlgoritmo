#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "veiculo/veiculo.h"
#include "entrega/entrega.h"
#include "funcionario/funcionario.h"
#include "cliente/cliente.h"

void gerenciarRecursos() {
    int escolha;
    do {
        system("cls");
        printf(
    "  __  __             _             _                             _        ____                               \n"
    " |  \\/  | __ _ _ __ (_)_ __  _   _| | __ _  ___ __ _  ___     __| | ___  |  _ \\ ___  ___ _   _ _ __ ___  ___ \n"
    " | |\\/| |/ _` | '_ \\| | '_ \\| | | | |/ _` |/ __/ _` |/ _ \\   / _` |/ _ \\ | |_) / _ \\/ __| | | | '__/ _ \\/ __|\n"
    " | |  | | (_| | | | | | |_) | |_| | | (_| | (_| (_| | (_) | | (_| |  __/ |  _ <  __/ (__| |_| | | | (_) \\__ \\\n"
    " |_|  |_|\\__,_|_| |_|_| .__/ \\__,_|_|\\__,_|\\___\\__,_|\\___/   \\__,_|\\___| |_| \\_\\___|\\___|\\__,_|_|  \\___/|___/\n"
    "                      |_|                                                                                     \n"
);
        printf("Escolha uma opcao:\n");
        printf("1. Gerenciar Veiculos\n");
        printf("2. Gerenciar Entregas\n");
        printf("3. Gerenciar Funcionarios\n");
        printf("4. Gerenciar Clientes\n");
        printf("0. Voltar\n");

        scanf("%d", &escolha);
        switch (escolha) {
            case 1: {
                int opVeiculo;
                do {
                    system("cls");
                    printf(
                " __     __   _            _           \n"
                     " \\ \\   / /__(_) ___ _   _| | ___  ___ \n"
                     "  \\ \\ / / _ \\ |/ __| | | | |/ _ \\/ __|\n"
                     "   \\ V /  __/ | (__| |_| | | (_) \\__ \\\n"
                     "    \\_/ \\___|_|\\___|\\__,_|_|\\___/|___/\n"
                     "                                       \n"
                    );
                    printf("Gerenciar Veiculos:\n");
                    printf("1. Adicionar Veiculo\n");
                    printf("2. Listar Veiculos\n");
                    printf("3. Atualizar Veiculo\n");
                    printf("4. Excluir Veiculo\n");
                    printf("0. Voltar\n");
                    scanf("%d", &opVeiculo);
                    switch (opVeiculo) {
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
                        case 4:
                            system("cls");
                            int idVeiculoExcluido;
                            printf("ID do veiculo a ser excluido: ");
                            scanf("%d", &idVeiculoExcluido);
                            excluirVeiculo(idVeiculoExcluido);
                            break;
                        case 0:
                            break;
                        default:
                            printf("Opcao invalida\n");
                    }
                } while (opVeiculo != 0);
                break;
            }
            case 2: {
                int opEntrega;
                do {
                    system("cls");
                    printf(
                    "  _____       _                             \n"
                    " | ____|_ __ | |_ _ __ ___  __ _  __ _ ___ \n"
                    " |  _| | '_ \\| __| '__/ _ \\/ _` |/ _` / __|\n"
                    " | |___| | | | |_| | |  __/ (_| | (_| \\__ \\\n"
                    " |_____|_| |_|\\__|_|  \\___|\\__, |\\__,_|___/\n"
                    "                           |___/            \n"
                    );
                    printf("Gerenciar Entregas:\n");
                    printf("1. Adicionar Entrega\n");
                    printf("2. Listar Entregas\n");
                    printf("3. Atualizar Entrega\n");
                    printf("4. Excluir Entrega\n");
                    printf("0. Voltar\n");
                    scanf("%d", &opEntrega);
                    switch (opEntrega) {
                        case 1: {
                            system("cls");
                            char origem[50], destino[50];
                            float tempoEstimado;
                            printf("Origem: ");
                            scanf(" %[^\n]", origem);
                            printf("Destino: ");
                            scanf(" %[^\n]", destino);
                            printf("Tempo estimado (em horas): ");
                            scanf("%f", &tempoEstimado);
                            adicionarEntrega(origem, destino, tempoEstimado);
                            break;
                        }
                        case 2:
                            system("cls");
                            listarEntregas();
                            break;
                        case 3:
                            system("cls");
                            int idEntrega;
                            printf("ID da entrega a ser atualizada: ");
                            scanf("%d", &idEntrega);
                            atualizarEntrega(idEntrega);
                            break;
                        case 4:
                            system("cls");
                            int idEntregaExcluido;
                            printf("ID da entrega a ser excluida: ");
                            scanf("%d", &idEntregaExcluido);
                            excluirEntrega(idEntregaExcluido);
                            break;
                        case 0:
                            break;
                        default:
                            printf("Opcao invalida\n");
                    }
                } while (opEntrega != 0);
                break;
            }
            case 3: {
                int opFuncionario;
                do {
                    system("cls");
                    printf(
                "  _____                 _                        _           \n"
                    " |  ___|   _ _ __   ___(_) ___  _ __   __ _ _ __(_) ___  ___ \n"
                    " | |_ | | | | '_ \\ / __| |/ _ \\| '_ \\ / _` | '__| |/ _ \\/ __|\n"
                    " |  _|| |_| | | | | (__| | (_) | | | | (_| | |  | | (_) \\__ \\\n"
                    " |_|   \\__,_|_| |_|\\___|_|\\___/|_| |_|\\__,_|_|  |_|\\___/|___/\n"
                    "                                                              \n"
                    );
                    printf("Gerenciar Funcionarios:\n");
                    printf("1. Adicionar Funcionario\n");
                    printf("2. Listar Funcionarios\n");
                    printf("3. Atualizar Funcionario\n");
                    printf("4. Excluir Funcionario\n");
                    printf("0. Voltar\n");
                    scanf("%d", &opFuncionario);
                    switch (opFuncionario) {
                        case 1: {
                            system("cls");
                            char nome[100];
                            printf("Nome do funcionario: ");
                            scanf(" %[^\n]", nome);
                            adicionarFuncionario(nome);
                            break;
                        }
                        case 2:
                            system("cls");
                            listarFuncionarios();
                            break;
                        case 3:
                            system("cls");
                            int idFuncionario;
                            printf("ID do funcionario a ser atualizado: ");
                            scanf("%d", &idFuncionario);
                            atualizarFuncionario(idFuncionario);
                            break;
                        case 4:
                            system("cls");
                            int idFuncionarioExcluido;
                            printf("ID do funcionario a ser excluido: ");
                            scanf("%d", &idFuncionarioExcluido);
                            excluirFuncionario(idFuncionarioExcluido);
                            break;
                        case 0:
                            break;
                        default:
                            printf("Opcao invalida\n");
                    }
                } while (opFuncionario != 0);
                break;
            }
            case 4: {
                int opCliente;
                do {
                    system("cls");
                    printf(
                    "   ____ _ _            _            \n"
                    "  / ___| (_) ___ _ __ | |_ ___  ___ \n"
                    " | |   | | |/ _ \\ '_ \\| __/ _ \\/ __|\n"
                    " | |___| | |  __/ | | | ||  __/\\__ \\\n"
                    "  \\____|_|_|\\___|_| |_|\\__\\___||___/\n"
                    "                                     \n"
                    );
                    printf("Gerenciar Clientes:\n");
                    printf("1. Adicionar Cliente\n");
                    printf("2. Listar Clientes\n");
                    printf("3. Atualizar Cliente\n");
                    printf("4. Excluir Cliente\n");
                    printf("0. Voltar\n");
                    scanf("%d", &opCliente);
                    switch (opCliente) {
                        case 1: {
                            system("cls");
                            char nome[100], endereco[200], tipoServico[20];
                            printf("Nome do Cliente: ");
                            scanf(" %[^\n]", nome);
                            printf("Endereco: ");
                            scanf(" %[^\n]", endereco);
                            printf("Tipo de Servico (economico/padrao/premium): ");
                            scanf(" %[^\n]", tipoServico);
                            adicionarCliente(nome, endereco, tipoServico);
                            break;
                        }
                        case 2:
                            system("cls");
                            listarClientes();
                            break;
                        case 3:
                            system("cls");
                            int idCliente;
                            printf("ID do cliente a ser atualizado: ");
                            scanf("%d", &idCliente);
                            atualizarCliente(idCliente);
                            break;
                        case 4:
                            system("cls");
                            int idClienteExcluido;
                            printf("ID do cliente a ser excluido: ");
                            scanf("%d", &idClienteExcluido);
                            excluirCliente(idClienteExcluido);
                            break;
                        case 0:
                            break;
                        default:
                            printf("Opcao invalida\n");
                    }
                } while (opCliente != 0);
                break;
            }
            case 0:
                break;
            default:
                printf("Opcao invalida\n");
        }
    } while (escolha != 0);
}

void realizarEntregas() {
    int escolha;
    do {
        system("cls");
        printf(
    "                 _ _                 _____       _                             \n"
        "  _ __ ___  __ _| (_)______ _ _ __  | ____|_ __ | |_ _ __ ___  __ _  __ _ ___ \n"
        " | '__/ _ \\/ _` | | |_  / _` | '__| |  _| | '_ \\| __| '__/ _ \\/ _` |/ _` / __|\n"
        " | | |  __/ (_| | | |/ / (_| | |    | |___| | | | |_| | |  __/ (_| | (_| \\__ \\\n"
        " |_|  \\___|\\__,_|_|_/___\\__,_|_|    |_____|_| |_|\\__|_|  \\___|\\__, |\\__,_|___/\n"
        "                                                              |___/            \n"
        );
        printf("Escolha uma opcao:\n");
        printf("1. Realizar entrega\n");
        printf("2. Listar relatorios detalhados\n");
        printf("0. Voltar\n");

        scanf("%d", &escolha);
        switch (escolha) {
            case 1: {
                system("cls");
                int entregaId, funcionarioId, veiculoId, clienteId;
                float tempoTotal;

                printf("\nInforme o ID da entrega: ");
                scanf("%d", &entregaId);

                printf("Informe o ID do funcionario: ");
                scanf("%d", &funcionarioId);

                printf("Informe o ID do veiculo: ");
                scanf("%d", &veiculoId);

                printf("Informe o ID do cliente: ");
                scanf("%d", &clienteId);

                printf("Informe o tempo total da entrega (em horas): ");
                scanf("%f", &tempoTotal);

                planejarEExecutarEGerarRelatorioEntrega(entregaId, funcionarioId, veiculoId, clienteId, tempoTotal);
                system("pause");
            }
            break;
            case 2:
                system("cls");
                listarRelatoriosEntregas();
            break;
            case 0:
                printf("Saindo...\n");
            break;
            default:
                printf("Opcao invalida\n");
        }
    } while (escolha != 0);
}


void menuPrincipal() {
    int escolha;
    do {
        system("cls");
        printf(
       "      _     _                             _                       _               \n"
       "  ___(_)___| |_ ___ _ __ ___   __ _    __| | ___    __ _  ___  ___| |_ __ _  ___  \n"
       " / __| / __| __/ _ \\ '_ ` _ \\ / _` |  / _` |/ _ \\  / _` |/ _ \\/ __| __/ _` |/ _ \\ \n"
       " \\__ \\ \\__ \\ ||  __/ | | | | | (_| | | (_| |  __/ | (_| |  __/\\__ \\ || (_| | (_) | \n"
       " |___/_|___/\\__\\___|_| |_| |_|\\__,_|  \\__,_|\\___|  \\__,_|\\___||___/\\__\\__,_|\\___/ \n"
       "                                                   |___/                           \n"
   );
        printf("Escolha uma opcao:\n");
        printf("1. Manipulacao de Recursos\n");
        printf("2. Realizar Entregas\n");
        printf("0. Sair\n");

        scanf("%d", &escolha);
        switch (escolha) {
            case 1:
                gerenciarRecursos();
                break;
            case 2:
                realizarEntregas();
                break;
            case 0:
                printf("Saindo...\n");
                break;
            default:
                printf("Opcao invalida\n");
        }
    } while (escolha != 0);
}

int main() {
    menuPrincipal();
    return 0;
}
