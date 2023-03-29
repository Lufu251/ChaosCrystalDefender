#include <overState.h>
#include <globalValues.h>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>

overState::overState(/* args */)
{
    init();
}

void overState::init()
{
    dataH.setTextureDirectory("data", 3);
    dataH.loadFont("arial.ttf");
    dataH.loadTexture("buttonStyle", "buttonStyle.png");
    dataH.loadTexture("gameOver", "gameOverTexture.png");

    music.openFromFile(dataH.texturePath.string() + "/" + "mainSong.wav");
    buttonH.addButton(button(200,200,300,30,"PLAY AGAIN", 30), [this]{stateInfo.setNextState(1);});
    buttonH.addButton(button(200,200,300,30,"EXIT", 30), [this]{g_Running = false;});
    buttonH.setTextStyle(dataH.font, sf::Color::Black);
    buttonH.setButtonStyle(dataH.getTexture("buttonStyle"), 16);
    music.play();
    music.setLoop(true);
    music.setVolume(5);
}

void overState::update(sf::RenderWindow &rWindow, inputHandler &rInputH)
{
    // update loop
    buttonH.updateButtons(rWindow, rInputH);
}

void overState::draw(sf::RenderWindow &rWindow, inputHandler &rInputH)
{
    sf::RectangleShape background;
    background.setTexture(&dataH.getTexture("gameOver"));
    background.setSize(sf::Vector2f(170,42));
    float scale = (rWindow.getSize().x / 400.0f);
    sf::Vector2f positionMid = sf::Vector2f(rWindow.getSize().x/2.0f, rWindow.getSize().y/2.0f);

    buttonH.buttons[0].position.x() = rWindow.getSize().x /2 - buttonH.buttons[0].size.x()/2;
    buttonH.buttons[0].position.y() = rWindow.getSize().y /2 - buttonH.buttons[0].size.y()/2;
    buttonH.buttons[0].size.x() = 400;
    buttonH.buttons[0].size.y() = 60;

    buttonH.buttons[1].position.x() = rWindow.getSize().x /2 - buttonH.buttons[1].size.x()/2;
    buttonH.buttons[1].position.y() = rWindow.getSize().y /2 - buttonH.buttons[1].size.y()/2 + 100;
    buttonH.buttons[1].size.x() = 400;
    buttonH.buttons[1].size.y() = 60;

    background.setPosition(positionMid.x - 80 * scale, positionMid.y - 21 * scale - 300);
    background.setScale(scale, scale);
    
    rWindow.draw(background);
    buttonH.drawButtons(rWindow);
}