//Autores: George Rappel e Ingrid Pacheco
//Data: 26/06/2015

#include <stdbool.h>
#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>

#include "tiro.h"

void iniciar_tiro(Tiro *t, ATIRADOR atirador)
{
    t->ativo = NAO_ATIVO;
    t->x = 0;
    t->y = 0;
    if(atirador == ALIEN){
      t->vel = -(VEL_TIRO - 1);
      t->img_tiro = al_load_bitmap("imagens/tiro2.png");
    }
    else {
        if(atirador == NAVEMAE){
            t->img_tiro = al_load_bitmap("imagens/tiro3.png");
            t->vel = VEL_TIRO;
        }
        else{
            t->img_tiro = al_load_bitmap("imagens/tiro1.png");
            t->vel = VEL_TIRO;
        }
    }
    if( t->img_tiro == NULL) {
        puts( "Erro ao carregar a imagem do tiro.");
        exit(0);
    }
}

void aumenta_vel_tiro(Tiro *t, ATIRADOR atirador)
{
    if (atirador == TANQUE)
        t->vel = t->vel + 2;
    else
        t->vel = t->vel;
}

void desenha_tiro(Tiro *t)
{
    if (t->ativo == ATIVO)
    {
        al_draw_bitmap(t->img_tiro, t->x, t->y, 0);
        if (t->y > 0 && t->y < 640){
           t->y -= t->vel;
        } else {
          t->ativo = NAO_ATIVO;
        }
    }
}

void atirar(Tiro* tiro, int x, int y)
{
    if (tiro->ativo == NAO_ATIVO)
    {
        tiro->ativo = ATIVO;
        tiro->x = x;
        tiro->y = y;
        desenha_tiro(tiro);
    }
}