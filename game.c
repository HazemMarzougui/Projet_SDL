#include "game.h"

int game(int nbp)
{
    //-----------partie declaration-------//
    /////////////////////////////
    SDL_Surface *hearts;
    SDL_Rect pos_hearts;
    SDL_Rect pos_hearts_src;
    pos_hearts_src.w = 250;
    pos_hearts_src.h = 62;
    pos_hearts.x = 1366 - 250;
    pos_hearts.y = 0;
    hearts = IMG_Load("hearts/hearts1.png");
    int continuer = 1;
    int vie = 3;
    background b;
    perso p, p2; // + perso 2
    Time temps;
    Ennemi e;
    Ennemi eAI;
    int Nbe = 1;
    int colEnt = 0;
    int colEnt2 = 0;
    SDL_Surface *mask;
    mask = IMG_Load("background resources/mask.png");
    int direction = 'N', direction2 = 'N';
    SDL_Surface *screen;
    SDL_Event event;
    int resx = 1366, resy = 768;
    int bgw = 3000, bgh = 768;
    int persow = 100, persoh = 100;

    //----------partie initialisation------//
    SDL_Init(SDL_INIT_VIDEO);

    screen = SDL_SetVideoMode(resx, resy, 32, SDL_HWSURFACE);

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1)
        printf("%s", Mix_GetError());

    initBack(&b, resx, resy);
    init(&p);
    init2(&p2); ///////// init perso 2
    inittemps(&temps);
    initEnnemiSimple(&e, 1);
    initEnnemiSimple(&eAI, 2);
    SDL_Rect posperso2maj;

    while (continuer) // ------boucle de jeu --------//
    {
        //------partie input--------//
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                continuer = 0;
                break;
            case SDL_KEYDOWN:

                switch (event.key.keysym.sym)
                {
                case SDLK_RIGHT:
                    direction = 'R';
                    p.Signalb = 0;
                    p.Signal = 1;
                    p.direction = 1;

                    break;
                case SDLK_LEFT:
                    direction = 'L';
                    p.Signal = 0;
                    p.Signalb = 1;
                    p.direction = -1;

                    break;
                case SDLK_UP:
                    // direction = 'U';
                    p.isJump = 1;

                    break;
                case SDLK_DOWN:
                    direction = 'D';
                    break;

                ////////////////////////////////////////////////// 2eme perso et camera
                case SDLK_d:
                    direction2 = 'R';
                    p2.Signalb = 0;
                    p2.Signal = 1;
                    p2.direction = 1;

                    break;
                case SDLK_q:
                    direction2 = 'L';
                    p2.Signal = 0;
                    p2.Signalb = 1;
                    p2.direction = -1;

                    break;
                case SDLK_z:
                    // direction = 'U';
                    p2.isJump = 1;

                    break;
                case SDLK_s:
                    direction2 = 'D';
                    break;
                }
                break;
            case SDL_KEYUP:
                if (event.key.keysym.sym == SDLK_RIGHT)
                {
                    p.Signal = 0;
                    b.vitesse = 0;
                }

                if (event.key.keysym.sym == SDLK_LEFT)
                {
                    p.Signalb = 0;
                    b.vitesse = 0;
                }
                if (event.key.keysym.sym == SDLK_UP)
                {
                    p.isJump = 0;
                }
                if (event.key.keysym.sym == SDLK_d)
                {
                    p2.Signal = 0;
                    b.vitesse2 = 0;
                }

                if (event.key.keysym.sym == SDLK_q)
                {
                    p2.Signalb = 0;
                    b.vitesse2 = 0;
                }
                if (event.key.keysym.sym == SDLK_z)
                {
                    p2.isJump = 0;
                }

                break;
            }
        }
        ////////////////////////////////////////////////////////////////////////////////////////////////// right
        afficherBack(b, screen, resx, resy, nbp);
        if (nbp == 1) // pour un seul perso
        {
            if (collision_parfaite_down(mask, p.posScreen, b.camera) == 0)
                saut(&p);
                else 
                {
                    vie--;

                p.posScreen.x = 0;
                b.camera.x = 10;
                e.posScreen.x = 400;
                p.Signal = 0;
                p.Signalb = 0; 
                e.RightBound = e.posScreen.x + 40;
                e.LeftBound = e.posScreen.x - 40;
                eAI.posScreen.x = 1700;
                eAI.RightBound = eAI.posScreen.x + 40;
                eAI.LeftBound = eAI.posScreen.x - 40;
                }
            if (collision_parfaite_right(mask, p.posScreen, b.camera) == 0)
            {
                if ((p.posScreen.x >= resx / 2) && (direction == 'R') && (b.camera.x <= bgw - resx) && (p.Signal == 1))
                {
                    if (p.speed != 0)
                        b.vitesse = p.speed;
                    else if (b.vitesse < 20)
                        b.vitesse += 0.5;
                    scrolling(&b, direction, b.vitesse, &e, &eAI);
                }
                else if ((direction == 'R') && (p.posScreen.x < resx - persow))
                {
                    deplacerPerso(&p);
                }
            }

            //////////////////////////////////////////////////////////////////////////////////////// left
            if (collision_parfaite_left(mask, p.posScreen, b.camera) == 0)
            {
                if ((p.posScreen.x <= resx / 4) && (direction == 'L') && (b.camera.x >= 0) && (p.Signalb == 1))
                {
                    if (p.speed != 0)
                        b.vitesse = p.speed;
                    else if (b.vitesse < 20)
                        b.vitesse += 0.5;
                    scrolling(&b, direction, b.vitesse, &e, &eAI);
                }
                else if ((direction == 'L') && (p.posScreen.x >= 0))
                {
                    deplacerPerso(&p);
                }
            }
            //////////////////////////////////////// time
            update_time(&temps);
            displaytime(temps, screen);
            ////////////////////////////////////////////////////////////// entity

            afficherEnnemiSimple(e, screen);
            afficherEnnemiSimple(eAI, screen);
            animerEnnemiSimple(&e);
            animerEnnemiSimple(&eAI);
            deplacerSimple(&e);
            deplacerAI(&eAI, p);
            colEnt = collisionBBSimple(p, e);
            colEnt2 = collisionBBSimple(p, eAI);

            if (collisionBBSimple(p, e) == 1)
            {
                
                vie--;

                p.posScreen.x = 0;
                b.camera.x = 10;
                e.posScreen.x = 400;
                p.Signal = 0;
                p.Signalb = 0; 
                e.RightBound = e.posScreen.x + 40;
                e.LeftBound = e.posScreen.x - 40;
                eAI.posScreen.x = 1700;
                eAI.RightBound = eAI.posScreen.x + 40;
                eAI.LeftBound = eAI.posScreen.x - 40;
            }
            if (collisionBBSimple(p, eAI) == 1)
            {
                
                vie--;
                p.posScreen.x = 0;
                p.Signal = 0;
                p.Signalb = 0; 
                b.camera.x = 10;
                e.posScreen.x = 400;
                e.RightBound = e.posScreen.x + 40;
                e.LeftBound = e.posScreen.x - 40;
                eAI.posScreen.x = 1700;
                eAI.RightBound = eAI.posScreen.x + 40;
                eAI.LeftBound = eAI.posScreen.x - 40;
            }
            if (vie <= 0)
            {
                continuer = 0;
            }
            ////////////////////////////////////////// affichage hearts

            pos_hearts_src.x = 0;
            pos_hearts_src.y = 0;
            pos_hearts_src.w = vie * (250 / 3);
            SDL_BlitSurface(hearts, &pos_hearts_src, screen, &pos_hearts);
            if (b.camera.x < resx / 4)
                animation(&b, screen);
            if ((b.camera2.x >= bgw - resx / 2) && (p2.posScreen.x > 10))
                animation2(&b, screen);
        }
        ///////////////////////////////////////////////////////////////// 2 joueurs
        if (nbp == 2) // pour deux perso
        {             ///////////////////////////////////////////////////////////////// camera 1
            if (collision_parfaite_down(mask, p.posScreen, b.camera1) == 0)
                saut(&p);
            if (collision_parfaite_right(mask, p.posScreen, b.camera1) == 0)
            {
                if ((p.posScreen.x >= resx / 4) && (direction == 'R') && (b.camera1.x <= bgw - (resx / 2)) && (p.Signal == 1))
                {
                    if (p.speed != 0)
                        b.vitesse = p.speed;
                    else if (b.vitesse < 20)
                        b.vitesse += 0.5;
                    scrolling1(&b, direction, b.vitesse);
                }
                else if ((direction == 'R') && (p.posScreen.x < (resx / 2) - persow))
                {
                    deplacerPerso(&p);
                }
            }

            //////////////////////////////////////////////////////////////////////////////////////// left
            if (collision_parfaite_left(mask, p.posScreen, b.camera1) == 0)
            {
                if ((p.posScreen.x <= resx / 4) && (direction == 'L') && (b.camera1.x >= 0) && (p.Signalb == 1))
                {
                    if (p.speed != 0)
                        b.vitesse = p.speed;
                    else if (b.vitesse < 20)
                        b.vitesse += 0.5;
                    scrolling1(&b, direction, b.vitesse);
                }
                else if ((direction == 'L') && (p.posScreen.x >= 0))
                {
                    deplacerPerso(&p);
                }
            }

            ///////////////////////////////////////////////////////////////////// camera 2
            posperso2maj = p2.posScreen;
            posperso2maj.x -= resx / 2;
            if (collision_parfaite_down(mask, posperso2maj, b.camera2) == 0)
                saut(&p2);
            if (collision_parfaite_right(mask, posperso2maj, b.camera2) == 0)
            {
                if ((p2.posScreen.x >= resx * 3 / 4) && (direction2 == 'R') && (b.camera2.x <= bgw - (resx / 2)) && (p2.Signal == 1))
                {
                    if (p2.speed != 0)
                        b.vitesse2 = p2.speed;
                    else if (b.vitesse2 < 20)
                        b.vitesse2 += 0.5;
                    scrolling2(&b, direction2, b.vitesse2);
                }
                else if ((direction2 == 'R') && (p2.posScreen.x < (resx)-persow))
                {
                    deplacerPerso(&p2);
                }
            }

            //////////////////////////////////////////////////////////////////////////////////////// left
            if (collision_parfaite_left(mask, posperso2maj, b.camera2) == 0)
            {
                if ((p2.posScreen.x <= resx * 3 / 4) && (direction2 == 'L') && (b.camera2.x >= 0) && (p2.Signalb == 1))
                {
                    if (p2.speed != 0)
                        b.vitesse2 = p2.speed;
                    else if (b.vitesse2 < 20)
                        b.vitesse2 += 0.5;
                    scrolling2(&b, direction2, b.vitesse2);
                }
                else if ((direction2 == 'L') && (p2.posScreen.x >= resx / 2))
                {
                    deplacerPerso(&p2);
                }
            }
        }
        //------partie affichage------//

        afficherPerso(p, screen);
        if (nbp == 2) //////////// affich perso2
            afficherPerso(p2, screen);
        animerPerso(&p);
        animerPerso(&p2);
        if (p.frame == 4)
            p.frame = 0;
             if (p.framej == 4)
            p.framej = 0;
        if (p2.frame == 4)
            p2.frame = 0;

        if (p.posScreen.x >= resx - 100)
            continuer = 0;

        ///////////////////////////////////////////////////////////////
        //------partie update------//
        SDL_Flip(screen);
        SDL_Delay(20);
    }
    freeTexttime(temps.temps);
    SDL_FreeSurface(b.sprite);
    SDL_FreeSurface(b.image);
    SDL_FreeSurface(b.mask);
    LibererSimple(e);
    LibererSimple(eAI);
    Mix_FreeMusic(b.music);
    Mix_CloseAudio();
    SDL_Quit();
    if (p.posScreen.x < resx - 350)
        vie = 0;
    return vie;
}
