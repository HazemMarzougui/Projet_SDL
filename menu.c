#include "menu.h"

int initialiser()
{
  if (SDL_Init(SDL_INIT_VIDEO) == -1)
  {
    printf("Can't init SDL:  %s\n", SDL_GetError());
    return EXIT_FAILURE;
  }

  Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 4096);

  TTF_Init();
  if (TTF_Init() == -1)
  {
    printf("Can't TTF:  %s\n", SDL_GetError());
    return EXIT_FAILURE;
  }
}
int load_menu(menu *m)
{
  m->screen = SDL_SetVideoMode(1920, 1080, 32, SDL_HWSURFACE | SDL_RESIZABLE);
  m->image = IMG_Load("resources menu/index.png");
  m->bar = IMG_Load("resources menu/Bar1.png");
  m->barbg = IMG_Load("resources menu/BarBG1.png");
  m->bgsett = IMG_Load("resources menu/bgsett.png");

  if (m->screen == NULL)
  {
    printf("Can't set video mode: %s\n", SDL_GetError());
    return EXIT_FAILURE;
  }

  if (m->image == NULL)
  {
    printf(" %s\n", SDL_GetError());
    return EXIT_FAILURE;
  }
  m->bouton_on[0] = IMG_Load("resources menu/play_on.png");
  m->bouton_on[1] = IMG_Load("resources menu/settings_on.png");
  m->bouton_on[2] = IMG_Load("resources menu/exit_on.png");

  m->bouton_off[0] = IMG_Load("resources menu/play_off.png");
  m->bouton_off[1] = IMG_Load("resources menu/settings_off.png");
  m->bouton_off[2] = IMG_Load("resources menu/exit_off.png");

  m->bouton_on1[0] = IMG_Load("resources menu/volume_on.png");
  m->bouton_on1[1] = IMG_Load("resources menu/fullscreen_on.png");
  m->bouton_on1[2] = IMG_Load("resources menu/back_on.png");

  m->bouton_off1[0] = IMG_Load("resources menu/volume_off.png");
  m->bouton_off1[1] = IMG_Load("resources menu/fullscreen_off.png");
  m->bouton_off1[2] = IMG_Load("resources menu/back_off.png");

  m->offset.x = 0;
  m->offset.y = 0;
  m->posvlm.x = 310 + 300 + 50;
  m->posvlm.y = 440 + (115 / 2 - 47 / 2);
  m->poslid.x = 0;
  m->poslid.y = 0;
  m->poslid.h = 47;
  m->poslid.w = 556 / 2;

  m->btnsnd = Mix_LoadWAV("resources menu/btnsnd.wav");
  m->music = Mix_LoadMUS("resources menu/mainmenu.mp3");

  m->font = TTF_OpenFont("resources menu/Pixeboy.ttf", 90); // to edit
  if (m->font == NULL)
  {
    printf("Can't font bruh:  %s\n", SDL_GetError());
    return EXIT_FAILURE;
  }

  m->post.x = 750;
  m->post.y = 100;
}
void setrects(SDL_Rect clips[5][3])
{
  for (int j = 0; j < 4; j++)
  {
    for (int i = 0; i < 3; i++)
    {
      clips[j][i].x = i * 1920;
      clips[j][i].y = j * 1080;
      clips[j][i].h = 1080;
      clips[j][i].w = 1920;
    }
  }
  for (int i = 0; i < 1; i++)
  {
    clips[4][i].x = i * 1920;
    clips[4][i].y = 4 * 1080;
    clips[4][i].h = 1080;
    clips[4][i].w = 1920;
  }
}

int menu_function()
{
  initialiser();
  menu m;
  load_menu(&m);
  setrects(m.rects);

  Mix_PlayMusic(m.music, -1);
  float sound;
  sound = 100 / 2;
  Mix_VolumeMusic(sound);

  SDL_Color white = {255, 255, 255}, rouge = {255, 0, 0}, grey = {128, 128, 128};
  m.Titre = TTF_RenderText_Blended(m.font, "LAST WHISPER", grey);

  int quit = 0;
  SDL_Event event;
  int frame = 0;
  int framej = 0;
  Uint32 start;
  const int fps = 60;
  int mx, my; // mouse position
  int mouse = 3;
  int keyboard = 0;
  int kbon = 0;
  int sett = 0;
  int vol = 0;
  int FS = 0;
  ////////////////////////////////////////////////////////////////////////////////////////////////start of menu cycle
  while (quit == 0)
  {
    ////////////////////////////////////////////////////////////////////////////////////////////// affichage
    if (sett == 0)
    {
      SDL_BlitSurface(m.image, &m.rects[framej][frame], m.screen, &m.offset);
      SDL_BlitSurface(m.Titre, NULL, m.screen, &m.post);
      start = SDL_GetTicks();
    }
    if (sett == 1)
    {
      SDL_BlitSurface(m.bgsett, NULL, m.screen, &m.offset);
      SDL_BlitSurface(m.barbg, NULL, m.screen, &m.posvlm);
      SDL_BlitSurface(m.bar, &m.poslid, m.screen, &m.posvlm);
      Mix_VolumeMusic(sound);
    }
    //////////////////////////////////// buttons blit loop
    for (int i = 0; i < 3; i++)
    {
      m.postext.x = 310;
      m.postext.y = 440 + i * 125;
      if (sett == 0)
      {
        if (kbon == 0 && mouse != i)
        {
          SDL_BlitSurface(m.bouton_off[i], NULL, m.screen, &m.postext);
        }
        else if (kbon == 0 && mouse == i)
        {
          SDL_BlitSurface(m.bouton_on[i], NULL, m.screen, &m.postext);
        }
        else
        {
          if (i == keyboard)
          {
            SDL_BlitSurface(m.bouton_on[i], NULL, m.screen, &m.postext);
          }
          if (i != keyboard)
          {
            SDL_BlitSurface(m.bouton_off[i], NULL, m.screen, &m.postext);
          }
        }
      }
      if (sett == 1)
      {
        if (kbon == 0 && mouse != i)
        {
          SDL_BlitSurface(m.bouton_off1[i], NULL, m.screen, &m.postext);
        }
        else if (kbon == 0 && mouse == i)
        {
          SDL_BlitSurface(m.bouton_on1[i], NULL, m.screen, &m.postext);
        }
        else
        {
          if (i == keyboard)
          {
            SDL_BlitSurface(m.bouton_on1[i], NULL, m.screen, &m.postext);
          }
          if (i != keyboard)
          {
            SDL_BlitSurface(m.bouton_off1[i], NULL, m.screen, &m.postext);
          }
        }
      }
    }
    // event handeling
    while (SDL_PollEvent(&event))
    {
      switch (event.type)
      {
      case SDL_MOUSEMOTION: /////////////////////////////////// mouse motion event
      {
        mx = event.motion.x;
        my = event.motion.y;
        if (sett == 0)
        {
          if ((mx >= m.postext.x) && (mx <= m.postext.x + 300) && (my >= 440) && (my <= 440 + 115))
          {
            mouse = 0;
            keyboard = 0;
          }
          else if ((mx >= m.postext.x) && (mx <= m.postext.x + 300) && (my >= 440 + 125) && (my <= 440 + 125 + 115))
          {
            keyboard = 1;
            mouse = 1;
          }
          else if ((mx >= m.postext.x) && (mx <= m.postext.x + 300) && (my >= 440 + 250) && (my <= 440 + 250 + 115))
          {
            mouse = 2;
            keyboard = 2;
          }
          else
          {
            kbon = 0;
            mouse = 3;
            keyboard = 3;
          }
        }
        else if (sett == 1)
        {
          if ((mx >= m.postext.x) && (mx <= m.postext.x + 300) && (my >= 440) && (my <= 440 + 115))
          {
            mouse = 0;
            keyboard = 0;
          }
          else if ((mx >= m.postext.x) && (mx <= m.postext.x + 300) && (my >= 440 + 125) && (my <= 440 + 125 + 115))
          {
            keyboard = 1;
            mouse = 1;
          }
          else if ((mx >= m.postext.x) && (mx <= m.postext.x + 300) && (my >= 440 + 250) && (my <= 440 + 250 + 115))
          {
            mouse = 2;
            keyboard = 2;
          }
          else
          {
            kbon = 0;
            mouse = 3;
            keyboard = 3;
          }
          if ((mx >= m.posvlm.x) && (mx <= m.posvlm.x + 556) && (my >= m.posvlm.y) && (my <= m.posvlm.y + 47))
          {
            vol = 1;
          }
          else
            vol = 0;
        }
        break;
      }
      case SDL_MOUSEBUTTONDOWN: ///////////////////////////////////// mouse click event
      {
        if (event.button.button == SDL_BUTTON_LEFT)
        {
          switch (sett)
          {
          case 0:
            if (keyboard == 0)
            {
              Mix_PlayChannel(-1, m.btnsnd, 0);
              sett = 2;
              quit = 1;
            }
            if (keyboard == 1)
            {
              Mix_PlayChannel(-1, m.btnsnd, 0);
              sett = 1;
            }
            if (keyboard == 2)
            {
              Mix_PlayChannel(-1, m.btnsnd, 0);
              quit = 1;
            }
            break;
          case 1:
            if (keyboard == 2)
            {
              Mix_PlayChannel(-1, m.btnsnd, 0);
              sett = 0;
            }
            if (keyboard == 1)
            {
              Mix_PlayChannel(-1, m.btnsnd, 0);
              switch (FS)
              {
              case 0:
                FS = 1;
                m.screen = SDL_SetVideoMode(1920, 1080, 32, SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_FULLSCREEN);
                break;
              case 1:
                FS = 0;
                m.screen = SDL_SetVideoMode(1920, 1080, 32, SDL_HWSURFACE | SDL_RESIZABLE);
                break;
              default:
                break;
              }
            }
            if (vol == 1)
            {
              Mix_PlayChannel(-1, m.btnsnd, 0);
              if ((mx >= m.posvlm.x + 556 / 2) && (sound >= 100))
              {
                sound = 100;
              }
              else if (mx >= m.posvlm.x + 556 / 2)
              {
                m.poslid.w = m.poslid.w + (int)(556 / 4);
                sound = sound + (100 / 4);
              }
              if ((mx < m.posvlm.x + 556 / 2) && (sound <= 0))
              {
                sound = 0;
              }
              else if (mx < m.posvlm.x + 556 / 2)
              {
                m.poslid.w = m.poslid.w - (int)(556 / 4);
                sound = sound - (100 / 4);
              }
            }
            break;
          default:
            break;
          }
          break;
        }
        else
          break;
      }
      case SDL_QUIT:
      {
        quit = 1;
        keyboard = 0;
      }
      break;
      case SDL_KEYDOWN: ///////////////////////////////////////////// keyboard keydown //////////////////////
        if (event.key.keysym.sym == SDLK_ESCAPE)
        {
          if (sett == 0)
          {
            quit = 1;
            keyboard = 1;
          }
          if (sett == 1)
          {
            Mix_PlayChannel(-1, m.btnsnd, 0);
            sett = 0;
          }
          if (sett == 2)
          {
            Mix_PlayChannel(-1, m.btnsnd, 0);
            sett = 0;
          }
        }
        if (event.key.keysym.sym == SDLK_UP)
        {
          if (kbon == 0)
          {
            keyboard = 0;
            kbon = 1;
          }
          else
          {
            keyboard--;
            if (keyboard < 0)
            {
              keyboard = 2;
            }
          }
        }
        if (event.key.keysym.sym == SDLK_DOWN)
        {
          if (kbon == 0)
          {
            keyboard = 0;
            kbon = 1;
          }
          else
          {
            keyboard++;
            if (keyboard > 2)
            {
              keyboard = 0;
            }
          }
        }
        if (event.key.keysym.sym == SDLK_RIGHT)
        {
          if (keyboard == 0)
          {
            Mix_PlayChannel(-1, m.btnsnd, 0);

            if (sound >= 100)
            {
              sound = 100;
            }
            else
            {
              m.poslid.w = m.poslid.w + (int)(556 / 4);
              sound = sound + (100 / 4);
            }
          }
        }
        if (event.key.keysym.sym == SDLK_LEFT)
        {
          if (keyboard == 0)
          {
            Mix_PlayChannel(-1, m.btnsnd, 0);

            if (sound <= 0)
            {
              sound = 0;
            }
            else
            {
              m.poslid.w = m.poslid.w - (int)(556 / 4);
              sound = sound - (100 / 4);
            }
          }
        }
        if (event.key.keysym.sym == SDLK_RETURN)
        {
          switch (sett)
          {
          case 0:
            if (keyboard == 0)
            {
              Mix_PlayChannel(-1, m.btnsnd, 0);
              sett = 2;
              quit = 1;
            }
            if (keyboard == 1)
            {
              Mix_PlayChannel(-1, m.btnsnd, 0);
              sett = 1;
            }
            if (keyboard == 2)
            {
              quit = 1;
            }
            break;
          case 1:
            if (keyboard == 2)
            {
              Mix_PlayChannel(-1, m.btnsnd, 0);
              sett = 0;
            }
            if (keyboard == 1)
            {
              Mix_PlayChannel(-1, m.btnsnd, 0);
              switch (FS)
              {
              case 0:
                FS = 1;
                m.screen = SDL_SetVideoMode(1920, 1080, 32, SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_FULLSCREEN);
                break;
              case 1:
                FS = 0;
                m.screen = SDL_SetVideoMode(1920, 1080, 32, SDL_HWSURFACE | SDL_RESIZABLE);
                break;
              default:
                break;
              }
            }
            break;
          default:
            break;
          }
        }

        break;
      default:
        break;
      }
    }
    SDL_Flip(m.screen);                      // mise a jour de l'ecran
    if (1000 / fps > SDL_GetTicks() - start) // Calcul delay + fps regulation
    {
      SDL_Delay(1000 / fps - (SDL_GetTicks() - start));
    }
  } ///////////////////////////////////////////////////////////////////////// outside of the menu cycle

  SDL_FreeSurface(m.image);
  SDL_FreeSurface(m.bar);
  SDL_FreeSurface(m.barbg);
  SDL_FreeSurface(m.bgsett);
  SDL_FreeSurface(m.Titre);
  for (int i = 0; i < 3; i++)
  {
    SDL_FreeSurface(m.bouton_on[i]);
    SDL_FreeSurface(m.bouton_off[i]);
    SDL_FreeSurface(m.bouton_on1[i]);
    SDL_FreeSurface(m.bouton_off1[i]);
  }

  Mix_FreeChunk(m.btnsnd);
  Mix_FreeMusic(m.music);
  Mix_CloseAudio();

  TTF_CloseFont(m.font);
  TTF_Quit();
  SDL_QUIT;
  return keyboard;
}
int menu2()
{
  SDL_Surface *screen, *text1, *text2;
  SDL_Rect pos1, pos2;
  int cont = 1;
  SDL_Init(SDL_INIT_VIDEO);
  if (TTF_Init() == -1)
    printf("cant ttf \n");
  screen = SDL_SetVideoMode(1920, 1000, 32, SDL_HWSURFACE || SDL_DOUBLEBUF);
  TTF_Font *font;
  font = TTF_OpenFont("resources menu/Pixeboy.ttf", 50);
  if (font == NULL)
    printf("no font \n ");
  SDL_Event event;
  int mx, my;
  SDL_Color red = {187, 0, 0}, grey = {128, 128, 128};
  pos1.x = 100;
  pos1.y = 500;
  pos2.x = 600;
  pos2.y = 500;
  int choix = 0;

  while (cont)
  {

    SDL_FillRect(screen, &screen->clip_rect, SDL_MapRGB(screen->format, 0xFF, 0xFF, 0xFF));
    if (choix == 0)
    {
      text1 = TTF_RenderText_Blended(font, "Soloplayer", grey);
      text2 = TTF_RenderText_Blended(font, "Multiplayer", grey);
      SDL_BlitSurface(text1, NULL, screen, &pos1);
      SDL_BlitSurface(text2, NULL, screen, &pos2);
    }
    else if (choix == 1)
    {
      text1 = TTF_RenderText_Blended(font, "Soloplayer", red);
      text2 = TTF_RenderText_Blended(font, "Multiplayer", grey);
      SDL_BlitSurface(text1, NULL, screen, &pos1);
      SDL_BlitSurface(text2, NULL, screen, &pos2);
    }
    else if (choix == 2)
    {
      text1 = TTF_RenderText_Blended(font, "Soloplayer", grey);
      text2 = TTF_RenderText_Blended(font, "Multiplayer", red);
      SDL_BlitSurface(text1, NULL, screen, &pos1);
      SDL_BlitSurface(text2, NULL, screen, &pos2);
    }

    while (SDL_PollEvent(&event))
    {
      switch (event.type)
      {
      case SDL_QUIT:
      {
        cont = 0;
      }
      case SDL_MOUSEMOTION:
        mx = event.motion.x;
        my = event.motion.y;
        if ((mx >= pos1.x) && (mx <= pos1.x + 300) && (my >= pos1.y) && (my <= pos1.y + 90))
        {
          choix = 1;
        }
        else if ((mx >= pos2.x) && (mx <= pos2.x + 300) && (my >= pos2.y) && (my <= pos2.y + 90))
        {
          choix = 2;
        }
        else
        {
          choix = 0;
        }
        break;
      case SDL_MOUSEBUTTONDOWN:
        if (event.button.button == SDL_BUTTON_LEFT)
        {
          if ((choix == 1) || (choix == 2))
            cont = 0;
        }
        break;
      default:
        break;
      }
    }
    SDL_Flip(screen);
  }

  SDL_FreeSurface(text1);
  SDL_FreeSurface(text2);
  TTF_CloseFont(font);
  TTF_Quit();
  SDL_Quit();
  return choix;
}
void end(int x)
{

  SDL_Surface *screen, *bg;

  int cont = 1;
  SDL_Init(SDL_INIT_VIDEO);

  screen = SDL_SetVideoMode(1920, 1000, 32, SDL_HWSURFACE || SDL_DOUBLEBUF);

  if (x == 0)
  {
    bg = IMG_Load("resources menu/game_over.jpg");
  }
  else
  {
    bg = IMG_Load("resources menu/you win.png");
  }

  SDL_Event event;
  while (cont)
  {
    SDL_BlitSurface(bg, NULL, screen, NULL);
    while (SDL_PollEvent(&event))
    {
      switch (event.type)
      {
      case SDL_QUIT:
      {
        cont = 0;
      }
      }
    }
    SDL_Flip(screen);
  }

  SDL_FreeSurface(bg);
  SDL_Quit();
}
