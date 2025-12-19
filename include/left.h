/**
 * Autores:
 * Richard Fernando Heise Ferreira GRR20101053
 * Carlos Iago Bueno GRR20190171
 */
#ifndef LEFT_H
#define LEFT_H

#include "utils.h"

/**
 * Quantas jogadas sao necessarias para se fazer gol na esquerda
 * Recebe um campo, o tamanho do campo e a posicao da bola
 * Retorna o numero de jogadas necessarias para vencer.
 */
int left_heuristic(char *p_field, int size, int ball_pos);

/**
 * Testa a heuristicaEsquerda colocando filosofos na direita da bola
 * Recebe um ponteiro para o jogo e um campo
 * Retorna a heuristica para todas as jogadas possiveis de filosofos
 * na direita do campo.
 */
int test_philosophers_left(game_t *game, char *temp_field);

/**
 * Testa a heuristicaEsquerda chutes para a esquerda
 * Recebe um ponteiro para o jogo e um campo
 * Retorna a heuristica para todas as jogadas possiveis de chutes
 * para a esquerda do campo.
 */
int test_kick_left(game_t *game, char *field);

/**
 * Busca a jogada que da menos chance do jogador da direita perder o jogo
 * Recebe um ponteiro jogo
 * Retorna uma string com a melhor jogada.
 */
char* search_best_play_left (game_t *game);

#endif