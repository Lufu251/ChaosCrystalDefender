#include <tileRenderer.h>

tileRenderer::tileRenderer(/* args */)
{
}

tileRenderer::~tileRenderer()
{
}

void tileRenderer::renderTiles(sf::RenderWindow& rWindow, dataHandler& rDataH, tileGrid& tg)
{
    float texturePixel = 32;
    float scale = float(tg.tileSize) / texturePixel;
    sf::Sprite tileSprite;

    for(int x=0; x<tg.getSizeX(); x++){
        for(int y=0; y<tg.getSizeY(); y++){

            if(tg(x,y).type == "tile1"){
                tileSprite.setTexture(rDataH.getTexture("tile1"));
            }
            else if(tg(x,y).type == "tile2"){
                tileSprite.setTexture(rDataH.getTexture("tile2"));
            }
            else if(tg(x,y).type == "tile3"){
                tileSprite.setTexture(rDataH.getTexture("tile3"));
            }
            else if(tg(x,y).type == "spawn"){
                tileSprite.setTexture(rDataH.getTexture("spawnTile"));
            }
            else if(tg(x,y).type == "base"){
                tileSprite.setTexture(rDataH.getTexture("baseTile"));
            }
            tileSprite.setScale(scale, scale);
            tileSprite.setPosition(sf::Vector2f(float(x) * float(tg.tileSize), float(y) * float(tg.tileSize)));
            rWindow.draw(tileSprite);
        }
    }
}