#include "perso.h"

int init(perso *p)
{
	p->sprite = IMG_Load("perso resources/perso.png");
	

	// position initiale
	p->posScreen.x = 0;
	p->posScreen.y = 580;
	// deplacement
	p->speed = 0;
	p->direction = 1;
	p->Signal = 0;
	p->Signalb = 0;
	// animation
	p->posSprite.x = 0;
	p->posSprite.y = 0;
	p->posSprite.h = 100;
	p->posSprite.w = 100;
	p->frame = 0;
	p->framej = 0;
	// saut
	p->isJump = 0;
	p->col = 1;
	p->speed = 0;
	p->ground = p->posScreen.y;
	p->VarX = 0;
}
int init2(perso* p)
{
	p->sprite = IMG_Load("perso resources/perso.png");
	

	// position initiale
	p->posScreen.x = 1920 / 2;
	p->posScreen.y = 520;
	// deplacement
	p->speed = 0;
	p->direction = 1;
	p->Signal = 0;
	p->Signalb = 0;
	// animation
	p->frame = 0;
	p->framej = 0;
	// saut
	p->isJump = 0;
	p->col = 1;
	p->speed = 0;
	p->ground = p->posScreen.y;
	p->VarX = 0;
}
void afficherPerso(perso p, SDL_Surface *screen)
{
	SDL_BlitSurface(p.sprite, &(p.posSprite), screen, &(p.posScreen));
}

void deplacerPerso(perso *p)
{

	if (((p->Signal == 1) || (p->Signalb == 1)) && (p->speed < 20))
	{
		p->speed += 0.5;
	}
	if ((p->Signal == 0) && (p->Signalb == 0) && (p->speed > 0))
	{
		p->speed -= 1.5;
	}

	if (p->speed <= 0)
	{
		p->speed = 0;
	}

	(p->posScreen.x) += p->speed * p->direction;
	if (p->posScreen.x <= 0)
		p->posScreen.x = 0;
	if (p->posScreen.x >= 1366 - 100)
		p->posScreen.x = 1366 - 100;
}

void animerPerso(perso *p)
{
	if ((p->direction == 1) && (p->Signal == 1))
	{

		p->posSprite.x = (p->frame) * 100;
		p->posSprite.y = 0 * 100;
		p->posSprite.h = 100;
		p->posSprite.w = 100;
		p->frame++;
	}
	if ((p->Signalb == 1) && (p->direction == -1))
	{

		p->posSprite.x = (p->framej) * 100;
		p->posSprite.y = 1 * 100;
		p->posSprite.h = 100;
		p->posSprite.w = 100;
		p->framej++;
	}

	if ((p->Signal == 0) && (p->Signalb == 0) && (p->isJump == 0))
	{	
		if (p->direction == 1)
		{
		p->posSprite.x = 0;
		p->posSprite.y = 0;
		p->posSprite.h = 100;
		p->posSprite.w = 100;
		}
		if (p->direction == -1)
		{
			p->posSprite.x = 0;
		p->posSprite.y = 100;
		p->posSprite.h = 100;
		p->posSprite.w = 100;
		}
	}
	if ((p->isJump == 1) && (p->direction == 1))
	{
		p->posSprite.x = 100;
		p->posSprite.y = 0 * 100;
		p->posSprite.h = 100;
		p->posSprite.w = 100;
	}
	if ((p->isJump == 1) && (p->direction == -1))
	{
		p->posSprite.x = 100;
		p->posSprite.y = 1 * 100;
		p->posSprite.h = 100;
		p->posSprite.w = 100;
	}
}
void saut(perso *p)
{
	int y;
	int Amp = -300;
	float delta = -4 * Amp;
	float x = (sqrt(delta) / 2);
	if ((p->isJump == 1) || (p->col == 0))
	{
		p->VarX++;
	}
	y = (int)((p->VarX - x) * (p->VarX - x) + Amp);
	if (y < 0)
	{
		p->col = 0;
	}
	if (y >= 0)
	{
		y = 0;
		p->VarX = 0;
		p->isJump = 0;
		p->col = 1;
	}
	p->posScreen.y = (int)y + p->ground;
}
