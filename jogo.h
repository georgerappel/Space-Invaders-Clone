//Autores: George Rappel e Ingrid Pacheco
//Data: 22/06/2015

#ifndef JOGO_H
#define JOGO_H

#define ALTURA_JOGO 520
#define LARGURA_JOGO 640

#include "bunker.h"
#include "tanque.h"
#include "navemae.h"
#include "aliens.h"

#define N_TIROS_TANQUE 3
typedef struct ALLEGRO_FONT ALLEGRO_FONT;

struct Jogo {
	ALLEGRO_BITMAP* fundo;
	ALLEGRO_DISPLAY* display;
  ALLEGRO_FONT* fonte;
	ALLEGRO_EVENT_QUEUE* fila_eventos;
  ALLEGRO_SAMPLE* audio_fundo;
  Bunker bunker[4];
  Tanque tanque;
  Aliens aliens;
  Tiro tiro_tanque[N_TIROS_TANQUE];
  Tiro tiro_alien;
  Tiro tiro_navemae;
  NaveMae navemae;
  int vidas;
  int largura, altura;
  int pontuacao;
  bool som_ativo;
};

void inicializa_jogo( Jogo* jogo );

void reinicia_jogo(Jogo* jogo);

void proxima_fase(Jogo *jogo);

void finaliza_jogo( Jogo* jogo );

void desenha_jogo( Jogo* jogo );

void inicializa_objetos( Jogo* jogo);

void move_tanque_jogo(Jogo* jogo, DIRECAO direcao);

void loop_eventos_jogo(Jogo *jogo);

int ler_pontuacao();

void salvar_pontuacao(int pontuacao);

bool loop_pause(Jogo *jogo);

void tela_game_over(Jogo *jogo);

void mudar_musica_fundo(Jogo *jogo);

#endif

