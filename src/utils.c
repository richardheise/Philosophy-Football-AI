/**
 * Autores:
 * Richard Fernando Heise Ferreira GRR20101053
 * Carlos Iago Bueno GRR20190171
 */
#include "utils.h"

void check_malloc(void *ptr){
    if(!ptr){
        fprintf(stderr, "ERRO MALLOC");
        exit(1);
    }
}

char *create_string(){
    char *vector = malloc(sizeof(char) * MAX_STR);
    check_malloc(vector);

    return vector;
}

int *create_int_vector(){
    int *vector = malloc(sizeof(int) * MAX_STR);
    check_malloc(vector);

    return vector;
}

game_t *create_game(){
    game_t *game = malloc(sizeof(game_t));
    check_malloc(game);

    game->field = create_string();

    return game;
}

void read_input(char *buffer, game_t *game) {
    sscanf(strtok(buffer, " \n"), "%c", &(game->my_side));
    sscanf(strtok(NULL, " \n"), "%d", &(game->field_size));
    sscanf(strtok(NULL, " \n"), "%s", game->field);
    sscanf(strtok(NULL, " \n"), "%c", &(game->opponent_side));
    sscanf(strtok(NULL, " \n"), "%c", &(game->opponent_move));
}

int get_ball_position(char *p_field, int size) {

    for (int i = 0; i < size; i++) {
        if (p_field[i] == 'o') return i;
    }
    return -1;
}

void kick(game_t *game, char *best_play, int* kicks, int num_kicks, int goal){

    char* tmp = create_string();

    // coloca uma string inicial na melhor jogada
    sprintf(best_play, "%c o %d", game->my_side, num_kicks + ((goal) ? 1 : 0));

    // concatena os proximos chutes
    for (int i = 0; i < num_kicks; i++) {
        sprintf(tmp, " %d", kicks[i]+1);
        strcat(best_play, tmp);
    }

    // se um gol eh possivel chutamos para fora do campo
    if (goal) {
        if (game->my_side == 'e') {
            sprintf(tmp, " %d", game->field_size+1);
            strcat(best_play, tmp);
        } else {
            sprintf(tmp, " %d", 0);
            strcat(best_play, tmp);
        }
    }

    free(tmp);
}