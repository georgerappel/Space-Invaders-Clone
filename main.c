//Autores: George Rappel e Ingrid Pacheco
//Data: 22/06/2015

#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>

#include "jogo.h"

typedef struct ALLEGRO_BITMAP ALLEGRO_BITMAP;

struct Menu{
  ALLEGRO_BITMAP* bg[8];
  int img_atual;
};


void inicializa_menu(Menu *menu){
  menu->img_atual = 0;
  for(int i = 0; i < 8; i++)
    menu->bg[i] = NULL;
  menu->bg[0] = al_load_bitmap("imagens/menu/principal-1.jpg");
  menu->bg[1] = al_load_bitmap("imagens/menu/principal-2.jpg");
  menu->bg[2] = al_load_bitmap("imagens/menu/principal-3.jpg");
  menu->bg[3] = al_load_bitmap("imagens/menu/principal-4.jpg");
  menu->bg[4] = al_load_bitmap("imagens/menu/principal-5.jpg");
  menu->bg[5] = al_load_bitmap("imagens/menu/principal-6.jpg");
  menu->bg[6] = al_load_bitmap("imagens/menu/principal-7.jpg");
  menu->bg[7] = al_load_bitmap("imagens/menu/principal-8.jpg");

  for(int i = 0; i < 8; i++)
    if(!menu->bg[i]){
      printf("Erro ao carregar arquivo imagens/menu/principal-%d.jpg", i);
      exit(-1);
    }
  al_draw_bitmap(menu->bg[menu->img_atual], 0, 0, 0);
  al_flip_display();
}

void desenha_menu(Menu *menu, Jogo *jogo){
  menu->img_atual = (menu->img_atual + 1)%8;
  al_draw_bitmap(menu->bg[menu->img_atual], 0, 0, 0);
  al_draw_textf(jogo->fonte, al_map_rgb(255, 255, 255), 20, 15, ALLEGRO_ALIGN_LEFT, "M - MUTE/UNMUTE");
  al_draw_textf(jogo->fonte, al_map_rgb(255, 255, 255), 600, 480, ALLEGRO_ALIGN_RIGHT, "Feito por George Rappel e Ingrid Pacheco");
  al_flip_display();
  al_rest(0.15);
}

void finaliza_menu(Menu *menu){
  al_destroy_bitmap(menu->bg[0]);  
  al_destroy_bitmap(menu->bg[1]);
  al_destroy_bitmap(menu->bg[2]);
  al_destroy_bitmap(menu->bg[3]);
  al_destroy_bitmap(menu->bg[4]);
  al_destroy_bitmap(menu->bg[5]);
  al_destroy_bitmap(menu->bg[6]);
  al_destroy_bitmap(menu->bg[7]);
}

int main(int argc, char **argv){
  bool sair = false;
	Jogo jogo;
  Menu menu;

	inicializa_jogo(&jogo);
  inicializa_menu(&menu);

  while(!sair){
      desenha_menu(&menu,&jogo);
      if( !al_is_event_queue_empty(jogo.fila_eventos) ){
        ALLEGRO_EVENT ev;
        al_wait_for_event(jogo.fila_eventos, &ev);
        if(ev.type == ALLEGRO_EVENT_KEY_DOWN){
          switch(ev.keyboard.keycode){
            case ALLEGRO_KEY_ENTER:
              reinicia_jogo( &jogo );
              // Iniciar o jogo
              finaliza_menu(&menu);
              desenha_jogo( &jogo );
              loop_eventos_jogo(&jogo);
              //Ao fim da execucao do loop de eventos
              inicializa_menu(&menu);
            break;
            case ALLEGRO_KEY_ESCAPE:
              // Sai do jogo
              sair = true;
            break;
            case ALLEGRO_KEY_M:
              mudar_musica_fundo(&jogo);
            break;
          }
        } else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
          sair = true;
        }
    }
  }
  finaliza_menu(&menu);
	finaliza_jogo(&jogo);

	return 0;
}
