#include "game.h"
#include <stdlib.h>
#include <string.h>

struct game_st{
    char *name;
    char *company;
    int year;
};

GAME* create_game(){

    GAME* structure = (GAME*)malloc(sizeof(GAME));

    structure->name = NULL;
    structure->company = NULL;
    structure->year = 0;

    return structure;
}

GAME* add_game(char* string){
    GAME* structure = create_game();

    char* aux = strtok(string,";");
    structure->name = aux;

    aux = strtok(NULL,";");
    structure->year = atoi(aux);

    aux = strtok(NULL,"\0");
    structure->company = aux;

    return structure;
}
char* return_name(GAME* structure){
    return structure->name;
}
int return_year(GAME* structure){
    return structure->year;
}
void free_game(GAME** structure){

    free((*structure)->name);
    (*structure)->name = NULL;
    free((*structure)->company);
    (*structure)->company = NULL;

    free(*structure);
    *structure = NULL;

    return;
}
