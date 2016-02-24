//Autores: George Rappel e Ingrid Pacheco
//Data: 24/06/2015

#ifndef NAVEMAE_H
#define NAVEMAE_H

#define VELOCIDADE_NAVEMAE 2
#define ALTURA_NAVEMAE 32
#define LARGURA_NAVEMAE 123
#include "tiro.h"

typedef struct NaveMae NaveMae;

enum DIRECAO_NAVEMAE {NM_DIREITA, NM_ESQUERDA};

struct NaveMae {
  ALLEGRO_BITMAP* bitmap[4];
  int vidas;
  int altura, largura;
  int min_x, max_x;
  int min_y, max_y;
  bool vivo;
  int velocidade;
  DIRECAO_NAVEMAE direcao;
};

void inicializa_nave_mae(NaveMae* navemae, int x, int y);

void finaliza_nave_mae(NaveMae* navemae);

void desenha_nave_mae(NaveMae *navemae);

void move_nave_mae(NaveMae *navemae);

void muda_direcao_nave_mae(NaveMae *navemae);

void explode_nave_mae(NaveMae *navemae);

int testar_colisao_navemae(NaveMae *navemae, Tiro *tiro);

#endif