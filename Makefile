CC = gcc
LD = gcc
CFLAGS = -g -Wall 
LDFLAGS = -I/usr/include -L/usr/lib -lGL -lGLU -lglut #–lGLEW
EXEC = main
SRC = main.c blockI.c
OBJ = $(SRC:.c=.o)
RM = rm

$(EXEC) : $(OBJ)
	$(LD) $(LDFLAGS) $(OBJ) -o $(EXEC)
	$(RM) $(OBJ)

$(OBJ): $(SRC)
	$(CC) $(CFLAGS) -c $^

clean: 
	$(RM) $(OBJ) $(EXEC)
