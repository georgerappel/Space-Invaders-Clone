//Autores: George Rappel e Ingrid Pacheco
//Data: 22/06/2015

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <stdio.h>

#include "bunker.h"

void inicializa_bunker( Bunker *bunker, int posicao_x, int posicao_y ) {
  bunker->posicao_x = posicao_x;
  bunker->posicao_y = posicao_y;
  
  for( int i = 0; i < 8; i++ )
    for( int j = 0; j < 4; j++ ) {
      bunker->pedaco[i][j] = INTEIRO;
      bunker->desenho[i][j] = QUADRADO;
    }
  bunker->desenho[0][0] = INFERIOR_DIREITO;    
  bunker->desenho[7][0] = INFERIOR_ESQUERDO;    
  bunker->desenho[2][2] = SUPERIOR_ESQUERDO;    
  bunker->desenho[5][2] = SUPERIOR_DIREITO;  
  bunker->desenho[2][3] = VAZIO;
  bunker->desenho[3][3] = VAZIO;
  bunker->desenho[3][2] = VAZIO;
  bunker->desenho[4][3] = VAZIO;
  bunker->desenho[4][2] = VAZIO;
  bunker->desenho[5][3] = VAZIO;
}  

void finaliza_bunker( Bunker *bunker ) {
  for( int i = 0; i < 8; i ++)
    for(int j = 0; j < 4; j++)
      bunker->desenho[i][j] = VAZIO;
}

void desenha_pedaco_bunker( int x, int y, LegoBunker lego, EstadoBunker estado ) {	     
  if (estado != DESTRUIDO){
    ALLEGRO_BITMAP* imagem = NULL;
    switch( lego ) {
      case VAZIO:
           break;
      case QUADRADO:
        if (estado == AVARIADO)
          imagem = al_load_bitmap("imagens/q-1.png");
        else 
          imagem = al_load_bitmap("imagens/q-0.png");
        al_draw_bitmap(imagem,x,y,0);
        break;
      
      case INFERIOR_DIREITO:
        if (estado == AVARIADO)
          imagem = al_load_bitmap("imagens/id-1.png");
        else
          imagem = al_load_bitmap("imagens/id-0.png");
        al_draw_bitmap(imagem,x,y,0);
        break;

      case INFERIOR_ESQUERDO:
        if (estado == AVARIADO)
          imagem = al_load_bitmap("imagens/ie-1.png");
        else
          imagem = al_load_bitmap("imagens/ie-0.png");
        al_draw_bitmap(imagem,x,y,0);
        break;
      
      case SUPERIOR_ESQUERDO:
        if (estado == AVARIADO)
          imagem = al_load_bitmap("imagens/se-1.png");
        else
          imagem = al_load_bitmap("imagens/se-0.png");
        al_draw_bitmap(imagem,x,y,0);
        break;
      
      case SUPERIOR_DIREITO:
        if (estado == AVARIADO)
          imagem = al_load_bitmap("imagens/sd-1.png");
        else
          imagem = al_load_bitmap("imagens/sd-0.png");
        al_draw_bitmap(imagem,x,y,0);
        break;
    }
    al_destroy_bitmap(imagem);
  }
}
  
void desenha_bunker( Bunker* bunker ) {
  for( int i = 0, x = bunker->posicao_x; i < 8; i++, x += TAMANHO_BUNKER / 8 )
    for( int j = 0, y = bunker->posicao_y; j < 4; j++, y += TAMANHO_BUNKER / 8 )             
      desenha_pedaco_bunker( x, y, bunker->desenho[i][j], bunker->pedaco[i][j] );  
}

void testa_colisao_bunker(Bunker *bunker, Tiro *tiro){
  if(tiro->ativo == ATIVO)
    for (int i = 0; i < 4; i++)
     if(bunker[i].posicao_x < tiro->x && bunker[i].posicao_x + TAMANHO_BUNKER > tiro->x)
        if(bunker[i].posicao_y < tiro->y && bunker[i].posicao_y + 40 > tiro->y){
          int linha = (tiro->x - bunker[i].posicao_x)/10;
          int coluna = (tiro->y - bunker[i].posicao_y)/10;
          if(bunker[i].desenho[linha][coluna]!= VAZIO)
            if (bunker[i].pedaco[linha][coluna] != DESTRUIDO){
              if(bunker[i].pedaco[linha][coluna] == INTEIRO)
               bunker[i].pedaco[linha][coluna] = AVARIADO;
              else if(bunker[i].pedaco[linha][coluna] == AVARIADO)
                bunker[i].pedaco[linha][coluna] = DESTRUIDO;
              tiro->ativo = NAO_ATIVO;
              break;
            }
        }     
}