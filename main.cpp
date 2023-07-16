#include <iostream>
#include <SFML/Graphics.hpp>

using namespace std;

class Cell{
    private:
        sf::Vector2<float> mCoordinates;
        sf::RectangleShape mSprite;
        int mValue;
    public:
        void initCell(){
            sf::Vector2f spriteSize(50.0f, 50.0f);
            sf::Vector2f spritePosition(mCoordinates.x + 2.75f, mCoordinates.y + 2.75f);

            mSprite.setSize(spriteSize);
            mSprite.setFillColor(sf::Color(120,120,120));
            mSprite.setPosition(spritePosition);
        }

        void setCoordinates(float x, float y){
            mCoordinates.x = x;
            mCoordinates.y = y;
        }

        sf::Vector2<float> getCoordinates(){
            return mCoordinates;
        }

        int getValue(){
            return mValue;
        }

        sf::RectangleShape getSprite(){
            return mSprite;
        }
};

Cell* generateBoard(sf::RenderWindow& window){
    Cell* board = new Cell[81];
    for(int i = 0; i < 9; i++){                                         // y coordinates loop
        for(int j = 0; j < 9; j++){                                     // x coordinates loop
            board[(i*9)+j].setCoordinates(j * 55.555f, i * 55.555f);
            board[(i*9)+j].initCell();
            // std::cout << board[(i*9)+j].getSprite().getSize().x << std::endl;
            // window.draw(board[(i*9)+j].getSprite());
        }
    }

    return board;
}

void deleteBoard(Cell* board){
    delete[] board;
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(500, 500), "Sudoku");
    sf::Texture texture;

    Cell* gameBoard = generateBoard(window);

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

        for(int i = 0; i < 81; i++){
            window.draw(gameBoard[i].getSprite());
        }

        window.display();
    }

    deleteBoard(gameBoard);
    return 0;
}
