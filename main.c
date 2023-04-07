#include "menu.h"
#include "game.h"

void main()
{
    int retour_menu;
    int retour_menu2;
    int retour_game;
    do
    {
        retour_menu = menu_function();
        if (retour_menu == 0)
        {
            retour_menu2 = menu2();
            retour_game = game(retour_menu2);
            end(retour_game);
        }
    } while (retour_menu != 2);
}