/**
 * Autores:
 * Richard Fernando Heise Ferreira GRR20101053
 * Carlos Iago Bueno GRR20190171
 */
#include "left.h"
#include "right.h"

int left_heuristic(char *p_field, int size, int ball_pos) {

    //distancia da bola ate o fim do campo

    int scenario;
    int dist = ball_pos-1;

    if(dist == 0)
        return 5;

    //indice e numero de passos até terminar o jogo
    int i = ball_pos-2, steps = 0;

    //checa a posicao adjacente da bola
    if(p_field[i] != 'f')
        steps++;

    //se é par, intera i em 1 e se é impar intera i em 2
    scenario = dist % 2;

    if (scenario == 0) {
        for(i = i - 1; i >= 0 ; i-=2){

            if ( (i-1) >= 0) {
                if(p_field[i] != 'f' && p_field[i-1] != 'f')
                    steps++;

            } else {
                if(p_field[i] != 'f')
                    steps++;
            }
        }
    }
    else {
        //caso impar
        for(i = i - 2; i >= 0 ; i-=2){
            if(p_field[i] != 'f')
                steps++;
        }
    }

    return steps+1;
}

int test_philosophers_left(game_t *game, char *temp_field) {

    int h, higher_heuristic = 0;

    char* temp_field_adv = create_string();

    // caminha para a direita depois da bola
    for (int j = game->ball_pos; j < game->field_size; j++) {

        strcpy(temp_field_adv, temp_field);

        if(temp_field_adv[j] != 'f'){

            // colcoa filosofo
            temp_field_adv[j] = 'f';

            // testa a heuristica pra esquerda
            h = left_heuristic(temp_field_adv, game->field_size, game->ball_pos);

            if (h > higher_heuristic) {
                higher_heuristic = h;
            }

        }
    }

    free(temp_field_adv);
    return higher_heuristic;
}

int test_kick_left(game_t *game, char *field) {

    // se nosso oponente pode marcar um gol, desistimos
    if( left_heuristic(field, game->field_size, game->ball_pos) == 1 ){
        if(game->my_side == 'e')
            return 34000;
        return 1;
    }

    int h, higher_heuristic = 0;

    int counter = 0;

    // caminha para a esquerda
    for (int i = game->ball_pos-2; i >= 0; i--) {

        if (field[i] == 'f') {
            counter = 0;

        } else {
            counter++;

            if ( counter == 2) {
                // se encontramos dois espacos vazios em sequencia, saimos
                break;
            } else {

                // copia para um vetor temporario
                char *temp_field = create_string();
                strcpy(temp_field, field);

                // limpa os filosofos do chute
                for (int k = game->ball_pos-1; k > i; k--) {
                    temp_field[k] = '.';
                }

                // chuta
                temp_field[i] = 'o';

                // testa a heuristica para o lado que nos interessa
                if (game->my_side == 'd')
                    h = left_heuristic(temp_field, game->field_size, i+1);
                else
                    h = right_heuristic(temp_field, game->field_size, i+1);

                if (h > higher_heuristic) {
                    higher_heuristic = h;
                }
            }
        }
    }

    return higher_heuristic;
}

char* search_best_play_left (game_t *game) {

    game->ball_pos = get_ball_position(game->field, game->field_size)+1;

    // vetor temporario
    char *temp_field = create_string();
    char *best_play = create_string();
    int h, kick_heuristic, best_heuristic = 32000;

    // andamos para a esquerda da bola
    for (int i = game->ball_pos-2; i >= 0; i--) {

        // copiamos o vetor temporário
        strcpy(temp_field, game->field);

        if (temp_field[i] != 'f') {

            // jogamos o filosofo
            temp_field[i] = 'f';

            // testando jogadas do oponente
            h = test_philosophers_left(game, temp_field);

            if (game->field[game->ball_pos]  == 'f') {
                kick_heuristic = test_kick_right(game, temp_field);

                if(kick_heuristic > h)
                    h = kick_heuristic;
            }

            if (game->field[game->ball_pos-2] == 'f') {
                kick_heuristic = test_kick_left(game, temp_field);

                if(kick_heuristic > h )
                    h = kick_heuristic;
            }

            // comparando com a jogada passada
            if( h < best_heuristic){
                best_heuristic = h;
                sprintf(best_play, "%c f %d", game->my_side, i+1);
            }
        }
    }

    int* kicks = create_int_vector();
    int num_kicks = 0;
    int goal = 0;

    // olha para a esquerda da bola, se tem um filosofo o chute eh possivel
    if (game->field[game->ball_pos-2] == 'f') {

        goal = 1;
        int counter = 0;

        for (int i = game->ball_pos-3; i >= 0; i--) {

            if (temp_field[i] == 'f') {
                counter = 0;

            } else {
                counter++;

                if ( counter == 2) {
                    // se encontramos dois espacos vazios em sequencia, saimos
                    // se saimos por break, nao fizemos um gol
                    goal = 0;
                    break;

                } else {
                    // guarda os possiveis chutes
                    kicks[num_kicks] = i;
                    num_kicks++;

                    strcpy(temp_field, game->field);

                    // desloca a bola
                    for (int k = game->ball_pos-1; k >= i; k--) {
                        temp_field[k] = '.';
                    }

                    // acerta a bola
                    temp_field[i] = 'o';
                    // nova posicao da bola
                    game->ball_pos = i+1;

                    // testa jogadas do oponente
                    h = test_philosophers_left(game, temp_field);

                    // comparando com a jogada passada
                    if( h < best_heuristic){
                        best_heuristic = h;
                        kick(game, best_play, kicks, num_kicks, 0);
                    }
                }
            }
        }
    }

    // se foi gol, colocamos o gol na melhor jogada
    if (goal)
        kick(game, best_play, kicks, num_kicks, goal);

    //freee nas variáveis
    free(temp_field);
    free(game->field);
    free(game);

    return best_play;
}