#include <entityRenderer.h>

entityRenderer::entityRenderer(/* args */)
{
}

entityRenderer::~entityRenderer()
{
}


void entityRenderer::renderEntities(sf::RenderWindow& rWindow, dataHandler& rDataH, std::vector<entity*>& rEntities){

    for(int i=0; i < rEntities.size(); i++){
        std::string type = rEntities.at(i)->type;
        std::string category = rEntities.at(i)->category;

        if(category == "enemy"){
            // ------
            // enemy
            // ------
            enemy* enemyPtr = static_cast<enemy*>(rEntities.at(i));

            sf::RectangleShape EnemyShape;
            sf::RectangleShape healthBarSlider;
            sf::RectangleShape healthBarBackground;

            sf::Sprite freezedSprite;
            sf::Sprite targetedSprite;

            EnemyShape.setOrigin(enemyPtr->size/2, enemyPtr->size/2);
            EnemyShape.setPosition(enemyPtr->pos.x(), enemyPtr->pos.y());
            EnemyShape.setSize(sf::Vector2f(enemyPtr->size, enemyPtr->size));

            healthBarBackground.setFillColor(sf::Color(0, 0, 0, 200));
            healthBarSlider.setFillColor(sf::Color(255, 0, 0, 255));
            healthBarBackground.setPosition(enemyPtr->pos.x() - enemyPtr->size/2, enemyPtr->pos.y() + enemyPtr->size /2 + 1);
            healthBarSlider.setPosition(enemyPtr->pos.x() - enemyPtr->size/2, enemyPtr->pos.y() + enemyPtr->size /2 + 1);
            healthBarBackground.setSize(sf::Vector2f(enemyPtr->size, 1));

            float proportionalHealth = enemyPtr->currentHealth / enemyPtr->maxHealth;
            float realWidth = enemyPtr->size * proportionalHealth;
            healthBarSlider.setSize(sf::Vector2f(realWidth, 1));

            freezedSprite.setOrigin(rEntities.at(i)->size/2, rEntities.at(i)->size/2);
            EnemyShape.setPosition(rEntities.at(i)->pos.x(), rEntities.at(i)->pos.y());

            if(type == "fraber"){
                EnemyShape.setTexture(&rDataH.getTexture("fraber"));
            }
            if(type == "tanker"){
                EnemyShape.setTexture(&rDataH.getTexture("tanker"));
            }
            if(type == "hermer"){
                EnemyShape.setTexture(&rDataH.getTexture("hermer"));
            }

            rWindow.draw(healthBarBackground);
            rWindow.draw(healthBarSlider);
            rWindow.draw(EnemyShape);

            if(enemyPtr->freezed == true){
                freezedSprite.setOrigin(float(rDataH.getTexture("freezed").getSize().x/2), float(rDataH.getTexture("freezed").getSize().y/2));
                freezedSprite.setPosition(rEntities.at(i)->pos.x(), rEntities.at(i)->pos.y());
                freezedSprite.setTexture(rDataH.getTexture("freezed"));
                freezedSprite.setColor(sf::Color(255,255,255,200));
                rWindow.draw(freezedSprite);
            }
            if(enemyPtr->targeted == true){
                targetedSprite.setOrigin(float(rDataH.getTexture("freezed").getSize().x/2), float(rDataH.getTexture("freezed").getSize().y/2));
                targetedSprite.setPosition(rEntities.at(i)->pos.x(), rEntities.at(i)->pos.y());
                targetedSprite.setTexture(rDataH.getTexture("targeted"));
                targetedSprite.setColor(sf::Color(255,255,255,200));
                rWindow.draw(targetedSprite);
            }
        }
        // ------
        // tower
        // ------
        else if(category == "tower"){
            tower* towerPtr = static_cast<tower*>(rEntities.at(i));
            sf::RectangleShape towerTopShape;
            sf::RectangleShape towerBaseShape;
            sf::Text levelText;
            bool renderTop = false;

            towerTopShape.setOrigin(towerPtr->size/2, towerPtr->size/2);
            towerTopShape.setPosition(towerPtr->pos.x(), towerPtr->pos.y());
            towerTopShape.setRotation(towerPtr->rotation);
            towerTopShape.setSize(sf::Vector2f(towerPtr->size, towerPtr->size));

            towerBaseShape.setOrigin(towerPtr->size/2, towerPtr->size/2);
            towerBaseShape.setPosition(towerPtr->pos.x(), towerPtr->pos.y());
            towerBaseShape.setSize(sf::Vector2f(towerPtr->size, towerPtr->size));

            levelText.setFont(rDataH.font);
            levelText.setPosition(towerPtr->pos.x() + towerPtr->size/2 -8, towerPtr->pos.y() + towerPtr->size/2 -10);
            levelText.setCharacterSize(32);
            levelText.setScale(0.24f,0.24f);
            levelText.setString(std::to_string(towerPtr->level));
            levelText.setFillColor(sf::Color::White);
            levelText.setOutlineThickness(2);
            levelText.setOutlineColor(sf::Color::Black);

            if(type == "zapper"){
                towerTopShape.setTexture(&rDataH.getTexture("zapperTop"));
                towerBaseShape.setTexture(&rDataH.getTexture("zapperBase"));
                renderTop = true;
            }
            else if(type == "pulser"){
                towerTopShape.setTexture(&rDataH.getTexture("pulserTop"));
                towerBaseShape.setTexture(&rDataH.getTexture("pulserBase"));
                renderTop = true;
            }
            else if(type == "freezer"){
                towerTopShape.setTexture(&rDataH.getTexture("freezerTop"));
                towerBaseShape.setTexture(&rDataH.getTexture("freezerBase"));
                renderTop = true;
            }
            else if(type == "focuser"){
                towerTopShape.setTexture(&rDataH.getTexture("focuserTop"));
                towerBaseShape.setTexture(&rDataH.getTexture("focuserBase"));
                renderTop = true;
            }
            else if(type == "sniper"){
                towerTopShape.setTexture(&rDataH.getTexture("sniperTop"));
                towerBaseShape.setTexture(&rDataH.getTexture("sniperBase"));
                renderTop = true;
            }

            rWindow.draw(towerBaseShape);
            if(renderTop == true){
                rWindow.draw(towerTopShape);
            }
            rWindow.draw(levelText);
        }
    }
}