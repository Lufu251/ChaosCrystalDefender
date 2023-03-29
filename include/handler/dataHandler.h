#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <filesystem>
#include <string>
#include <fstream>
#include <iostream>
#include <unordered_map>

#include <pathSearcher.h>


class dataHandler
{
private:
    PathSearcher pS;
    
public:
    std::filesystem::path texturePath;
    std::unordered_map<std::string, sf::Texture> textures;
    std::vector<std::string> worlds;
    sf::Font font;

    dataHandler();

    void loadFont(std::string fileName);
    void setTextureDirectory(std::string name, int depth);
    void setSaveDirectory(std::string name, int depth);
    void loadTexture(std::string name, std::string fileName);
    sf::Texture& getTexture(std::string name);
};