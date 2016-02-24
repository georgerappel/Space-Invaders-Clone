//Autores: George Rappel e Ingrid Pacheco
//Data: 24/06/2015

#include "tanque.h"

#include <stdbool.h>
#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>

void inicializa_tanque( Tanque* t, int x, int y){
	t->posicao_x = x;
	t->posicao_y = y;
	t->bitmap = al_load_bitmap("imagens/tank.png");
	t->altura = ALTURA_TANQUE;
	t->largura = LARGURA_TANQUE;
	if( t->bitmap == NULL) {
	    puts( "Erro ao carregar o arquivo imagens/tank.png");
	    exit(0);
  	}
}

void finaliza_tanque(Tanque *t){
  al_destroy_bitmap( t->bitmap );
}

void desenha_tanque(Tanque *t){
	al_draw_bitmap(t->bitmap, t->posicao_x, t->posicao_y, 0);
}

void move_tanque(Tanque *t, DIRECAO direcao){
	switch(direcao){
		case DIREITA:
			// Condicao para prevenir que o tanque bata nas bordas
			if(t->posicao_x < 640 - (VELOCIDADE_TANQUE + 2) - LARGURA_TANQUE)
				t->posicao_x += VELOCIDADE_TANQUE;
		  break;
		case ESQUERDA:
			if(t->posicao_x > VELOCIDADE_TANQUE + 2)
			t->posicao_x -= VELOCIDADE_TANQUE;
			break;
	}
	desenha_tanque(t);
}

void mudar_posicao_tanque(Tanque *t){
	
	if(t->posicao_x > 200){
		t->posicao_x = t->posicao_x - ((rand()%50) + 100);
	}
	else{
		t->posicao_x = t->posicao_x + ((rand()%50) + 100);
	}
}


bool testa_colisao_tanque(Tanque *t, Tiro *tiro){
	bool acertou = false;
  if(tiro->ativo == ATIVO)
    if(tiro->x > t->posicao_x && tiro->x < t->posicao_x + t->largura)
      if(tiro->y + 10 > t->posicao_y && tiro->y + 10 < t->posicao_y + t->altura){
        tiro->ativo = NAO_ATIVO;
        acertou = true;
      }

	return acertou;
}
