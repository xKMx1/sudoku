#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <SFML/Graphics.hpp>

using namespace std;

int main()
{
    sf::RenderWindow window(sf::VideoMode(1200, 700), "Sudoku");

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
