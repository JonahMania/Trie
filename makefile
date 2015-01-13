NAME = trietest
SRC = trietest.cpp\

OBJ = $(SRC:.cpp=.o)
RM = rm -f
all: $(OBJ)
	g++ -g $(OBJ) -o $(NAME)

clean:
	-$(RM) *.o
	-$(RM) *.core

