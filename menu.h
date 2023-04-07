#ifndef FONCTIONS_H_
#define FONCTIONS_H_
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_image.h>

typedef struct
{
    SDL_Surface *image, *screen, *bar, *barbg, *bgsett, *bgplay; // 1
    SDL_Rect offset, postext, posvlm, poslid;                    // 2
    SDL_Rect rects[5][3];
    SDL_Surface *bouton_on[3], *bouton_off[3], *bouton_on1[3], *bouton_off1[3];
    
    Mix_Music *music;                                                           // 4
    Mix_Chunk *btnsnd;  
                                                            // 5
    TTF_Font *font;                                                             // 6
    SDL_Surface *Titre;                                                         // 7
    SDL_Rect post;                                                              // 8

} menu;
int initialiser();
int load_menu(menu *m);
void setrects(SDL_Rect clips[5][3]);
int menu_function();
int menu2();
void end(int x);
#endif
