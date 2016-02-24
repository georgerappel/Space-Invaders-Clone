//Autores: George Rappel e Ingrid Pacheco
//Data: 26/06/2015

#include "aliens.h"
#include <stdio.h>

#define ESPACO_ALIENS 9

void inicializa_aliens(Aliens* aliens){
  aliens->posicao_y = 95;
  aliens->posicao_x = 80;
  aliens->direcao = A_DIREITA;
  aliens->n_vivos = N_LINHAS * N_COLUNAS;
  aliens->distancia_esquerda = aliens->posicao_x;
  aliens->distancia_direita = 640 - (aliens->posicao_x + (N_COLUNAS) * (LARGURA_ALIEN + ESPACO_ALIENS) - ESPACO_ALIENS);
  for(int i = 0; i < N_LINHAS; i++){ // Linhas
    for(int j = 0; j < N_COLUNAS; j++){ // Colunas
      inicializa_alien(&aliens->matriz_aliens[i][j], aliens->posicao_x + j*(LARGURA_ALIEN + ESPACO_ALIENS), aliens->posicao_y + i * (ALTURA_ALIEN + 11), i + 1);
    }
  }
}

void finaliza_aliens(Aliens* aliens){
  for(int i = 0; i < N_LINHAS; i++)
    for(int j = 0; j < N_COLUNAS; j++)
      finaliza_alien(&aliens->matriz_aliens[i][j]);
}


void move_aliens(Aliens* aliens){
  int mudou = 0;
  for(int i = 0; i < N_LINHAS; i++)
    for(int j = 0; j < N_COLUNAS; j++){
      if(aliens->distancia_direita < 15 || aliens->distancia_esquerda < 15){
        muda_direcao_alien(&aliens->matriz_aliens[i][j]);
        mudou = 1;
      }
      move_alien(&aliens->matriz_aliens[i][j]);
    }

  if(mudou)
    muda_direcao_aliens(aliens);

  switch(aliens->direcao){
    case A_DIREITA:
      aliens->distancia_esquerda += VELOCIDADE_ALIEN;
      aliens->distancia_direita -= VELOCIDADE_ALIEN;
    break;
    case A_ESQUERDA:
      aliens->distancia_esquerda -= VELOCIDADE_ALIEN;
      aliens->distancia_direita += VELOCIDADE_ALIEN;
    break;
  }
}

void desenha_aliens(Aliens *aliens){
  for(int i = 0; i < N_LINHAS; i++)
    for(int j = 0; j < N_COLUNAS; j++){
      if(aliens->matriz_aliens[i][j].vivo)
        desenha_alien(&aliens->matriz_aliens[i][j]);
    }
}

int testar_colisao_aliens(Aliens* aliens, Tiro* tiro){
  int alien_destruido = 0;
  if(tiro->ativo == ATIVO)
    for(int i = 0; i < N_LINHAS; i++)
      for(int j = 0; j < N_COLUNAS; j++)
        if(aliens->matriz_aliens[i][j].vivo)
          if(aliens->matriz_aliens[i][j].min_x < tiro->x && aliens->matriz_aliens[i][j].max_x > tiro->x)
            if(aliens->matriz_aliens[i][j].min_y < tiro->y && aliens->matriz_aliens[i][j].max_y > tiro->y){
              aliens->matriz_aliens[i][j].vivo = false;
              tiro->ativo = NAO_ATIVO;
              alien_destruido = i + 1;
              aliens->n_vivos--;
            }
  return alien_destruido;
}

int get_aliens_vivos(Aliens *aliens){
  return aliens->n_vivos;
}

void muda_direcao_aliens(Aliens* aliens){
  aliens->posicao_y += VELOCIDADE_DESCIDA;
  if(aliens->direcao == A_DIREITA)
    aliens->direcao = A_ESQUERDA;
  else
    aliens->direcao = A_DIREITA;
}