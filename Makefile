CFLAGS = -Wall -g 

NAME = indexer

OBJ = main.o compar.o hasher.o


all: $(NAME)

%.o: %.cpp
	gcc -c -o $@ $^

$(NAME) : $(OBJ)
	gcc -o $(NAME) $^ $(CFLAGS) -lblake3

clean:
	$(RM) $(OBJ) $(NAME)