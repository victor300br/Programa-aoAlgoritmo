#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "entrega.h"

#define ENTREGAS_FILE "bin/entregas.dat"

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
    getchar();
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



