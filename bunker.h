//Autores: George Rappel e Ingrid Pacheco
//Data: 22/06/2015

#ifndef BUNKER_H
#define BUNKER_H
#define TAMANHO_BUNKER (8*10)

#include "tiro.h"

enum LegoBunker { VAZIO, QUADRADO, SUPERIOR_ESQUERDO, SUPERIOR_DIREITO, INFERIOR_ESQUERDO, INFERIOR_DIREITO };
enum EstadoBunker { INTEIRO, AVARIADO, DESTRUIDO };

struct Bunker {
  int posicao_x, posicao_y;
  ALLEGRO_BITMAP* imagens[8][4];
  LegoBunker desenho[8][4];
  EstadoBunker pedaco[8][4];
};

void inicializa_bunker( Bunker *bunker, int posicao_x, int posicao_y );

void finaliza_bunker( Bunker *bunker );

void desenha_bunker( Bunker *bunker );

void testa_colisao_bunker(Bunker *bunker, Tiro *tiro);

#endif


