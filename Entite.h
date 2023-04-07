#ifndef ENTITE_H_
#define ENTITE_H_

#include "perso.h"


typedef struct{
  int type; //1 Swordsman 2 Archer 3 Shield boy
  int id;
  int hp;
  int speed;
  int LeftBound;
  int RightBound;
  int range;
  int Dir;
  int frame;
  int Detected;
  SDL_Surface * sprite;
  SDL_Surface * spriteb;
  SDL_Rect rect[4];
  SDL_Rect posScreen;
}Ennemi;

//Main functions
void initEnnemi(Ennemi e[]);
void afficherEnnemi(Ennemi e[], SDL_Surface * screen);
void deplacer(Ennemi e[]);
int collisionBB(perso p, Ennemi e[]);
void animerEnnemi(Ennemi e[]);
void Liberer(Ennemi e[]);

//Functions for one entity
void initEnnemiSimple(Ennemi * e, int i);
void afficherEnnemiSimple(Ennemi e, SDL_Surface * screen);
void deplacerSimple(Ennemi * e);
int collisionBBSimple(perso p, Ennemi e);
void animerEnnemiSimple(Ennemi * e);
void LibererSimple(Ennemi e);

//functions for AI
void deplacerAI(Ennemi * e, perso p );


//Misc
int mathSign(int x);

#endif
