#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <Eigen/Core>
#include <iostream>

class dachView
{
public:
    sf::View view;
    float zoomFactor = 1;
    Eigen::Vector2f offset{0,0};

    dachView(){
    } 

    dachView(const sf::FloatRect& rectangle){
        view.reset(rectangle);
    }

    void reset(const sf::FloatRect& rectangle){
        view.reset(rectangle);
    }

    void move(float offsetX, float offsetY){
        offset.x() += offsetX;
        offset.y() += offsetY;
    }

    void zoom(float factor){
        zoomFactor += factor;
        if(zoomFactor < 0.1f){
            zoomFactor = 0.1f;
        }
    }

    void updateView(){
        view.move(offset.x(), offset.y());
        view.zoom(zoomFactor);
    }
};