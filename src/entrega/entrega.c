#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "entrega.h"
#include "veiculo.h"
#include "funcionario.h"
#include "cliente.h"


#define ENTREGAS_FILE "bin/entregas.dat"
#define RELATORIO_FILE "bin/relatorio_entregas.dat"
#define FUNCIONARIOS_FILE "bin/funcionarios.dat"
#define VEICULOS_FILE "bin/veiculos.dat"
#define CLIENTES_FILE "bin/clientes.dat"

typedef struct {
    int entregaId;
    int funcionarioId;
    int veiculoId;
    int clienteId;
    float tempoTotal;
} EntregaConcluida;

int obterProximoIdEntrega() {
    FILE *file = fopen(ENTREGAS_FILE, "rb");
    if (file == NULL) {
        return 1;
    }
    Entrega entrega;
    int ultimoId = 0;

    while (fread(&entrega, sizeof(Entrega), 1, file)) {
        if (entrega.id > ultimoId) {
            ultimoId = entrega.id;
        }
    }
    fclose(file);

    return ultimoId + 1;
}

void adicionarEntrega(const char* origem, const char* destino, float tempoEstimado) {
    Entrega entrega;
    entrega.id = obterProximoIdEntrega();
    strcpy(entrega.origem, origem);
    strcpy(entrega.destino, destino);
    entrega.tempoEstimado = tempoEstimado;
    sleep(1);

    FILE *file = fopen(ENTREGAS_FILE, "ab");
    if (file != NULL) {
        fwrite(&entrega, sizeof(Entrega), 1, file);
        fclose(file);
        printf("Entrega adicionada com sucesso! ID: %d\n", entrega.id);
    } else {
        printf("Erro ao abrir o arquivo para escrita.\n");
        return;
    }
    sleep(3);
}

void listarEntregas() {
    Entrega entrega;
    FILE *file = fopen(ENTREGAS_FILE, "rb");
    if (file != NULL) {
        while (fread(&entrega, sizeof(Entrega), 1, file)) {
            printf("ID: %d, Origem: %s, Destino: %s, Tempo Estimado: %.2f horas\n",
                   entrega.id, entrega.origem, entrega.destino, entrega.tempoEstimado);
        }
        fclose(file);
    } else {
        printf("Erro ao abrir o arquivo de entregas.\n");
    }

    printf("\nPressione qualquer tecla para continuar...");
    getchar();
    getchar(); //por algum motivo so funciona se eu colocar 2 getchar, nao apaga
}

void atualizarEntrega(int id) {
    FILE *file = fopen(ENTREGAS_FILE, "rb+");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo de entregas.\n");
        return;
    }

    Entrega entrega;
    int encontrado = 0;

    while (fread(&entrega, sizeof(Entrega), 1, file)) {
        if (entrega.id == id) {
            encontrado = 1;

            printf("Dados atuais da entrega:\n");
            printf("ID: %d\nOrigem: %s\nDestino: %s\nTempo Estimado: %.2f horas\n\n",
                   entrega.id, entrega.origem, entrega.destino, entrega.tempoEstimado);

            printf("Nova origem: ");
            scanf(" %[^\n]", entrega.origem);
            printf("Novo destino: ");
            scanf(" %[^\n]", entrega.destino);
            printf("Novo tempo estimado (em horas): ");
            scanf("%f", &entrega.tempoEstimado);

            fseek(file, -sizeof(Entrega), SEEK_CUR);
            fwrite(&entrega, sizeof(Entrega), 1, file);
            fclose(file);

            printf("\nEntrega atualizada com sucesso!\n");
            sleep(1);
            return;
        }
    }

    fclose(file);

    if (!encontrado) {
        printf("Nenhuma entrega encontrada com o ID informado.\n");
        sleep(3);
    }
}
void excluirEntrega(int id) {
  FILE *file = fopen(ENTREGAS_FILE, "rb+");
  if (file == NULL) {
    printf("Erro ao abrir o arquivo de entregas.\n");
  }
    Entrega entrega;
    int encontrado = 0;
    long int posicaoExclusao = -1;

    while (fread(&entrega, sizeof(Entrega), 1, file)) {
        if (entrega.id == id) {
            encontrado = 1;
            posicaoExclusao = ftell(file) - sizeof(Entrega);
            break;
        }
    }
    if (!encontrado) {
        printf("Nao existe entrega com esse ID %d.\n", id);
        sleep(2);
        fclose(file);
        return;
    }
    fseek(file, -sizeof(Entrega), SEEK_END);
    long int posicaoUltimo = ftell(file);
    fread(&entrega, sizeof(Entrega), 1, file);

    if (posicaoExclusao != posicaoUltimo) {
        fseek(file, posicaoExclusao, SEEK_SET);
        fwrite(&entrega, sizeof(Entrega), 1, file);
    }

    ftruncate(fileno(file), posicaoUltimo);

    fclose(file);
    printf("Entrega com ID %d excluido com sucesso!\n", id);
    sleep(2);
}


void planejarEExecutarEGerarRelatorioEntrega(int entregaId, int funcionarioId, int veiculoId, int clienteId, float tempoTotal) {
    FILE *file = fopen(ENTREGAS_FILE, "rb");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo de entregas.\n");
        return;
    }
    Entrega entrega;
    int entregaEncontrada = 0;
    while (fread(&entrega, sizeof(Entrega), 1, file)) {
        if (entrega.id == entregaId) {
            entregaEncontrada = 1;
            break;
        }
    }
    fclose(file);
    if (!entregaEncontrada) {
        printf("Entrega com ID %d não encontrada.\n", entregaId);
        return;
    }
    file = fopen(FUNCIONARIOS_FILE, "rb");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo de funcionários.\n");
        return;
    }

    Funcionario funcionario;
    int funcionarioEncontrado = 0;
    while (fread(&funcionario, sizeof(Funcionario), 1, file)) {
        if (funcionario.id == funcionarioId) {
            funcionarioEncontrado = 1;
            break;
        }
    }
    fclose(file);

    if (!funcionarioEncontrado) {
        printf("Funcionário com ID %d não encontrado.\n", funcionarioId);
        return;
    }


    file = fopen(CLIENTES_FILE, "rb");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo de clientes.\n");
        return;
    }

    Cliente cliente;
    int clienteEncontrado = 0;
    while (fread(&cliente, sizeof(Cliente), 1, file)) {
        if (cliente.id == clienteId) {
            clienteEncontrado = 1;
            break;
        }
    }
    fclose(file);

    if (!clienteEncontrado) {
        printf("Cliente com ID %d não encontrado.\n", clienteId);
        return;
    }


    file = fopen(VEICULOS_FILE, "rb+");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo de veículos.\n");
        return;
    }

    Veiculo veiculo;
    int veiculoEncontrado = 0;
    while (fread(&veiculo, sizeof(Veiculo), 1, file)) {
        if (veiculo.id == veiculoId) {
            veiculoEncontrado = 1;
            break;
        }
    }

    if (!veiculoEncontrado) {
        printf("Veículo com ID %d não encontrado.\n", veiculoId);
        fclose(file);
        return;
    }

    if (strcmp(veiculo.status, "ocupado") == 0) {
        printf("O veículo com ID %d está ocupado e não pode realizar a entrega.\n", veiculoId);
        fclose(file);
        return;
    }
    fclose(file);


    EntregaConcluida entregaConcluida;
    entregaConcluida.entregaId = entregaId;
    entregaConcluida.funcionarioId = funcionarioId;
    entregaConcluida.veiculoId = veiculoId;
    entregaConcluida.clienteId = clienteId;
    entregaConcluida.tempoTotal = tempoTotal;
    sleep(3);

    file = fopen(RELATORIO_FILE, "ab");
    if (file != NULL) {
        fwrite(&entregaConcluida, sizeof(EntregaConcluida), 1, file);
        fclose(file);
        printf("Entrega concluída registrada com sucesso! ID: %d\n", entregaId);
    } else {
        printf("Erro ao abrir o arquivo para escrita.\n");
        return;
    }
    sleep(3);
}

void listarRelatoriosEntregas() {
    FILE *file = fopen(RELATORIO_FILE, "rb");
    if (file == NULL) {
        printf("Nenhum relatorio de entrega encontrado.\n");
        return;
    }

    EntregaConcluida entrega;
    printf("Lista de Relatorios de Entregas Concluidas\n");
    printf("=========================================\n\n");

    while (fread(&entrega, sizeof(EntregaConcluida), 1, file)) {
        printf("ID: %d\n", entrega.entregaId);
        printf("Funcionario ID: %d\n", entrega.funcionarioId);
        printf("Veiculo ID: %d\n", entrega.veiculoId);
        printf("Cliente ID: %d\n", entrega.clienteId);
        printf("Tempo Total de Entrega: %.2f horas\n", entrega.tempoTotal);
        printf("---------------------------------\n\n");
    }

    fclose(file);
    sleep(3);
}





