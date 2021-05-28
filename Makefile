CC = gcc
NAME = dec_opcode
CFLAGS = -I include
SRC = $(wildcard src/*.c)
OBJ = $(SRC:.c=.o)

all: $(NAME)

%.o : %.c
	@echo "\033[38;5;82m[\033[94m+\033[38;5;82m] Creation of the object \033[38;5;226m$< \033[32;5;85m -> \033[38;5;226m $@ \033[00m"
	@$(CC) $(CFLAGS) -o $@ -c $<

$(NAME) : $(OBJ)
	@$(CC) $(CFLAGS) -o $(NAME) $^

clean: $(OBJ)
	rm -f $^

fclean:
	rm -f $(NAME)

re: fclean clean