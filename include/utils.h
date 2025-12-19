/**
 * Autores:
 * Richard Fernando Heise Ferreira GRR20101053
 * Carlos Iago Bueno GRR20190171
 */

#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include "campo.h"
#include <math.h>

#define MAX_STR 512
#define MAX_INT 16

// Struct jogo
typedef struct game_type
{
    char my_side, opponent_side, opponent_move;
    int field_size, ball_pos;
    char *field;

} game_t;

/**
 * Testa se o alocamento funcionou
 * Retorna um erro caso não tenha funcionado.
 */
void check_malloc(void *ptr);

/**
 * Cria um vetor de char (string)
 * Retorna a string criado.
 */
char *create_string();

/**
 * Inicializa a struct jogo.
 */
game_t *create_game();

/**
 * Cria um vetor de inteiro (string)
 * Retorna o vetor criado.
 */
int *create_int_vector();

/**
 * Descobre a posicao da bola
 * Recebe uma string do campo e o tamanho do campo
 * Retorna um inteiro que é a posicao da bola.
 */
int get_ball_position(char *p_field, int size);

/**
 * Le o que veio do buffer e aloca na struct de jogo
 * Recebe o buffer e um ponteiro para a struct jogo.
 */
void read_input(char *buffer, game_t *game);

/**
 * Chuta a bola
 * Recebe uma struct jogo, a string jogada em que será escrito o chute,
 * o vetor de possiveis chutes, a quantidade de chutes possiveis e se o chute
 * foi ou não um gol.
 */
void kick(game_t *game, char *best_play, int* kicks, int num_kicks, int goal);

#endif