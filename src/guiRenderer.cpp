#include <guiRenderer.h>

void guiRenderer::renderBaseHealth(sf::RenderWindow &rWindow, assets &rGameAsset, dataHandler &rDataH){
    sf::RectangleShape healthBarBackground;
    sf::RectangleShape healthBarSlider;
    sf::Text healthText;

    float barSize = 200;
    float proportialSize = float(rGameAsset.baseHealth) / float(rGameAsset.baseHealthMax) * barSize;

    healthBarBackground.setPosition(rWindow.getSize().x -barSize -10, 10);
    healthBarBackground.setSize(sf::Vector2f(barSize, 12));
    healthBarBackground.setFillColor(sf::Color(255,0,0));
    healthBarBackground.setOutlineColor(sf::Color::Black);
    healthBarBackground.setOutlineThickness(2);

    healthBarSlider.setPosition(rWindow.getSize().x -barSize -10, 10);
    healthBarSlider.setSize(sf::Vector2f(proportialSize, 12));
    healthBarSlider.setFillColor(sf::Color(0,180,0));

    healthText.setFont(rDataH.font);
    healthText.setCharacterSize(12);
    healthText.setFillColor(sf::Color::White);
    healthText.setPosition(float(rWindow.getSize().x) -150,8);
    healthText.setString("BASE HEALTH");

    rWindow.draw(healthBarBackground);
    rWindow.draw(healthBarSlider);
    rWindow.draw(healthText);
}

void guiRenderer::renderMoney(sf::RenderWindow &rWindow, assets &rGameAsset, dataHandler &rDataH){
    sf::Text moneyText;

    moneyText.setFont(rDataH.font);
    moneyText.setCharacterSize(16);
    moneyText.setFillColor(sf::Color::White);
    moneyText.setOutlineThickness(1);
    moneyText.setOutlineColor(sf::Color::Black);
    moneyText.setPosition(10,5);
    moneyText.setString("$" + std::to_string(rGameAsset.money));

    rWindow.draw(moneyText);
}

void guiRenderer::renderWaveDisplay(sf::RenderWindow &rWindow, assets &rGameAsset, dataHandler &rDataH){
    sf::Text waveCountText;
    sf::Text waveTimer;

    sf::Sprite waveCount;
    sf::Sprite hourglass;

    waveCountText.setFont(rDataH.font);
    waveCountText.setCharacterSize(16);
    waveCountText.setOutlineThickness(1);
    waveCountText.setOutlineColor(sf::Color::Black);
    waveCountText.setFillColor(sf::Color::White);
    waveCountText.setPosition(float(rWindow.getSize().x /2) -40,5);
    waveCountText.setString(std::to_string(rGameAsset.waveCount));

    waveCount.setPosition(float(rWindow.getSize().x /2) -60,7);
    waveCount.setTexture(rDataH.getTexture("waveCount"));

    hourglass.setPosition(float(rWindow.getSize().x /2) +15,7);
    hourglass.setTexture(rDataH.getTexture("hourglass"));

    waveTimer.setFont(rDataH.font);
    waveTimer.setCharacterSize(16);
    waveTimer.setOutlineThickness(1);
    waveTimer.setOutlineColor(sf::Color::Black);
    waveTimer.setFillColor(sf::Color::White);
    waveTimer.setPosition(float(rWindow.getSize().x /2) +35,5);
    waveTimer.setString(std::to_string(rGameAsset.nextWave) + "s");

    rWindow.draw(waveCountText);
    rWindow.draw(waveTimer);

    rWindow.draw(hourglass);
    rWindow.draw(waveCount);
}

void guiRenderer::renderTowerRange(sf::RenderWindow &rWindow, assets &rGameAsset, gameHandler &rGameH){
    if(rGameH.indexTowerHovered >= 0){
        tower* hT = rGameAsset.towers.at(rGameH.indexTowerHovered).get();
        sf::CircleShape rangeCircle;
        rangeCircle.setFillColor(sf::Color(255,0,0,10));
        rangeCircle.setOrigin(hT->range, hT->range);
        rangeCircle.setPosition(hT->pos.x(), hT->pos.y());
        rangeCircle.setRadius(hT->range);
        rangeCircle.setOutlineThickness(1);
        rangeCircle.setOutlineColor(sf::Color(255,0,0,100));

        rWindow.draw(rangeCircle);
    }

    if(rGameH.indexTowerSelected >= 0){
        tower* hT = rGameAsset.towers.at(rGameH.indexTowerSelected).get();
        sf::CircleShape rangeCircle;
        rangeCircle.setFillColor(sf::Color(255,0,0,10));
        rangeCircle.setOrigin(hT->range, hT->range);
        rangeCircle.setPosition(hT->pos.x(), hT->pos.y());
        rangeCircle.setRadius(hT->range);
        rangeCircle.setOutlineThickness(1);
        rangeCircle.setOutlineColor(sf::Color(255,0,0,100));

        rWindow.draw(rangeCircle);
    }
}

void guiRenderer::renderSelectedTower(sf::RenderWindow &rWindow, assets &rGameAsset, gameHandler &rGameH, dataHandler &rDataH){
    if(rGameH.xTileSelected != -1 && rGameH.yTileSelected != -1){
        sf::Sprite selectedTile;
        selectedTile.setPosition(float(rGameH.xTileSelected) * rGameAsset.grid.tileSize, float(rGameH.yTileSelected) * rGameAsset.grid.tileSize);
        selectedTile.setTexture(rDataH.getTexture("selectedTile"));

        rWindow.draw(selectedTile);
    }
}

void guiRenderer::renderMessage(sf::RenderWindow &rWindow, assets &rGameAsset, gameHandler &rGameH, dataHandler &rDataH){
    if(rGameH.messageTime != 0){
        sf::Text messageText;
        messageText.setString(rGameH.message);
        messageText.setFont(rDataH.font);
        messageText.setCharacterSize(16);
        messageText.setFillColor(sf::Color::Red);
        messageText.setPosition(10, 30);

        rWindow.draw(messageText);
    }
}

void guiRenderer::renderGameMenu(sf::RenderWindow &rWindow, assets &rGameAsset, gameHandler &rGameH, dataHandler &rDataH){
    if(rGameH.buildMenuActive == true){
        sf::RectangleShape background;
        background.setFillColor(sf::Color(100,100,100,200));
        background.setOutlineThickness(1);
        background.setOutlineColor(sf::Color(50,50,50,200));

        background.setPosition(float(rGameH.buildM.pos.x()), float(rGameH.buildM.pos.y()));
        background.setSize(sf::Vector2f(float(rGameH.buildM.size.x()), float(rGameH.buildM.size.y())));
        rWindow.draw(background);

        for (size_t i = 0; i < rGameH.buildM.buttons.size(); i++)
        {
            menuButton mb = rGameH.buildM.buttons.at(i);
            sf::RectangleShape button;
            sf::Sprite towerImage;
            sf::Text name;

            button.setSize(sf::Vector2f(float(mb.sizeX), float(mb.sizeY)));
            button.setPosition(float(mb.pos.x()), float(mb.pos.y()));
            button.setFillColor(sf::Color(200,200,200,100));
            button.setOutlineThickness(1);
            button.setOutlineColor(sf::Color(50,50,50,200));

            towerImage.setPosition(float(mb.pos.x()) + float(mb.sizeX)/2 -16, float(mb.pos.y()));

            float scale = 0.125;
            name.setFont(rDataH.font);
            name.setPosition(float(mb.pos.x() + 3), float(mb.pos.y() +30));
            name.setCharacterSize(64);
            name.setScale(scale, scale);
            name.setFillColor(sf::Color::Black);

            std::stringstream sstream;
            sstream.precision(4);
            if(mb.action == "zapper"){
                towerImage.setTexture(rDataH.getTexture("zapperIcon"));
                sstream << "zapper" << std::endl;
                sstream << "$: " << rGameH.baseCostZapper << std::endl;
                sstream << "D: " << rGameH.baseDamageZapper << std::endl;
                sstream << "S: " << rGameH.baseSpeedZapper << std::endl;
                sstream << "R: " << rGameH.baseRangeZapper << std::endl;
            }
            else if(mb.action == "pulser"){
                towerImage.setTexture(rDataH.getTexture("pulser"));
                sstream << "pulser" << std::endl;
                sstream << "$: " << rGameH.baseCostPulser << std::endl;
                sstream << "D: " << rGameH.baseDamagePulser << std::endl;
                sstream << "S: " << rGameH.baseSpeedPulser << std::endl;
                sstream << "R: " << rGameH.baseRangePulser << std::endl;
            }
            else if(mb.action == "freezer"){
                towerImage.setTexture(rDataH.getTexture("freezer"));
                sstream << "freezer" << std::endl;
                sstream << "$: " << rGameH.baseCostFreezer << std::endl;
                sstream << "D: " << rGameH.baseDamageFreezer << std::endl;
                sstream << "S: " << rGameH.baseSpeedFreezer << std::endl;
                sstream << "R: " << rGameH.baseRangeFreezer << std::endl;
            }
            else if(mb.action == "focuser"){
                towerImage.setTexture(rDataH.getTexture("focuserIcon"));
                sstream << "focuser" << std::endl;
                sstream << "$: " << rGameH.baseCostFocuser << std::endl;
                sstream << "D: " << rGameH.baseDamageFocuser << std::endl;
                sstream << "S: " << rGameH.baseSpeedFocuser << std::endl;
                sstream << "R: " << rGameH.baseRangeFocuser << std::endl;
            }
            else if(mb.action == "sniper"){
                towerImage.setTexture(rDataH.getTexture("sniperIcon"));
                sstream << "sniper" << std::endl;
                sstream << "$: " << rGameH.baseCostSniper << std::endl;
                sstream << "D: " << rGameH.baseDamageSniper << std::endl;
                sstream << "S: " << rGameH.baseSpeedSniper << std::endl;
                sstream << "R: " << rGameH.baseRangeSniper << std::endl;
            }

            name.setString(sstream.str());
            
            rWindow.draw(button);
            rWindow.draw(towerImage);
            rWindow.draw(name);
        }
    }

    if(rGameH.upgradeMenuActive == true){
        sf::RectangleShape background;
        background.setFillColor(sf::Color(100,100,100,200));
        background.setOutlineThickness(1);
        background.setOutlineColor(sf::Color(50,50,50,200));

        background.setPosition(float(rGameH.upgradeM.pos.x()), float(rGameH.upgradeM.pos.y()));
        background.setSize(sf::Vector2f(float(rGameH.upgradeM.size.x()), float(rGameH.upgradeM.size.y())));
        rWindow.draw(background);

        for (size_t i = 0; i < rGameH.upgradeM.buttons.size(); i++)
        {
            menuButton mb = rGameH.upgradeM.buttons.at(i);
            sf::RectangleShape button;
            sf::Sprite actionImage;
            sf::Text name;

            button.setSize(sf::Vector2f(float(mb.sizeX), float(mb.sizeY)));
            button.setPosition(float(mb.pos.x()), float(mb.pos.y()));
            button.setFillColor(sf::Color(200,200,200,100));
            button.setOutlineThickness(1);
            button.setOutlineColor(sf::Color(50,50,50,200));

            actionImage.setPosition(float(mb.pos.x()) + float(mb.sizeX)/2 -16, float(mb.pos.y()));

            float scale = 0.125;
            name.setFont(rDataH.font);
            name.setPosition(float(mb.pos.x() + 1), float(mb.pos.y() +28));
            name.setCharacterSize(64);
            name.setScale(scale, scale);
            name.setFillColor(sf::Color::Black);

            std::stringstream sstream;
            sstream.precision(4);
            tower* ct = rGameAsset.towers.at(rGameH.indexTowerSelected).get();
            if(mb.action == "upgrade"){
                actionImage.setTexture(rDataH.getTexture("upgrade"));

                sstream << "upgrade" << std::endl;
                sstream << "$: " << ct->currentCost + ct->costAdd << std::endl;
                sstream << "D+: " << ct->damageUpgrade << std::endl;
                sstream << "S+: " << ct->speedUpgrade << std::endl;
                sstream << "R+: " << ct->rangeUpgrade << std::endl;
            }
            else if(mb.action == "sell"){
                actionImage.setTexture(rDataH.getTexture("sell"));

                sstream << "sell" << std::endl;
                sstream << "$: " << ct->currentCost /2 << std::endl;
            }

            name.setString(sstream.str());
            rWindow.draw(button);
            rWindow.draw(actionImage);
            rWindow.draw(name);
        }
        
    }
}