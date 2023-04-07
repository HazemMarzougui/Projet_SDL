#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_image.h>
#include "Entite.h"
#include "perso.h"

//Math
int mathSign(int x){
  return (x > 0) - (x < 0);
}

//Main functions
void initEnnemi(Ennemi e[]){
  for(int i = 0; i < 10; i++){
    e[i].hp = 1;
    e[i].type = 1;
    e[i].speed = 2;
    e[i].range = 20;
    e[i].sprite = IMG_Load("entity resources/Walk.png");
    e[i].spriteb = IMG_Load("entity resources/Walkb.png");
    e[i].posScreen.x = 100 + i * 100;
    e[i].posScreen.y = 150;
    e[i].RightBound = e[i].posScreen.x + 50;
    e[i].LeftBound = e[i].posScreen.x - 50;
    e[i].frame = 0;
    for(int j = 0; j < 4; j++){
      e[i].rect[j].x = j * 150;
      e[i].rect[j].y = 0;
      e[i].rect[j].h = 150;
      e[i].rect[j].w = 150;
    }
    e[i].Dir = 1;
  }
}

void afficherEnnemi(Ennemi e[], SDL_Surface * screen){
  for(int i = 0; i < 10; i++){
    if(e[i].Dir == 1){
      SDL_BlitSurface(e[i].sprite, &e[i].rect[e[i].frame], screen, &e[i].posScreen);
    }
    if(e[i].Dir == -1){
      SDL_BlitSurface(e[i].spriteb, &e[i].rect[e[i].frame], screen, &e[i].posScreen);
    }
  }
}

void deplacer(Ennemi e[]){
  int Detection = 0;
  for(int i = 0; i < 10; i++){
    switch(e[i].type){
      case 1:
        e[i].posScreen.x = e[i].posScreen.x + e[i].speed * e[i].Dir;
        if(e[i].posScreen.x >= e[i].RightBound){
          e[i].Dir = -1;
          e[i].frame = 0;
        }
        if(e[i].posScreen.x <= e[i].LeftBound){
          e[i].Dir = 1;
          e[i].frame = 0;
        }
        break;
      case 2:
        break;
      case 3:
        break;
      default:
        break;
    }
  }
}

int collisionBB( perso p, Ennemi e[]){
  int col = 0;
  for(int i = 0; i < 10; i++){
    if((abs(e[i].posScreen.x - p.posScreen.x) <= ((e[i].posScreen.w + 150) / 2))&&(abs(e[i].posScreen.y - p.posScreen.y) <= ((e[i].posScreen.h + 200) / 2))){ //Edit this cuz player instantly
      col = 1;
    }
    else col = 0;
  }
  printf("%d\n",col);
  return col;
}

void animerEnnemi(Ennemi e[]){
  for(int i = 0; i < 10; i++){
    e[i].frame++;
    SDL_Delay(1);
    if(e[i].frame > 4){
      e[i].frame = 0;
    }
  }
}

void Liberer(Ennemi e[]){
  for(int i = 0; i < 10; i++){
    SDL_FreeSurface(e[i].sprite);
    SDL_FreeSurface(e[i].spriteb);
  }
}

//One entity

void initEnnemiSimple(Ennemi * e, int i){
  e->hp = 1;
  e->type = 1;
  e->speed = 2;
  e->range = 50;
  e->sprite = IMG_Load("entity resources/Walk11.png");
  e->spriteb = IMG_Load("entity resources/Walkb11.png");
  
  if(i == 1){
  	e->posScreen.x = 400;
    e->posScreen.y = 530;
  }
  if(i == 2){
  	e->posScreen.x = 1700;
    e->posScreen.y = 530;
  }

  e->RightBound = e->posScreen.x + 40;
  e->LeftBound = e->posScreen.x - 40;
  e->frame = 0;
  for(int j = 0; j < 4; j++){
    e->rect[j].x = j * 147;
    e->rect[j].y = 0;
    e->rect[j].h = 192;
    e->rect[j].w = 147;
  }
  e->Dir = 1;
  e->Detected = 0;
  e->range = 150;
}

void afficherEnnemiSimple(Ennemi e, SDL_Surface * screen){
  if(e.Dir == 1){
    SDL_BlitSurface(e.sprite, &e.rect[e.frame], screen, &e.posScreen);
  }
  if(e.Dir == -1){
    SDL_BlitSurface(e.spriteb, &e.rect[e.frame], screen, &e.posScreen);
  }
}

void deplacerSimple(Ennemi * e){
  switch(e->type){
    case 1:
      e->posScreen.x = e->posScreen.x + e->speed * e->Dir;
      if(e->posScreen.x >= e->RightBound){
        e->Dir = -1;
        e->frame = 0;
      }
      if(e->posScreen.x <= e->LeftBound){
        e->Dir = 1;
        e->frame = 0;
      }
      break;
    case 2:
      break;
    case 3:
      break;
    default:
      break;
  }
}

int collisionBBSimple(perso p, Ennemi e){
 if ((p.posScreen.x + 100 < e.posScreen.x) || (p.posScreen.x > e.posScreen.x + 140) ||
		(p.posScreen.y + 100 < e.posScreen.y) || (p.posScreen.y > e.posScreen.y + 192))
		return 0;
	else
		return 1;
  
}

void animerEnnemiSimple(Ennemi * e){
  e->frame++;
  //SDL_Delay(30);
  if(e->frame > 3){
    e->frame = 0;
  }
}

void LibererSimple(Ennemi e){
  SDL_FreeSurface(e.sprite);
  SDL_FreeSurface(e.spriteb);
}

//AI
void deplacerAI(Ennemi * e, perso p){
  int distance = p.posScreen.x - e->posScreen.x;
  if((abs(distance) <= e->range)&&(mathSign(distance) == e->Dir)){
    e->Detected = 1;
  }
  if(abs(distance) > e->range){
    e->Detected = 0;
  }
  switch(e->Detected){
    case 0:
      e->posScreen.x = (e->posScreen.x) + e->speed * e->Dir;
      if(e->posScreen.x >= e->RightBound){
        e->Dir = -1;
        e->frame = 0;
      }
      if(e->posScreen.x <= e->LeftBound){
        e->Dir = 1;
        e->frame = 0;
      }
      break;
    case 1:
      e->Dir = mathSign(distance);
      e->posScreen.x = e->posScreen.x + e->speed * e->Dir;
      break;
    default:
      break;
  }
}

