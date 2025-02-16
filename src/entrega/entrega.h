#ifndef ENTREGA_H
#define ENTREGA_H

typedef struct {
    int id;
    char origem[100];
    char destino[100];
    float tempoEstimado;
} Entrega;

typedef struct {
    int entregaId;
    int funcionarioId;
    int veiculoId;
    int clienteId;
    float tempoTotal;
} EntregaConcluidas;

void adicionarEntrega(const char* origem, const char* destino, float tempoEstimado);
void listarEntregas();
void atualizarEntrega(int id);
void excluirEntrega(int id);
void planejarEExecutarEGerarRelatorioEntrega(int entregaId, int funcionarioId, int veiculoId, int clienteId, float tempoTotal);
void listarRelatoriosEntregas();

#endif
