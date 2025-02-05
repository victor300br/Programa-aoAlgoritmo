#ifndef VEICULO_H
#define VEICULO_H

typedef struct {
    int id;
    char tipo[20];
    float capacidade;
    char status[10];
} Veiculo;

void adicionarVeiculo(const char* tipo, float capacidade, const char* status);
void listarVeiculos();
void atualizarVeiculo(int id);
#endif
