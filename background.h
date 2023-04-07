#ifndef back_H_INCLUDED
#define back_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_mixer.h>
#include "Entite.h"

typedef struct background
{
    SDL_Surface *image, *mask, *sprite, *sprite2;
    SDL_Rect camera, camera1, camera2;
    Mix_Music *music;
    int vitesse, vitesse2;
    int i;
    int j;
    SDL_Rect pos_anim;
    SDL_Rect pos_sprite;
    int x;
    int y;
    SDL_Rect pos_anim2;
    SDL_Rect pos_sprite2;
} background;

void initBack(background *b, int x, int y);
void afficherBack(background b, SDL_Surface *screen, int x, int y, int nbp);
void scrolling(background *b, int direction, int pasAvancement , Ennemi *e,Ennemi *eAI);
void scrolling1(background *b, int direction, int pasAvancement);
void scrolling2(background *b, int direction, int pasAvancement);
void animation(background *b, SDL_Surface *screen);
void animation2(background *b, SDL_Surface *screen);

#endif // DS_H_INCLUDED
