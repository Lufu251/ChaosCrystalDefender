#include <dataHandler.h>

dataHandler::dataHandler(){

}

void dataHandler::loadFont(std::string fileName){
    if (!font.loadFromFile(texturePath.string() + "/" + fileName))
    {
        std::cout << "couldn't load font";
    }
}

void dataHandler::setTextureDirectory(std::string name, int depth){
    texturePath = pS.getDirPath(name, depth);
}

void dataHandler::loadTexture(std::string name, std::string fileName){
    sf::Texture texture;
    if(!texture.loadFromFile(texturePath.string() + "/" + fileName)){
        std::cout << fileName << " could not load \n";
    }
    textures.insert(std::make_pair(name, texture));
}

sf::Texture& dataHandler::getTexture(std::string name){
    if(textures.count(name) == 0){
        std::cout << "texture does not exist or was not yet loaded" << "\n";
        return textures["null"];
    }
    else{
        return textures[name];
    }
}