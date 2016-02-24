//Autores: George Rappel e Ingrid Pacheco
//Data: 22/06/2015

#include <stdlib.h>
#include <stdio.h>

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

#include "jogo.h"

enum TECLAS {KEY_LEFT, KEY_RIGHT, KEY_SPACE};

int movimento_aliens = 1;
int max_movimento = 4;
int pontuacao_alta;

ALLEGRO_SAMPLE *audio_tiro = NULL;
ALLEGRO_SAMPLE *audio_explosao_alien = NULL;
ALLEGRO_SAMPLE *audio_explosao_tanque = NULL;
ALLEGRO_BITMAP *vida = NULL;

void inicializa_jogo( Jogo* jogo ) {

  if(!al_init()) {
    fprintf(stderr, "Falha ao inicializar o Allegro!\n");
    exit(-1);
  }

  if (!al_init_primitives_addon()) {
    fprintf(stderr, "Falha ao inicializar add-on de primitivas.\n");
    exit(-1);
  }

  if (!al_init_image_addon()) {
    fprintf(stderr, "Falha ao inicializar add-on de imagens.\n");
    exit(-1);
  }

  // ====== INICIALIZAÇÃO DO DISPLAY ======= //
  jogo->display = al_create_display( LARGURA_JOGO, ALTURA_JOGO );
  if(!jogo->display) {
    fprintf(stderr, "Falha ao criar o display!\n");
    exit(-1);
  }
  ALLEGRO_BITMAP *icone = NULL;
  icone = al_load_bitmap("imagens/icone.png");
  al_set_display_icon(jogo->display, icone);
  al_set_window_title(jogo->display, "Space Invaders");

  // ======== INICIALIZACAO DO AUDIO ======== //
  if(!al_install_audio()){
    puts("Falha ao iniciar o audio.");
    exit(-1);
  } 
  if(!al_init_acodec_addon()){
    puts("Falha ao iniciar os codecs de audio.");
    exit(-1);
  } 
  if (!al_reserve_samples(4)){
    puts("Falha ao resevar samples.");
    exit(-1);
  }
  audio_tiro = al_load_sample( "audio/tiro.wav" ); 
  if (!audio_tiro){
    puts( "Erro no carregamento do arquivo de audio do tiro."); 
    exit(-1);
  }
  audio_explosao_alien = al_load_sample( "audio/explosao_alien.wav" ); 
  if (!audio_explosao_alien){
    puts( "Erro no carregamento do arquivo de audio da explosao."); 
    exit(-1);
  }
  jogo->audio_fundo = al_load_sample( "audio/BlackVortex.ogg" ); 
  if (!audio_explosao_alien){
    puts( "Erro no carregamento do arquivo de audio de fundo."); 
    exit(-1);
  }
  audio_explosao_tanque = al_load_sample ( "audio/explosao_player.wav");
  if(!audio_explosao_tanque){
    puts("Erro no carregamento do arquivo de audio da explosao do player.");
    exit(-1);
  }
  al_play_sample(jogo->audio_fundo, 0.8, 0.0, 1.0,ALLEGRO_PLAYMODE_LOOP,NULL);

  // ======== INICIALIZAÇÃO DA FONTE ========= //
  al_init_font_addon();
  if (!al_init_ttf_addon()){
    puts("Falha ao inicializar add-on de fontes TrueType.");
    exit(-1);
  }
  jogo->fonte = al_load_font("fontes/04B.TTF", 24, 0);
  if (!jogo->fonte){
    puts("Falha ao inicializar a fonte especificada.");
    exit(-1);
  }

  // ======== INICIALIZACAO DOS EVENTOS ======== //
  if(!al_install_keyboard()){
    puts("Erro na inicialização do teclado.");
    exit(-1);
  }

  jogo->fila_eventos = al_create_event_queue();
  if(!jogo->fila_eventos) {
    puts("Falha na inicialização da fila de eventos.\n");
    exit(-1);
  }

  vida = al_load_bitmap("imagens/tank-vida.png");
  if(!vida){
    puts("Erro ao carregar icone de vida.");
    exit(-1);
  }

  jogo->fundo = al_load_bitmap("imagens/background.jpg");
  al_draw_bitmap(jogo->fundo, 0, 0, 0);
  jogo->pontuacao = 0;
  jogo->vidas = 3;
  jogo->altura = ALTURA_JOGO;
  jogo->largura = LARGURA_JOGO;
  jogo->som_ativo = true;
  inicializa_objetos(jogo);
  
  al_register_event_source(jogo->fila_eventos, al_get_display_event_source(jogo->display));
  al_register_event_source(jogo->fila_eventos, al_get_keyboard_event_source());
}

void inicializa_objetos(Jogo* jogo){
  for( int i = 0, x = (jogo->largura/4 - TAMANHO_BUNKER)/2 + 10; 
    i < 4; 
    i++, x += jogo->largura / 4 - 6) {
    inicializa_bunker( &jogo->bunker[i], x, 410 );
  }
  inicializa_tanque(&jogo->tanque, jogo->largura /2 - LARGURA_TANQUE/2, 475);
  inicializa_aliens(&jogo->aliens);
  for(int i = 0; i < N_TIROS_TANQUE; i++)
    iniciar_tiro(&jogo->tiro_tanque[i], TANQUE);
  iniciar_tiro(&jogo->tiro_alien, ALIEN);
  iniciar_tiro(&jogo->tiro_navemae, NAVEMAE);
  desenha_aliens(&jogo->aliens);
  inicializa_nave_mae(&jogo->navemae, 20, 70);
}

void reinicia_jogo(Jogo* jogo){
  pontuacao_alta = ler_pontuacao();
  movimento_aliens = 1;
  max_movimento = 4;
  if(jogo->vidas < 3)
    jogo->vidas++;
  inicializa_objetos(jogo);
}

void proxima_fase(Jogo *jogo){
  movimento_aliens = 1;
  max_movimento = 4;
  if(jogo->vidas < 3)
    jogo->vidas++;
  for(int i = 0; i < N_TIROS_TANQUE; i++)
    aumenta_vel_tiro(&jogo->tiro_tanque[i],TANQUE);
  inicializa_tanque(&jogo->tanque, jogo->largura /2 - LARGURA_TANQUE/2, 475);
  inicializa_aliens(&jogo->aliens);
}

void finaliza_jogo( Jogo* jogo ) {
  for( int i = 0; i < 4; i++ )
    finaliza_bunker( &jogo->bunker[i] );
  finaliza_aliens(&jogo->aliens);
  finaliza_tanque(&jogo->tanque);
  finaliza_nave_mae(&jogo->navemae);
  al_destroy_bitmap(jogo->fundo);
  al_destroy_display( jogo->display );
  al_destroy_event_queue(jogo->fila_eventos);
  al_destroy_bitmap(vida);
  al_destroy_sample(jogo->audio_fundo);
  al_destroy_sample(audio_tiro);
  al_destroy_sample(audio_explosao_alien);
  al_destroy_sample(audio_explosao_tanque);
}

void desenha_jogo( Jogo* jogo ) {
  al_draw_bitmap(jogo->fundo, 0, 0, 0);  

  al_draw_textf(jogo->fonte, al_map_rgb(255, 255, 255), 20, 15, ALLEGRO_ALIGN_LEFT, "SCORE:");
  al_draw_textf(jogo->fonte, al_map_rgb(255, 255, 255), LARGURA_JOGO/2 - 60, 15, ALLEGRO_ALIGN_LEFT, "HI-SCORE:");
  al_draw_textf(jogo->fonte, al_map_rgb(255, 255, 255), LARGURA_JOGO - 35, 15, ALLEGRO_ALIGN_RIGHT, "LIFES:");
  al_draw_textf(jogo->fonte, al_map_rgb(255, 255, 255), 18, 38, ALLEGRO_ALIGN_LEFT, "%05d", jogo->pontuacao);
  al_draw_textf(jogo->fonte, al_map_rgb(255, 255, 255), LARGURA_JOGO/2 - 40, 38, ALLEGRO_ALIGN_LEFT, "%05d", pontuacao_alta);
  for( int i = 0; i < 4; i++ )
    desenha_bunker( &jogo->bunker[i] );

  // ======= TESTES DE COLISÃO ======== //
  if(testa_colisao_tanque(&jogo->tanque, &jogo->tiro_alien)){
    jogo->vidas--;
    if(jogo->som_ativo)
      al_play_sample(audio_explosao_tanque, 0.7, 0.0, 1.5,ALLEGRO_PLAYMODE_ONCE,NULL);
  }
  for(int i = 0; i < N_TIROS_TANQUE; i++){
    int alien_explodiu = testar_colisao_aliens(&jogo->aliens, &jogo->tiro_tanque[i]);
    int navemae_explodiu = testar_colisao_navemae(&jogo->navemae, &jogo->tiro_tanque[i]);
    if(alien_explodiu){
      jogo->pontuacao += (7 - alien_explodiu) * 10;
      if(jogo->som_ativo)
        al_play_sample(audio_explosao_alien, 0.7, 0.0, 1.0,ALLEGRO_PLAYMODE_ONCE,NULL);
    }    
    if(navemae_explodiu){
      jogo->pontuacao += (150);
      if(jogo->som_ativo)
        al_play_sample(audio_explosao_alien,1.0,0.0,1.0,ALLEGRO_PLAYMODE_ONCE,NULL);
    }
    testa_colisao_bunker(&jogo->bunker[0], &jogo->tiro_tanque[i]);
  }
  testa_colisao_bunker(&jogo->bunker[0], &jogo->tiro_alien);
  testa_colisao_bunker(&jogo->bunker[0], &jogo->tiro_navemae);

  // ======== DESENHAR E MOVIMENTAR ========= //
  if(jogo->vidas)
    desenha_tanque(&jogo->tanque);  
  for(int i = 0; i < jogo->vidas; i++){
    al_draw_bitmap(vida, 590 - i*33, 38, 0);
  }
  if(jogo->aliens.posicao_y > 120)
    desenha_nave_mae(&jogo->navemae);
  for(int i = 0; i < N_TIROS_TANQUE; i++)
    desenha_tiro(&jogo->tiro_tanque[i]);
  desenha_tiro(&jogo->tiro_alien);
  desenha_tiro(&jogo->tiro_navemae);
  desenha_aliens(&jogo->aliens);
  if(movimento_aliens % max_movimento == 0){
    move_aliens(&jogo->aliens);
  }
  if(movimento_aliens % 900 == 0){
    movimento_aliens == 1; 
    if(max_movimento > 2)
      max_movimento--;
  }
  movimento_aliens++;
  al_flip_display();
}

void timer_imagem_inicial(Jogo* jogo){
  ALLEGRO_BITMAP* img_tempo = NULL;
  img_tempo = al_load_bitmap("imagens/timer2.png");
  if(!img_tempo){
    puts("Erro ao carregar imagem do timer.");
    exit(-1);
  }
  desenha_jogo(jogo);
  al_draw_bitmap(img_tempo, LARGURA_JOGO/2 - 128, ALTURA_JOGO/2 - 128, 0);
  al_flip_display();
  al_rest(1);
  img_tempo = al_load_bitmap("imagens/timer1.png");
  if(!img_tempo){
    puts("Erro ao carregar imagem do timer.");
    exit(-1);
  }
  desenha_jogo(jogo);
  al_draw_bitmap(img_tempo, LARGURA_JOGO/2 - 128, ALTURA_JOGO/2 - 128, 0);
  al_flip_display();
  al_rest(1);
  img_tempo = al_load_bitmap("imagens/timer0.png");
  if(!img_tempo){
    puts("Erro ao carregar imagem do timer.");
    exit(-1);
  }
  desenha_jogo(jogo);
  al_draw_bitmap(img_tempo, LARGURA_JOGO/2 - 128, ALTURA_JOGO/2 - 128, 0);
  al_flip_display();
  al_rest(0.5);
  al_destroy_bitmap(img_tempo);
}

void move_tanque_jogo(Jogo* jogo, DIRECAO direcao){
  move_tanque(&jogo->tanque, direcao);
}

void loop_eventos_jogo(Jogo *jogo){
  bool game_over = false;
  bool sair = false;
  bool seta[2] = {false, false};
  srand(time(NULL));

  timer_imagem_inicial(jogo);
  while(!sair && !game_over){
    if(rand()%45 < 3){
      int linha = rand()%6;
      int coluna = rand()%9;
      if(jogo->aliens.matriz_aliens[linha][coluna].vivo)
        atirar(&jogo->tiro_alien, jogo->aliens.matriz_aliens[linha][coluna].min_x + LARGURA_ALIEN/2, jogo->aliens.matriz_aliens[linha][coluna].max_y);
    }
    desenha_jogo(jogo);
    if(!get_aliens_vivos(&jogo->aliens)){
      // Todos os aliens morreram
      proxima_fase(jogo);
    }
    if(!jogo->vidas){
      game_over = true;
    }
    if( !al_is_event_queue_empty(jogo->fila_eventos) ){

      ALLEGRO_EVENT ev;
      al_wait_for_event(jogo->fila_eventos, &ev);

      if(ev.type == ALLEGRO_EVENT_KEY_DOWN)
        switch(ev.keyboard.keycode){
          case ALLEGRO_KEY_RIGHT: seta[KEY_RIGHT] = true; break;
          case ALLEGRO_KEY_LEFT: seta[KEY_LEFT] = true; break;
          case ALLEGRO_KEY_P: sair = loop_pause(jogo); break;
          case ALLEGRO_KEY_ESCAPE: sair = loop_pause(jogo); break;          
          case ALLEGRO_KEY_M: mudar_musica_fundo(jogo); break;
          case ALLEGRO_KEY_EQUALS: mudar_posicao_tanque(&jogo->tanque); break;
          case ALLEGRO_KEY_PAD_PLUS: mudar_posicao_tanque(&jogo->tanque); break;
          case ALLEGRO_KEY_SPACE:
            for(int i = 0; i < N_TIROS_TANQUE; i++)
              if(jogo->tiro_tanque[i].ativo == NAO_ATIVO){
                atirar(&jogo->tiro_tanque[i], jogo->tanque.posicao_x + LARGURA_TANQUE/2, jogo->tanque.posicao_y);
                if(jogo->som_ativo)
                  al_play_sample(audio_tiro, 0.7, 0.0, 1.0,ALLEGRO_PLAYMODE_ONCE,NULL);
                break;
              }
          break;
        }
      else if (ev.type == ALLEGRO_EVENT_KEY_UP)
        switch(ev.keyboard.keycode){
          case ALLEGRO_KEY_RIGHT: seta[KEY_RIGHT] = false; break;
          case ALLEGRO_KEY_LEFT: seta[KEY_LEFT] = false; break;
        }

      if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
        sair = true;
      }
    }

    if(seta[KEY_RIGHT]){
      move_tanque_jogo(jogo, DIREITA);
    } else if(seta[KEY_LEFT]){
      move_tanque_jogo(jogo, ESQUERDA);
    }
  }
  // Fim de jogo
  salvar_pontuacao(jogo->pontuacao);
  if(game_over){
    tela_game_over(jogo);
  }

  jogo->pontuacao = 0;
  jogo->vidas = 3;
}

int ler_pontuacao(){
  FILE *fp;
  int valor;
  fp=fopen("pontuacao.txt", "r");
  if( fp == NULL ){
    printf("Erro ao abrir arquivo para leitura.\n");
    fp=fopen("pontuacao.txt", "w+");
    if (fp == NULL){
      printf("Erro ao abrir arquivo para leitura.\n");
      return 0;
    }
    fclose(fp);
    return 0;
  }
  fscanf(fp, "%d", &valor);
  fclose(fp);
  return valor;
}

void salvar_pontuacao(int pontuacao){
  if(ler_pontuacao() < pontuacao){
    FILE *fp;
    fp=fopen("pontuacao.txt", "w+");
    if( fp == NULL ){
      printf("Erro ao abrir arquivo para escrita.\n");
      exit(-1);
    }
    fprintf(fp, "%d", pontuacao);
    fclose(fp);
  }
}

bool loop_pause(Jogo *jogo){
  bool sair_pause = false;
  bool sair_jogo = false;
  ALLEGRO_BITMAP *bg_pause = NULL;
  bg_pause = al_load_bitmap("imagens/bg_pause.png");
  if(!bg_pause){
    puts("Erro ao carregar tela de pause.");
    exit(-1);
  }
  al_draw_bitmap(bg_pause, 0, 0, 0);
  al_stop_samples();
  al_flip_display();
  while(!sair_pause){
    ALLEGRO_EVENT ev;
    al_wait_for_event(jogo->fila_eventos, &ev);
    if(ev.type == ALLEGRO_EVENT_KEY_DOWN)
      switch(ev.keyboard.keycode){
        case ALLEGRO_KEY_P:
          sair_pause = true;
        break;
        case ALLEGRO_KEY_ESCAPE:
          sair_jogo = true;
          sair_pause = true;
        break;              
        case ALLEGRO_KEY_M: mudar_musica_fundo(jogo); break;
      }
      if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
        sair_jogo = true;
        sair_pause = true;
      }
  }
  al_destroy_bitmap(bg_pause);
  jogo->audio_fundo = al_load_sample( "audio/BlackVortex.ogg" );
  al_play_sample(jogo->audio_fundo, 0.8, 0.0, 1.0,ALLEGRO_PLAYMODE_LOOP,NULL);
  return sair_jogo;
}

void tela_game_over(Jogo *jogo){
  bool sair = false;
  ALLEGRO_BITMAP *bg = NULL;
  bg = al_load_bitmap("imagens/bg_game_over.png");
  pontuacao_alta = ler_pontuacao();
  int red = 255, blue = 255;
  if(jogo->pontuacao == pontuacao_alta){
    red = 0;
    blue = 0;
  }
  al_draw_bitmap(bg, 0, 0, 0);
  al_draw_textf(jogo->fonte, al_map_rgb(red, 255, blue), LARGURA_JOGO/2 - 40, 210, ALLEGRO_ALIGN_LEFT, "%05d", jogo->pontuacao);
  al_draw_textf(jogo->fonte, al_map_rgb(red, 255, blue), LARGURA_JOGO/2 - 40, 320, ALLEGRO_ALIGN_LEFT, "%05d", pontuacao_alta);
  al_flip_display();
  while(!sair){
    if( !al_is_event_queue_empty(jogo->fila_eventos) ){

      ALLEGRO_EVENT ev;
      al_wait_for_event(jogo->fila_eventos, &ev);

      if(ev.type == ALLEGRO_EVENT_KEY_DOWN)
        switch(ev.keyboard.keycode){
          case ALLEGRO_KEY_ESCAPE: sair = true; break;
          case ALLEGRO_KEY_ENTER: sair = true; break;
        }
      if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
        sair = true;
      }
    }
  }
  al_destroy_bitmap(bg);
}

void mudar_musica_fundo(Jogo *jogo){
if(jogo->som_ativo == true){
  al_stop_samples();
  jogo->som_ativo = false;
}
else{
  jogo->audio_fundo = al_load_sample( "audio/BlackVortex.ogg" );
  al_play_sample(jogo->audio_fundo, 0.8, 0.0, 1.0,ALLEGRO_PLAYMODE_LOOP,NULL);
  jogo->som_ativo = true;
}
}
