#ifndef FUNCIONARIO_H
#define FUNCIONARIO_H

typedef struct {
    int id;
    char nome[100];
} Funcionario;

void adicionarFuncionario(const char* nome);
void listarFuncionarios();
void atualizarFuncionario(int id);
void excluirFuncionario(int id);
#endif
