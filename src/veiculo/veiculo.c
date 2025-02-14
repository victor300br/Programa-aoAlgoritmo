#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include "veiculo.h"

#define VEICULOS_FILE "bin/veiculos.dat"


int obterProximoId() {
    FILE *file = fopen(VEICULOS_FILE, "rb");
    if (file == NULL) {
        return 1;
    }

    Veiculo veiculo;
    int ultimoId = 0;

    while (fread(&veiculo, sizeof(Veiculo), 1, file)) {
        if (veiculo.id > ultimoId) {
            ultimoId = veiculo.id;
        }
    }

    fclose(file);
    return ultimoId + 1;
}


void adicionarVeiculo(const char* tipo, float capacidade, const char* status) {
    Veiculo veiculo;
    veiculo.id = obterProximoId();
    strncpy(veiculo.tipo, tipo, sizeof(veiculo.tipo) - 1);
    veiculo.capacidade = capacidade;
    strncpy(veiculo.status, status, sizeof(veiculo.status) - 1);

    FILE *file = fopen(VEICULOS_FILE, "ab");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo para escrita.\n");
        return;
    }

    fwrite(&veiculo, sizeof(Veiculo), 1, file);
    fclose(file);

    printf("Veiculo adicionado com sucesso! ID: %d\n", veiculo.id);
    sleep(3);
}


void listarVeiculos() {
    FILE *file = fopen(VEICULOS_FILE, "rb");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo de veículos.\n");
        return;
    }

    Veiculo veiculo;
    int encontrado = 0;

    while (fread(&veiculo, sizeof(Veiculo), 1, file)) {
          printf("ID: %d, Tipo: %s, Capacidade: %.2f kg, Status: %s\n",
          veiculo.id, veiculo.tipo, veiculo.capacidade, veiculo.status);
          encontrado = 1;

    }

    fclose(file);

    if (!encontrado) {
        printf("Nenhum veiculo ativo encontrado.\n");
    }

    printf("\nPressione qualquer tecla para continuar...");
    getchar();
    getchar();
}


void atualizarVeiculo(int id) {
    FILE *file = fopen(VEICULOS_FILE, "rb+");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo de veiculos.\n");
        return;
    }

    Veiculo veiculo;
    int encontrado = 0;

    while (fread(&veiculo, sizeof(Veiculo), 1, file)) {
        if (veiculo.id == id) {
            encontrado = 1;

            printf("Dados atuais do veiculo:\n");
            printf("ID: %d\nTipo: %s\nCapacidade: %.2f kg\nStatus: %s\n\n",
                   veiculo.id, veiculo.tipo, veiculo.capacidade, veiculo.status);

            printf("Novo tipo (ex: Caminhao): ");
            scanf("%s", veiculo.tipo);
            printf("Nova capacidade (em kg): ");
            scanf("%f", &veiculo.capacidade);
            printf("Novo status (livre/ocupado): ");
            scanf("%s", veiculo.status);

            fseek(file, -sizeof(Veiculo), SEEK_CUR);
            fwrite(&veiculo, sizeof(Veiculo), 1, file);
            fclose(file);

            printf("\nVeiculo atualizado com sucesso!\n");
            sleep(1);
            return;
        }
    }

    fclose(file);

    if (!encontrado) {
        printf("Nenhum veiculo encontrado com o ID informado.\n");
        sleep(3);
    }
}


void excluirVeiculo(int id) {

    FILE *file = fopen(VEICULOS_FILE, "rb+");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo de veiculos.\n");
        return;
    }


    Veiculo veiculo;
    int encontrado = 0;
    long int posicaoExclusao = -1;

    while (fread(&veiculo, sizeof(Veiculo), 1, file)) {
        if (veiculo.id == id) {
            encontrado = 1;
            posicaoExclusao = ftell(file) - sizeof(Veiculo);
            break;
        }
    }


    if (!encontrado) {
        printf("Nao existe veiculo com esse ID %d.\n", id);
        sleep(2);
        fclose(file);
        return;
    }


    fseek(file, -sizeof(Veiculo), SEEK_END);
    long int posicaoUltimo = ftell(file);
    fread(&veiculo, sizeof(Veiculo), 1, file);

    if (posicaoExclusao != posicaoUltimo) {
        fseek(file, posicaoExclusao, SEEK_SET);
        fwrite(&veiculo, sizeof(Veiculo), 1, file);
    }


    ftruncate(fileno(file), posicaoUltimo);


    fclose(file);
    printf("Veiculo com ID %d excluido com sucesso!\n", id);
    sleep(2);
}


