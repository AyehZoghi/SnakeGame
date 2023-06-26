#ifndef INPUT_CPP_MAINMENU_H
#define INPUT_CPP_MAINMENU_H
#define Max_main_menu 3

#include<SFML/Graphics.hpp>
#include "Engine.h"
#include <iostream>

using namespace sf;
using namespace std;

class MainMenu {

public:
    MainMenu( unsigned width ,unsigned height);
    ~MainMenu();
    void draw(RenderWindow *window);
    void MoveUp();
    void MoveDown();
    int MainMenuPressed() const{
        return MainMenuSelected;
    }

private:
    int MainMenuSelected;
    Font font;
    Text mainMenu[Max_main_menu];
};


#endif //INPUT_CPP_MAINMENU_H
