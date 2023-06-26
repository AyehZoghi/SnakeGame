#include "../headers/MainMenu.h"
MainMenu::MainMenu(unsigned width , unsigned height ) {
    if(!font.loadFromFile("C:/Users/asus/CLionProjects/Snake/assets/fonts/slant_regular.ttf")){
        cout<<"No font is here";
    }

    //Play
   mainMenu[0].setFont(font);
   mainMenu[0].setFillColor(Color::Red);
   mainMenu[0].setOutlineColor(Color::Black);
   mainMenu[0].setOutlineThickness(2);
   mainMenu[0].setString("Play");
   mainMenu[0].setCharacterSize(50);
   mainMenu[0].setPosition(300,200);

   //About
   mainMenu[1].setFont(font);
   mainMenu[1].setFillColor(Color::White);
   mainMenu[1].setOutlineColor(Color::Black);
   mainMenu[1].setOutlineThickness(2);
   mainMenu[1].setString("About");
   mainMenu[1].setCharacterSize(50);
   mainMenu[1].setPosition(300,300);

   //Exit
   mainMenu[2].setFont(font);
   mainMenu[2].setFillColor(Color::White);
   mainMenu[2].setOutlineColor(Color::Black);
   mainMenu[2].setOutlineThickness(2);
   mainMenu[2].setString("Let me leave!");
   mainMenu[2].setCharacterSize(50);
   mainMenu[2].setPosition(300,400);

   MainMenuSelected = 0;

}

MainMenu::~MainMenu() = default;

//Draw MainMenu
void MainMenu::draw(RenderWindow *window) {
    for(const auto & i : mainMenu){
        window->draw(i);
    }
}
//move up
void MainMenu::MoveUp() {
    if(MainMenuSelected - 1 >= 0)
    {
        mainMenu[MainMenuSelected].setFillColor(Color::White);
        MainMenuSelected--;
        mainMenu[MainMenuSelected].setFillColor(Color::Red);
    }
}
//move down
void MainMenu::MoveDown(){
    if(MainMenuSelected + 1 < Max_main_menu )
    {
        mainMenu[MainMenuSelected].setFillColor(Color::White);
        MainMenuSelected++;
        mainMenu[MainMenuSelected].setFillColor(Color::Red);
    }
}

