#include "time.h"

void Timer(int *tempsdebut)
{
    if (SDL_GetTicks() - *tempsdebut >= 1000)
    {
        *tempsdebut = SDL_GetTicks();
    }
}

void inittemps(Time *t)
{
    int test;
    time(&(t->tempsdebut));
    t->mm = 0;
    t->ss = 0;
    test = initTexttime(&t->temps);
    t->score = 1000;
    t->pos_score.x = 350;
    t->pos_score.y = 20;
}

int initTexttime(Text *T)
{
    int testload;
    T->couleurTxt.r = 0;
    T->couleurTxt.g = 0;
    T->couleurTxt.b = 0;

    strcpy(T->txt, "");
    T->positionText.x = 20;
    T->positionText.y = 20;
    testload = loadFonttime(T, "resources menu/angelina.TTF");
    T->textSurface = NULL;
    return testload;
}
int loadFonttime(Text *T, char *path)
{
    if (TTF_Init() == -1)
    {
        printf("Erreur d'initialisation de TTF_Init : %s\n", TTF_GetError());
        return -1;
    }
    T->police = TTF_OpenFont(path, 60); // pathn hoa esm l font o 60 l taile
    if (T->police == NULL)
    {
        printf("Unable to load Font: %s\n", SDL_GetError());
        return (-1);
    }
    return (0);
}

void update_time(Time *T)
{
    char ch_score[100];
    int tmp;
    int ts;
    time(&(T->t2));
    ts = T->t2 - T->tempsdebut;
    T->mm = (ts / 60) % 60;
    T->ss = ts % 60;
    tmp = (T->ss * 10 + T->mm * 60);
    if(tmp == 1000)
    T->score = 0 ;
    T->score = 1000 -tmp ;
    sprintf(T->temps.txt, "*** time :%02d:%02d  ***", T->mm, T->ss);
    sprintf(ch_score, "*** score : %d ***", (T->score));
    T->temps.textSurface = TTF_RenderText_Solid(T->temps.police, T->temps.txt, T->temps.couleurTxt); // ttfrender tekho l police o txt o couleur taa l text eli besh taficchiih
    T->surface_score = TTF_RenderText_Solid(T->temps.police, ch_score, T->temps.couleurTxt);         // ttfrender tekho l police o txt o couleur taa l text eli besh taficchiih
}
void displaytime(Time T, SDL_Surface *screen)
{

    SDL_BlitSurface(T.temps.textSurface, NULL, screen, &(T.temps.positionText));
    SDL_BlitSurface(T.surface_score, NULL, screen, &(T.pos_score));
}

void freeTexttime(Text T)
{
    TTF_CloseFont(T.police);
    TTF_Quit();
}
