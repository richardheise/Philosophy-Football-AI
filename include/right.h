/**
 * Autores:
 * Richard Fernando Heise Ferreira GRR20101053
 * Carlos Iago Bueno GRR20190171
 */
#ifndef RIGHT_H
#define RIGHT_H

#include "utils.h"

/**
 * Quantas jogadas sao necessarias para se fazer gol na direita
 * Recebe um campo, o tamanho do campo e a posicao da bola
 * Retorna o numero de jogadas necessarias para vencer.
 */
int right_heuristic(char *p_field, int size, int ball_pos);

/**
 * Testa a heuristicaEsquerda colocando filosofos na esquerda da bola
 * Recebe um ponteiro para o jogo e um campo
 * Retorna a heuristica para todas as jogadas possiveis de filosofos
 * na esquerda do campo.
 */
int test_philosophers_right(game_t *game, char *temp_field);

/**
 * Testa a heuristicaEsquerda chutes para a direita
 * Recebe um ponteiro para o jogo e um campo
 * Retorna a heuristica para todas as jogadas possiveis de chutes
 * para a direita do campo.
 */
int test_kick_right(game_t *game, char *field);

/**
 * Busca a jogada que da menos chance do jogador da esquerda perder o jogo
 * Recebe um ponteiro jogo
 * Retorna uma string com a melhor jogada.
 */
char* search_best_play_right(game_t *game);

#endif