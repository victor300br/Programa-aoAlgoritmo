CC = gcc
CFLAGS = -Wall -Wextra -pedantic -I src/veiculo -I src/entrega -I src/funcionario -I src/cliente
LDFLAGS = -mconsole

SRC = src/main.c \
      src/veiculo/veiculo.c \
      src/entrega/entrega.c \
      src/funcionario/funcionario.c \
      src/cliente/cliente.c

OBJ = $(SRC:.c=.o)

EXEC = sistema_gestao

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(OBJ) -o $(EXEC) $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(EXEC)
