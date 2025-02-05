CC = gcc
CFLAGS = -Wall -Wextra -pedantic -I src/veiculo

SRC = src/main.c \
      src/veiculo/veiculo.c \


OBJ = $(SRC:.c=.o)

EXEC = sistema_gestao

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(OBJ) -o $(EXEC)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(EXEC)
