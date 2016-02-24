//Autores: George Rappel e Ingrid Pacheco
//Data: 24/06/2015

#ifndef ALIEN_H
#define ALIEN_H

#define VELOCIDADE_ALIEN 2
#define VELOCIDADE_DESCIDA 3
#define ALTURA_ALIEN 29
#define LARGURA_ALIEN 45

typedef struct ALLEGRO_BITMAP ALLEGRO_BITMAP;
enum DIRECAO_ALIEN {A_DIREITA, A_ESQUERDA, A_BAIXO};

struct Alien {
  ALLEGRO_BITMAP* bitmap[1];
  int altura, largura;
  int min_x, max_x;
  int min_y, max_y;
  bool vivo;
  DIRECAO_ALIEN direcao;
};

void inicializa_alien(Alien* a, int x, int y, int num_imagem);

void finaliza_alien(Alien* a);

void desenha_alien(Alien *a);

void move_alien(Alien *a);

void desce_alien(Alien *a);

void muda_direcao_alien(Alien *a);

void explode_alien(Alien *a);

#endif
