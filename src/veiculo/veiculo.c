#include <stdio.h>
#include <string.h>
#include "veiculo.h"
#include <unistd.h>
#include <stdlib.h>

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
    strcpy(veiculo.tipo, tipo);
    veiculo.capacidade = capacidade;
    strcpy(veiculo.status, status);

    FILE *file = fopen(VEICULOS_FILE, "ab");
    if (file != NULL) {
        fwrite(&veiculo, sizeof(Veiculo), 1, file);
        fclose(file);
        printf("Veiculo adicionado com sucesso! ID: %d\n", veiculo.id);
    } else {
        printf("Erro ao abrir o arquivo para escrita.\n");
        return;
    }
    sleep(3);
}

void listarVeiculos() {
    Veiculo veiculo;
    FILE *file = fopen(VEICULOS_FILE, "rb");
    if (file != NULL) {
        while (fread(&veiculo, sizeof(Veiculo), 1, file)) {
            printf("ID: %d, Tipo: %s, Capacidade: %.2f kg, Status: %s\n",
                   veiculo.id, veiculo.tipo, veiculo.capacidade, veiculo.status);
        }
        fclose(file);
    } else {
        printf("Erro ao abrir o arquivo de veículos.\n");
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