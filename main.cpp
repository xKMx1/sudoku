#include <iostream>
#include <SFML/Graphics.hpp>

using namespace std;

class Cell{
    private:
        sf::Vector2<float> mCoordinates;
        int value;
    public:
        int getValue(){
            return value;
        }
        
        void setCoordinates(float x, float y){
            mCoordinates.x = x;
            mCoordinates.y = y;
        }
};

void generateBoard(){
    Cell* board = new Cell[81];
    for(int i = 0; i < 9; i++){                                         // x coordinates loop
        for(int j = 0; j < 9; j++){                                     // y coordinates loop
            board[i].setCoordinates((i+1) * 55.55f, (j+1) * 55.55f);
        }
    }
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(500, 500), "Sudoku");

    sf::Texture texture;

    if(!texture.loadFromFile("img/crane_image.png")){
        std::cout << "There was an error" << std::endl;
        system("pause");
    }

    window.setFramerateLimit(60);
    while(window.isOpen()){
        sf::Event event;

        while (window.pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::Closed:
                window.close();
                break;
            }

        }

        window.clear(sf::Color(255,255,255));
        window.display();
    }

    return 0;
}
