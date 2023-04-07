#include "background.h"

void initBack(background *b, int x, int y)
{
    b->image = IMG_Load("background resources/bg.png");
    if (b->image == NULL)
        printf("error bg \n");
    b->sprite = IMG_Load("background resources/spritesmall.png");
    b->sprite2 = IMG_Load("background resources/sprite22.png");
    if (b->sprite2 == NULL)
        printf("can't open sprite 2 \n");
    if (b->sprite == NULL)
        printf("error loading sprite \n ");
    b->vitesse = 0;
    b->vitesse2 = 0;
    b->camera.x = 0;
    b->camera.y = 0;
    b->camera.w = x;
    b->camera.h = y;
    /////////////////////// camera 1
    b->camera1.x = 0;
    b->camera1.y = 0;
    b->camera1.w = x / 2;
    b->camera1.h = y;
    ///////////////////////// camera 2
    b->camera2.x = 0;
    b->camera2.y = 0;
    b->camera2.w = x / 2;
    b->camera2.h = y;
    b->mask = IMG_Load("background resources/mask.png");
    if (b->mask == NULL)
        printf("error mask \n");
    b->music = Mix_LoadMUS("background resources/music.mp3");
    Mix_PlayMusic(b->music, -1);
    b->i = 0;
    b->j = 0;
    b->pos_anim.x = 0;
    b->pos_anim.y = 200;
    b->pos_sprite.x = 0;
    b->pos_sprite.y = 0;
    b->pos_sprite.w = (int)(160 / 3);
    b->pos_sprite.h = (int)(160 / 3);
    b->x = 0;
    b->y = 0;
    b->pos_anim2.x = 1366 - (int)(626 / 5);
    b->pos_anim2.y = 0;
    b->pos_sprite2.x = 0;
    b->pos_sprite2.y = 0;
    b->pos_sprite2.w = (int)(626 / 5);
    b->pos_sprite2.h = (int)(626 / 5);
}

void afficherBack(background b, SDL_Surface *screen, int x, int y, int nbp)
{
    SDL_Rect pos_camera2;
    pos_camera2.x = x / 2;
    pos_camera2.y = 0;
    pos_camera2.w = x / 2;
    pos_camera2.h = y;

    if (nbp == 1)
        SDL_BlitSurface(b.image, &(b.camera), screen, NULL);
    if (nbp == 2)
    {
        SDL_BlitSurface(b.image, &(b.camera1), screen, NULL);
        SDL_BlitSurface(b.image, &(b.camera2), screen, &pos_camera2);
    }
}

void scrolling(background *b, int direction, int pasAvancement, Ennemi *e, Ennemi *eAI)
{
    switch (direction)
    {
    case 'R':
        b->camera.x += pasAvancement;
        e->posScreen.x -= pasAvancement;
        eAI->posScreen.x -= pasAvancement;
        e->RightBound -= pasAvancement;
        e->LeftBound -= pasAvancement;
        eAI->RightBound -= pasAvancement;
        eAI->LeftBound -= pasAvancement;
        break;
    case 'L':
        if (b->camera.x >= 0){
            b->camera.x -= pasAvancement;
            e->posScreen.x += pasAvancement;
                eAI->posScreen.x += pasAvancement;
                e->RightBound += pasAvancement;
                e->LeftBound += pasAvancement;
                eAI->RightBound += pasAvancement;
               eAI->LeftBound += pasAvancement;
        }
        break;
    case 'U':
        b->camera.y -= pasAvancement;
        break;
    case 'D':
        if (b->camera.y <= 3000 - 768)
            b->camera.y += pasAvancement;
        break;
    }
}
void scrolling1(background *b, int direction, int pasAvancement)
{

    switch (direction)
    {
    case 'R':

        b->camera1.x += pasAvancement;
        break;
    case 'L':

        b->camera1.x -= pasAvancement;
        break;
    case 'U':
        // b->camera.y -= pasAvancement;
        break;
    case 'D':
        // b->camera.y += pasAvancement;
        break;
    }
}
void scrolling2(background *b, int direction, int pasAvancement)
{

    switch (direction)
    {
    case 'R':
        b->camera2.x += pasAvancement;
        break;
    case 'L':

        b->camera2.x -= pasAvancement;
        break;
    case 'U':
        // b->camera.y -= pasAvancement;
        break;
    case 'D':
        // b->camera.y += pasAvancement;
        break;
    }
}
void animation(background *b, SDL_Surface *screen)
{

    if (b->pos_anim.x < 1366 / 2 - 50)
    {
        SDL_BlitSurface(b->sprite, &(b->pos_sprite), screen, &(b->pos_anim));
        b->pos_anim.x += 3;
        if (b->pos_anim.x >= 1366 / 2 - 50)
            b->pos_anim.x = 0;
    }

    b->pos_sprite.x = b->i * (int)(160 / 3);
    b->pos_sprite.y = b->j * (int)(160 / 3);
    (b->j)++;
    if ((b->j) == 3)
    {
        (b->j) = 0;
        (b->i)++;
        if (b->i == 3)
            b->i = 0;
    }
    if (((b->i) == 2) && (b->j == 0))
    {
        (b->j)++;
    }
}
void animation2(background *b, SDL_Surface *screen)
{
    SDL_BlitSurface(b->sprite2, &(b->pos_sprite2), screen, &(b->pos_anim2));

    b->pos_sprite2.x = b->x * (int)(626 / 5);
    b->pos_sprite2.y = b->y * (int)(626 / 5);
    (b->y)++;
    if ((b->y) == 5)
    {
        (b->y) = 0;
        (b->x)++;
        if (b->x == 5)
            b->x = 0;
    }
}