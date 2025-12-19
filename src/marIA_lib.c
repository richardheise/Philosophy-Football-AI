/**
 * Autores:
 * Richard Fernando Heise Ferreira GRR20101053
 * Carlos Iago Bueno GRR20190171
 */
#include "marIA.h"

char* solve(char* buffer) {
    //crio a struct
    game_t *game;
    game = create_game();

    //le entrada e descobre posicao da bola
    read_input(buffer, game);

    // verifica qual lado estamos e chama o respectivo
    if (game->my_side == 'e') {
        return search_best_play_right(game);
    }
    if (game->my_side == 'd') {
        return search_best_play_left(game);
    }

    return "0";
}
