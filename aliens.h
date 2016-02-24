//Autores: George Rappel e Ingrid Pacheco
//Data: 26/06/2015

#ifndef ALIENS_H
#define ALIENS_H

#define N_COLUNAS 9
#define N_LINHAS 6

#include "alien.h"
#include "tiro.h"

typedef struct ALLEGRO_SAMPLE ALLEGRO_SAMPLE;

struct Aliens {
  Alien matriz_aliens[N_LINHAS][N_COLUNAS];
  int posicao_x;
  int posicao_y;
  int distancia_esquerda;
  int distancia_direita;
  int n_vivos;
  DIRECAO_ALIEN direcao;
};

void inicializa_aliens(Aliens* aliens);

void finaliza_aliens(Aliens* aliens);

void desenha_aliens(Aliens *aliens);

void move_aliens(Aliens* aliens);

int testar_colisao_aliens(Aliens* aliens, Tiro* tiro);

int get_aliens_vivos(Aliens *aliens);

void muda_direcao_aliens(Aliens* aliens);

#endif