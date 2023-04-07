#ifndef PERSO_H_INCLUDED
#define PERSO_H_INCLUDED
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <math.h>

typedef struct 
{
	SDL_Surface * sprite;
	SDL_Rect posScreen;
	SDL_Rect posSprite;
	int direction;
	int Signal;
	int Signalb;
	float speed;
	int frame;
	int framej;
	float VarX;
	int col;
	int ground;
	int isJump;
}perso;

int init(perso* p);
int init2(perso* p);
void afficherPerso(perso p,SDL_Surface* screen);
void deplacerPerso(perso *p);
void animerPerso(perso *p);
void saut(perso *p);

#endif // HEADER_H_INCLUDED