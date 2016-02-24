//Autores: George Rappel e Ingrid Pacheco
//Data: 22/06/2015

#ifndef TANQUE_H
#define TANQUE_H

#include "tiro.h"

#define ALTURA_TANQUE 35
#define LARGURA_TANQUE 64
#define VELOCIDADE_TANQUE 3

typedef struct ALLEGRO_BITMAP ALLEGRO_BITMAP;
enum DIRECAO {DIREITA, ESQUERDA};

struct Tanque {
  int posicao_x, posicao_y;
  int altura, largura;
  Tiro tiro;
  ALLEGRO_BITMAP* bitmap;
};

void inicializa_tanque( Tanque* t, int x, int y);

void mudar_posicao_tanque(Tanque *t);

void finaliza_tanque( Tanque* t );

void desenha_tanque(Tanque *t);

void move_tanque(Tanque *t, DIRECAO direcao);

bool testa_colisao_tanque(Tanque *t, Tiro *tiro);

#endif
