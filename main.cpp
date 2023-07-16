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
    int row;

    switch(int(cell->getCoordinates().y / 55.555f)){                // get cell coordinates -> transform them into int coresponding to the number to the row 
        case 0:
            row = 0;
        case 1:
            row = 1;
        case 2:
            row = 2;
        case 3:
            row = 3;
        case 4:
            row = 4;
        case 5:
            row = 5;
        case 6:
            row = 6;
        case 7:
            row = 7;
        case 8:
            row = 8;
    }

    for(int i = 0; i < 9; i++){
        if(gameBoard[(row*9)+i].getValue() == potNumber){
            return false;
        }
    }
    return true;
}

bool checkCol(Cell* cell, Cell* gameBoard, int potNumber){
    int column;

    switch(int(cell->getCoordinates().x / 55.555f)){                
        case 0:
            column = 0;
        case 1:
            column = 1;
        case 2:
            column = 2;
        case 3:
            column = 3;
        case 4:
            column = 4;
        case 5:
            column = 5;
        case 6:
            column = 6;
        case 7:
            column = 7;
        case 8:
            column = 8;
    }

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
