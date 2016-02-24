//Autores: George Rappel e Ingrid Pacheco
//Data: 26/06/2015

#ifndef TIRO_H
#define TIRO_H

#define VEL_TIRO 8

typedef struct ALLEGRO_BITMAP ALLEGRO_BITMAP;

enum ESTADO {ATIVO, NAO_ATIVO};

enum ATIRADOR {ALIEN, TANQUE, NAVEMAE};

struct Tiro
{
    int x, y;
    int vel;
    int ativo;
    ALLEGRO_BITMAP* img_tiro;
};

void iniciar_tiro(Tiro *t, ATIRADOR atirador);

void desenha_tiro(Tiro *t);

void atirar(Tiro* tiro, int x, int y);

void aumenta_vel_tiro(Tiro *t, ATIRADOR atirador);

#endif
