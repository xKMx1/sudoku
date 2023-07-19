#include <iostream>
#include <SFML/Graphics.hpp>

using namespace std;

class Cell{
    private:
        sf::Vector2<float> mCoordinates;
        sf::RectangleShape mSprite;
        int mValue;
        int mCellNumber;
    public:
        void initCell(int n){
            sf::Vector2f spriteSize(50.0f, 50.0f);
            sf::Vector2f spritePosition(mCoordinates.x + 2.75f, mCoordinates.y + 2.75f);

            this->setValue(0);
            this->setCellNumber(n);
            mSprite.setSize(spriteSize);
            mSprite.setFillColor(sf::Color(120,120,120));
            mSprite.setPosition(spritePosition);
        }

        void setCoordinates(float x, float y){
            mCoordinates.x = x;
            mCoordinates.y = y;
        }

        void setCellNumber(int num){
            mCellNumber = num;
        }

        void setValue(int num){
            mValue = num;
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

Cell* generateBoard(){
    Cell* board = new Cell[81];
    for(int i = 0; i < 9; i++){                                         // y coordinates loop
        for(int j = 0; j < 9; j++){                                     // x coordinates loop
            board[(i*9)+j].setCoordinates(j * 55.555f, i * 55.555f);
            board[(i*9)+j].initCell((i*9)+j);
        }
    }

    return board;
}

bool checkRow(Cell* cell, Cell* gameBoard, int potNumber){
    int row = int(cell->getCoordinates().y / 55.555f);

    for(int i = 0; i < 9; i++){
        std::cout << i << " " << gameBoard[(row*9)+i].getValue() << std::endl;

        if(gameBoard[(row*9)+i].getValue() == potNumber){
            return false;
        }
    }
    return true;
}

bool checkCol(Cell* cell, Cell* gameBoard, int potNumber){
    int column = int(cell->getCoordinates().x / 55.555f);
    
    for(int i = 0; i < 9; i++){
        if(gameBoard[(i*9) + column].getValue() == potNumber){
            return false;
        }
    }
    return true;
}

bool checkNonet(Cell* cell, Cell* gameBoard, int potNumber){
    int nonetX;
    int nonetY;

    if(int(cell->getCoordinates().x / 55.555f) <= 2){           //if to determine the y coordinate of nonet
        nonetX = 0;
    }
    else if(int(cell->getCoordinates().x / 55.555f) <= 5){
        nonetX = 1;
    }
    else{
        nonetX = 2;
    }

    if(int(cell->getCoordinates().y / 55.555f) <= 2){           //if to determine the x coordinate of nonet
        nonetY = 0;
    }
    else if(int(cell->getCoordinates().y / 55.555f) <= 5){
        nonetY = 1;
    }
    else{
        nonetY = 2;
    }

    for(int i = nonetX * 3; i < 3 * nonetX + 3; i++){                                         
        for(int j = nonetY * 3; j < 3 * nonetY + 3; j++){                                    
            if(gameBoard[(i*9) + j].getValue() == potNumber){
                return false;
            }
        }
    }
    return true;
}

void deleteBoard(Cell* board){
    delete[] board;
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(500, 500), "Sudoku");
    sf::Texture texture;

    Cell* gameBoard = generateBoard();

    if(checkNonet(&gameBoard[10], gameBoard, 4)){
        std::cout << "Works" << std::endl;
    }
    else{
        std::cout << "Doesnt work" << std::endl;
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

        for(int i = 0; i < 81; i++){
            window.draw(gameBoard[i].getSprite());
        }

        window.display();
    }

    deleteBoard(gameBoard);
    return 0;
}
