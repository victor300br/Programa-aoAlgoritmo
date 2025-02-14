#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "funcionario.h"

#define FUNCIONARIOS_FILE "bin/funcionarios.dat"

int obterProximoIdFuncionario() {
    FILE *file = fopen(FUNCIONARIOS_FILE, "rb");
    if (file == NULL) {
        return 1;
    }
    Funcionario funcionario;
    int ultimoId = 0;

    while (fread(&funcionario, sizeof(Funcionario), 1, file)) {
        if (funcionario.id > ultimoId) {
            ultimoId = funcionario.id;
        }
    }
    fclose(file);

    return ultimoId + 1;
}

void adicionarFuncionario(const char* nome) {
    Funcionario funcionario;
    funcionario.id = obterProximoIdFuncionario();
    strcpy(funcionario.nome, nome);

    FILE *file = fopen(FUNCIONARIOS_FILE, "ab");
    if (file != NULL) {
        fwrite(&funcionario, sizeof(Funcionario), 1, file);
        fclose(file);
        printf("Funcionario adicionado com sucesso! ID: %d\n", funcionario.id);
    } else {
        printf("Erro ao abrir o arquivo para escrita.\n");
        return;
    }
    sleep(3);
}

void listarFuncionarios() {
    Funcionario funcionario;
    FILE *file = fopen(FUNCIONARIOS_FILE, "rb");
    if (file != NULL) {
        while (fread(&funcionario, sizeof(Funcionario), 1, file)) {
            printf("ID: %d, Nome: %s\n", funcionario.id, funcionario.nome);
        }
        fclose(file);
    } else {
        printf("Erro ao abrir o arquivo de funcionarios.\n");
    }

    printf("\nPressione qualquer tecla para continuar...");
    getchar();
    getchar();
}

void atualizarFuncionario(int id) {
    FILE *file = fopen(FUNCIONARIOS_FILE, "rb+");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo de funcionarios.\n");
        return;
    }

    Funcionario funcionario;
    int encontrado = 0;

    while (fread(&funcionario, sizeof(Funcionario), 1, file)) {
        if (funcionario.id == id) {
            encontrado = 1;

            printf("Dados atuais do funcionario:\n");
            printf("ID: %d\nNome: %s\n\n", funcionario.id, funcionario.nome);

            printf("Novo nome: ");
            scanf(" %[^\n]", funcionario.nome);

            fseek(file, -sizeof(Funcionario), SEEK_CUR);
            fwrite(&funcionario, sizeof(Funcionario), 1, file);
            fclose(file);

            printf("\nFuncionario atualizado com sucesso!\n");
            sleep(1);
            return;
        }
    }

    fclose(file);

    if (!encontrado) {
        printf("Nenhum funcionario encontrado com o ID informado.\n");
        sleep(3);
    }
}

void excluirFuncionario(int id) {
  FILE *file = fopen(FUNCIONARIOS_FILE, "rb+");
  if (file == NULL) {
    printf("Arquivo nao encontrado!\n");
    return;
  }

  Funcionario funcionario;
  int encontrado = 0;
  long int IdExcluido = -1;

  while(fread(&funcionario, sizeof(Funcionario), 1, file)) {
    if (funcionario.id == id) {
      encontrado = 1;
      IdExcluido = ftell(file) - sizeof(Funcionario);
      break;
    }
  }

    if (!encontrado) {
      printf("Nao existe funcionario com esse ID %d.\n", id);
      sleep(2);
      fclose(file);
      return;
  }
    fseek(file, -sizeof(Funcionario), SEEK_END);
    long int posicaoUltimo = ftell(file);
    fread(&funcionario, sizeof(Funcionario), 1, file);

    if (IdExcluido != posicaoUltimo) {
        fseek(file, IdExcluido, SEEK_SET);
        fwrite(&funcionario, sizeof(Funcionario), 1, file);
    }

    ftruncate(fileno(file),posicaoUltimo);
    fclose(file);
    printf("Funcionario com ID %d excluido com sucesso!\n", id);
    sleep(2);
}
