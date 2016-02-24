//Autores: George Rappel e Ingrid Pacheco
//Data: 24/06/2015

#include "alien.h"

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <stdio.h>

void inicializa_alien(Alien* a, int x, int y, int num_imagem){
	switch(num_imagem){
		case 1: a->bitmap[0] = al_load_bitmap("imagens/alien1.png"); break;
		case 2: a->bitmap[0] = al_load_bitmap("imagens/alien2.png"); break;
		case 3: a->bitmap[0] = al_load_bitmap("imagens/alien3.png"); break;
		case 4: a->bitmap[0] = al_load_bitmap("imagens/alien4.png"); break;
		case 5: a->bitmap[0] = al_load_bitmap("imagens/alien5.png"); break;
		case 6: a->bitmap[0] = al_load_bitmap("imagens/alien6.png"); break;
	}
	a->vivo = true;
	a->min_x = x;
	a->min_y = y;
	a->max_x = x + LARGURA_ALIEN;
	a->max_y = y + ALTURA_ALIEN;
	a->direcao = A_DIREITA;
	a->altura = ALTURA_ALIEN;
	a->largura = LARGURA_ALIEN;
	if( a->bitmap[0] == NULL) {
	    printf( "Erro ao carregar o arquivo imagens/alien%d.png\n", num_imagem);
	    exit(-1);
  }
}

void finaliza_alien(Alien *a){
  al_destroy_bitmap( a->bitmap[0] );
}

void desenha_alien(Alien *a){
	if(a->vivo)
		al_draw_bitmap(a->bitmap[0], a->min_x, a->min_y, 0);
}

void move_alien(Alien *a){
	if(a->vivo){
		switch(a->direcao){
			case A_DIREITA:
					a->min_x += VELOCIDADE_ALIEN;
					a->max_x += VELOCIDADE_ALIEN;
				break;
			case A_ESQUERDA:
					a->min_x -= VELOCIDADE_ALIEN;
					a->max_x -= VELOCIDADE_ALIEN;
				break;
		}
	}
}

void muda_direcao_alien(Alien *a){
	if(a->vivo){
		desce_alien(a);
		switch(a->direcao){
			case A_DIREITA:
				a->direcao = A_ESQUERDA;
				break;
			case A_ESQUERDA:
				a->direcao = A_DIREITA;
			break;
		}
	}
}

void desce_alien(Alien *a){
	a->min_y += VELOCIDADE_DESCIDA;
	a->max_y += VELOCIDADE_DESCIDA;
}

void explode_alien(Alien *a){
	a->vivo = false;
}