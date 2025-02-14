#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "cliente.h"

#define CLIENTES_FILE "bin/clientes.dat"

int obterProximoIdCliente() {
    FILE *file = fopen(CLIENTES_FILE, "rb");
    if (file == NULL) {
        return 1;
    }
    Cliente cliente;
    int ultimoId = 0;

    while (fread(&cliente, sizeof(Cliente), 1, file)) {
        if (cliente.id > ultimoId) {
            ultimoId = cliente.id;
        }
    }
    fclose(file);

    return ultimoId + 1;
}

void adicionarCliente(const char* nome, const char* endereco, const char* tipoServico) {
    Cliente cliente;
    cliente.id = obterProximoIdCliente();
    strcpy(cliente.nome, nome);
    strcpy(cliente.endereco, endereco);
    strcpy(cliente.tipoServico, tipoServico);

    FILE *file = fopen(CLIENTES_FILE, "ab");
    if (file != NULL) {
        fwrite(&cliente, sizeof(Cliente), 1, file);
        fclose(file);
        printf("Cliente adicionado com sucesso! ID: %d\n", cliente.id);
    } else {
        printf("Erro ao abrir o arquivo para escrita.\n");
        return;
    }
    sleep(3);
}

void listarClientes() {
    Cliente cliente;
    FILE *file = fopen(CLIENTES_FILE, "rb");
    if (file != NULL) {
        while (fread(&cliente, sizeof(Cliente), 1, file)) {
            printf("ID: %d, Nome: %s, Endereco: %s, Tipo de Servico: %s\n",
                   cliente.id, cliente.nome, cliente.endereco, cliente.tipoServico);
        }
        fclose(file);
    } else {
        printf("Erro ao abrir o arquivo de clientes.\n");
    }

    printf("\nPressione qualquer tecla para continuar...");
    getchar();
    getchar();
}

void atualizarCliente(int id) {
    FILE *file = fopen(CLIENTES_FILE, "rb+");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo de clientes.\n");
        return;
    }

    Cliente cliente;
    int encontrado = 0;

    while (fread(&cliente, sizeof(Cliente), 1, file)) {
        if (cliente.id == id) {
            encontrado = 1;

            printf("Dados atuais do cliente:\n");
            printf("ID: %d\nNome: %s\nEndereco: %s\nTipo de Servico: %s\n\n",
                   cliente.id, cliente.nome, cliente.endereco, cliente.tipoServico);

            printf("Novo nome: ");
            scanf(" %[^\n]", cliente.nome);
            printf("Novo endereco: ");
            scanf(" %[^\n]", cliente.endereco);
            printf("Novo tipo de servico (economico/padrao/premium): ");
            scanf(" %[^\n]", cliente.tipoServico);

            fseek(file, -sizeof(Cliente), SEEK_CUR);
            fwrite(&cliente, sizeof(Cliente), 1, file);
            fclose(file);

            printf("\nCliente atualizado com sucesso!\n");
            sleep(1);
            return;
        }
    }

    fclose(file);

    if (!encontrado) {
        printf("Nenhum cliente encontrado com o ID informado.\n");
        sleep(3);
    }
}

void excluirCliente(int id) {
  FILE *file = fopen(CLIENTES_FILE, "rb+");
  if (file == NULL) {
    printf("Erro ao abrir o arquivo de clientes.\n");
    return;
  }

    Cliente cliente;
    int encontrado = 0;
    long int posicaoExclusao = -1;

    while (fread(&cliente, sizeof(Cliente), 1, file)) {
        if (cliente.id == id) {
            encontrado = 1;
            posicaoExclusao = ftell(file) - sizeof(Cliente);
            break;
        }
    }


    if (!encontrado) {
        printf("Nao existe cliente com esse ID %d.\n", id);
        sleep(2);
        fclose(file);
        return;
    }


    fseek(file, -sizeof(Cliente), SEEK_END);
    long int posicaoUltimo = ftell(file);
    fread(&cliente, sizeof(Cliente), 1, file);

    if (posicaoExclusao != posicaoUltimo) {
        fseek(file, posicaoExclusao, SEEK_SET);
        fwrite(&cliente, sizeof(Cliente), 1, file);
    }


    ftruncate(fileno(file), posicaoUltimo);


    fclose(file);
    printf("Cliente com ID %d excluido com sucesso!\n", id);
    sleep(2);
}
