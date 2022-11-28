#ifndef EX_7_GAME_H
#define EX_7_GAME_H

typedef struct game_st GAME;

GAME* create_game();
GAME* add_game(char* string);
char* return_name(GAME* structure);
int return_year(GAME* structure);
void free_game(GAME** structure);

#endif //EX_7_GAME_H
