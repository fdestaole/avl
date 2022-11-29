UTIL=avl.c game.c util.c
MAIN=main.c
BINARY=executavel

all:
	gcc -Wall -g $(UTIL) $(MAIN) -o $(BINARY) -lm

run:
	./$(BINARY)
	
debug:
	gcc -DDEBUG -Wall $(MAIN) $(UTIL) -o $(BINARY)

valgrind:
	valgrind --tool=memcheck --leak-check=full  --track-origins=yes --show-leak-kinds=all --show-reachable=yes ./$(BINARY)

zip:
	zip entrega.zip *.c *.h CSV-TodosJogos.csv makefile

clean:
	@rm *.o
