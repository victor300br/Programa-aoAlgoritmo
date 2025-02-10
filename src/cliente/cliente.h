#ifndef CLIENTE_H
#define CLIENTE_H

typedef struct {
    int id;
    char nome[100];
    char endereco[200];
    char tipoServico[20];
} Cliente;

void adicionarCliente(const char* nome, const char* endereco, const char* tipoServico);
void listarClientes();
void atualizarCliente(int id);

#endif
