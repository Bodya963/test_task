CFLAGS = -Wall -g 

NAME = indexer

OBJ = main.o  hasher.o comper.o


all: $(NAME)

%.o: %.cpp
	gcc -c -o $@ $^

$(NAME) : $(OBJ)
	gcc -o $(NAME) $^ $(CFLAGS) -lblake3 -lm

clean:
	$(RM) $(OBJ) $(NAME)