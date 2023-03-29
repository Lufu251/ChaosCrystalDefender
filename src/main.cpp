#include <iostream>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <globalValues.h>
#include <gameState.h>
#include <menuState.h>
#include <stateHandler.h>
#include <inputHandler.h>

// is global value
bool g_Running = true;

void handelEvents(sf::RenderWindow& rWindow, inputHandler& rInputH){
    // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (rWindow.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed){
                rWindow.close();
                std::cout << "window closed \n";
            }
            if (event.type == sf::Event::Resized){
                // update the view to the new size of the window
                rWindow.setSize(sf::Vector2u(event.size.width, event.size.height));
                sf::FloatRect visibleArea(0, 0, float(event.size.width), float(event.size.height));
                rWindow.setView(sf::View(visibleArea));
            }
            if (event.type == sf::Event::MouseWheelMoved)
            {
                rInputH.updateMouseWeel(-event.mouseWheel.delta);
            }
        }
}



int main()
{
    g_Running = true;
    sf::RenderWindow window(sf::VideoMode(1200, 900), "Tower Defense", sf::Style::Default, sf::ContextSettings(0, 0, 4, 1, 1, 0, false));
    window.setFramerateLimit(60);
    std::unique_ptr<gameState> state = std::make_unique<menuState>();
    stateHandler stateH;
    inputHandler inputH;

    inputH.newMouseButton("left", sf::Mouse::Left);
    inputH.newMouseButton("right", sf::Mouse::Right);
    inputH.newMouseButton("middle", sf::Mouse::Middle);

    while (window.isOpen() && g_Running)
    {
        inputH.update(window);

        // clear windows
        window.clear(sf::Color(100,100,110));

        // update all assets
        
        handelEvents(window, inputH);

        state->update(window, inputH);
        state->draw(window, inputH);

        stateH.checkState(state);

        // draw to the screen
        window.display();


        inputH.updateState();
    }


    return 0;
}