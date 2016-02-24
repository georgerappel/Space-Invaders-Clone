//Autores: George Rappel e Ingrid Pacheco
//Data: 24/06/2015

#include "navemae.h"

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <stdio.h>

void inicializa_nave_mae(NaveMae* navemae, int x, int y){
	navemae->bitmap[0] = al_load_bitmap("imagens/navemae1(1).png");
	navemae->bitmap[1] = al_load_bitmap("imagens/navemae2(1).png");
	navemae->bitmap[2] = al_load_bitmap("imagens/navemae3(1).png");
	navemae->bitmap[3] = al_load_bitmap("imagens/navemae4(1).png");
	navemae->vidas = 4;
	navemae->vivo = true;
	navemae->min_x = x;
	navemae->min_y = y;
	navemae->max_x = x + LARGURA_NAVEMAE;
	navemae->max_y = y + ALTURA_NAVEMAE;
	navemae->direcao = NM_DIREITA;
	navemae->altura = ALTURA_NAVEMAE;
	navemae->largura = LARGURA_NAVEMAE;
	navemae->velocidade = VELOCIDADE_NAVEMAE;
	if( !navemae->bitmap[0] || !navemae->bitmap[1] || !navemae->bitmap[2] || !navemae->bitmap[3]) {
	    printf( "Erro ao carregar uma das imagens da navemae\n");
	    exit(-1);
  	}
}

void finaliza_nave_mae(NaveMae *navemae){
  al_destroy_bitmap( navemae->bitmap[0] );
  al_destroy_bitmap( navemae->bitmap[1] );
  al_destroy_bitmap( navemae->bitmap[2] );
  al_destroy_bitmap( navemae->bitmap[3] );
}

void desenha_nave_mae(NaveMae *navemae){
	if(navemae->vivo){
		move_nave_mae(navemae);
		al_draw_bitmap(navemae->bitmap[4 - navemae->vidas], navemae->min_x, navemae->min_y, 0);
	}
}

void move_nave_mae(NaveMae *navemae){
	if(navemae->vivo){
		switch(navemae->direcao){
			case NM_DIREITA:
					navemae->min_x += VELOCIDADE_NAVEMAE;
					navemae->max_x += VELOCIDADE_NAVEMAE;
					if(navemae->max_x > 820)
						muda_direcao_nave_mae(navemae);
				break;
			case NM_ESQUERDA:
					navemae->min_x -= VELOCIDADE_NAVEMAE;
					navemae->max_x -= VELOCIDADE_NAVEMAE;
					if(navemae->min_x < -250)
						muda_direcao_nave_mae(navemae);
				break;
		}
	}
}

void muda_direcao_nave_mae(NaveMae *navemae){
	if(navemae->vivo){
		switch(navemae->direcao){
			case NM_DIREITA:
				navemae->direcao = NM_ESQUERDA;
				break;
			case NM_ESQUERDA:
				navemae->direcao = NM_DIREITA;
			break;
		}
	}
}

int testar_colisao_navemae(NaveMae* navemae, Tiro* tiro){
  int navemae_destruida = 0;
  if(tiro->ativo == ATIVO)
    if(navemae->vivo){
        if(navemae->min_x < tiro->x && navemae->max_x > tiro->x){
            if(navemae->min_y < tiro->y && navemae->max_y > tiro->y){
              navemae->vidas--;              
            	tiro->ativo = NAO_ATIVO;
              if(!navemae->vidas){
              	navemae_destruida = 1;
              	navemae->vivo = false;
              }
            }
        }
    }
  return navemae_destruida;
}

void explode_nave_mae(NaveMae *navemae){
	navemae->vivo = false;
}
