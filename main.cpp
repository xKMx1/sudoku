#include <iostream>
#include <SFML/Graphics.hpp>
#include <ctime>
#include <windows.h>

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

        int getNum(){
            return mCellNumber;
        }

        sf::RectangleShape getSprite(){
            return mSprite;
        }
};

bool checkRow(Cell* cell, Cell* gameBoard, int potNumber){
    int row = int(cell->getCoordinates().y / 55.555f);

    for(int i = 0; i < 9; i++){
        if(gameBoard[(row*9)+i].getValue() == potNumber){
            return false;
        }
    }
    // std::cout << row << " | " << potNumber << " | Row" << std::endl;
    // Sleep(500);
    return true;
}

bool checkCol(Cell* cell, Cell* gameBoard, int potNumber){
    int column = int(cell->getCoordinates().x / 55.555f);
    
    for(int i = 0; i < 9; i++){
        if(gameBoard[(i*9) + column].getValue() == potNumber){
            return false;
        }
    }
    std::cout << column << " | " << potNumber << " | Column" << std::endl;
    // Sleep(500);
    return true;
}

bool checkNonet(Cell* cell, Cell* gameBoard, int potNumber){
    int nonetX;
    int nonetY;

    if(int(cell->getCoordinates().x / 55.555f) <= 2){           //if to determine the x coordinate of nonet
        nonetX = 0;
    }
    else if(int(cell->getCoordinates().x / 55.555f) <= 5){
        nonetX = 1;
    }
    else{
        nonetX = 2;
    }

    if(int(cell->getCoordinates().y / 55.555f) <= 2){           //if to determine the y coordinate of nonet
        nonetY = 0;
    }
    else if(int(cell->getCoordinates().y / 55.555f) <= 5){
        nonetY = 1;
    }
    else{
        nonetY = 2;
    }

    std::cout << nonetX << " | " << nonetY << std::endl;

    for(int i = nonetX * 3; i < 3 * nonetX + 3; i++){                                         
        for(int j = nonetY * 3; j < 3 * nonetY + 3; j++){                                
            if(gameBoard[(j*9) + i].getValue() == potNumber){
                std::cout << potNumber << " Bad" << std::endl;
                return false;
            }
        }
    }

    std::cout << potNumber << " Good" << std::endl;
    return true;
}

void checkCell(Cell* cell, Cell* gameBoard, int potNumber){
    if(checkRow(cell, gameBoard, potNumber)){                // nested ifs, checking if number is valide in row, column and nonet(3x3)
        if(checkCol(cell, gameBoard, potNumber)){
            if(checkNonet(cell, gameBoard, potNumber)){
                cell->setValue(potNumber);
                // std::cout << board[(i*9)+j].getValue() << " " << (i*9)+j << std::endl;
                // Sleep(250);
            }
            else{
                cout << potNumber << "Nonet Error" << std::endl;
            }
        }
        else{
            cout << potNumber << "Column Error" << std::endl;
        }
    }
    else{
        cout << potNumber << "Row Error" << std::endl;
    }
}


Cell* generateBoard(){
    std::srand(std::time(nullptr));
    int potNumber;

    Cell* board = new Cell[81];
    
    for(int i = 0; i < 9; i++){                                                 // y coordinates loop
        for(int j = 0; j < 9; j++){                                             // x coordinates loop
            board[(i*9)+j].setCoordinates(j * 55.555f, i * 55.555f);
            board[(i*9)+j].initCell((i*9)+j);

            while(!board[(i*9)+j].getValue()){                                  // as long as cell is 0 (without value) it will generate new numbers, check if they are valid and fill the cell with valid number
                potNumber = 1 + rand() % 9;                                     // function is biased but we dont care
                checkCell(&board[(i*9)+j], board, potNumber);
            }
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
