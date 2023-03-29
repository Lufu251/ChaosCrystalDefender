#include <attackRenderer.h>

void attackRenderer::renderAttacks(sf::RenderWindow &rWindow, assets &rGameAsset, dataHandler& rDataH){
    for (size_t i = 0; i < rGameAsset.attacks.size(); i++)
    {
        std::string type = rGameAsset.attacks[i]->type;
        if(type == "zapperAttack"){
            zapperAttack* a = static_cast<zapperAttack*>(rGameAsset.attacks[i].get());
            sf::RectangleShape line;
            if(a->enemyIsDead == false){
                line = drawLine(sf::Vector2f(a->e->pos.x(), a->e->pos.y()), sf::Vector2f(a->t->pos.x(), a->t->pos.y()), 2.0f, sf::Color(255,255,255,255));
            }
            else{
                line = drawLine(a->lastEnemyPosition, sf::Vector2f(a->t->pos.x(), a->t->pos.y()), 2.0f, sf::Color(255,255,255,255));
            }
            line.setTexture(&rDataH.getTexture("zapperAttack"));
            rWindow.draw(line);
        }
        else if(type == "pulserAttack"){
            pulserAttack* a = static_cast<pulserAttack*>(rGameAsset.attacks[i].get());

            float scale = a->currenttime / a->maxTime;

            sf::CircleShape circle;
            circle.setPosition(a->t->pos.x(), a->t->pos.y());
            circle.setRadius(a->t->range);
            circle.setScale(scale,scale);
            circle.setFillColor(sf::Color(255,255,255,60));
            circle.setOrigin(a->t->range, a->t->range);
            circle.setTexture(&rDataH.getTexture("pulserAttack"));
            rWindow.draw(circle);
        }
        else if(type == "freezerAttack"){
            freezerAttack* a = static_cast<freezerAttack*>(rGameAsset.attacks[i].get());

            float scale = a->currenttime / a->maxTime;
            
            sf::CircleShape circle;
            circle.setPosition(a->t->pos.x(), a->t->pos.y());
            circle.setRadius(a->t->range);
            circle.setScale(scale,scale);
            circle.setFillColor(sf::Color(200,200,200,100));
            circle.setOrigin(a->t->range, a->t->range);
            circle.setTexture(&rDataH.getTexture("freezerAttack"));
            rWindow.draw(circle);
        }
        else if(type == "sniperAttack"){
            sniperAttack* a = static_cast<sniperAttack*>(rGameAsset.attacks[i].get());
            sf::RectangleShape line;
            if(a->enemyIsDead == false){
                line = drawLine(sf::Vector2f(a->e->pos.x(), a->e->pos.y()), sf::Vector2f(a->t->pos.x(), a->t->pos.y()), 2.0f, sf::Color(255,255,255,255));
            }
            else{
                line = drawLine(a->lastEnemyPosition, sf::Vector2f(a->t->pos.x(), a->t->pos.y()), 2.0f, sf::Color(255,255,255,255));
            }
            line.setTexture(&rDataH.getTexture("sniperAttack"));
            rWindow.draw(line);
        }
        else if(type == "focuserAttack"){
            focuserAttack* a = static_cast<focuserAttack*>(rGameAsset.attacks[i].get());
            sf::RectangleShape line;
            if(a->enemyIsDead == false){
                line = drawLine(sf::Vector2f(a->e->pos.x(), a->e->pos.y()), sf::Vector2f(a->t->pos.x(), a->t->pos.y()), 5.0f, sf::Color(255,255,255,200));
            }
            else{
                line = drawLine(a->lastEnemyPosition, sf::Vector2f(a->t->pos.x(), a->t->pos.y()), 5.0f, sf::Color(255,255,255,200));
            }
            line.setTexture(&rDataH.getTexture("focuserAttack"));
            rWindow.draw(line);
        }

    }

}

sf::RectangleShape attackRenderer::drawLine(sf::Vector2f startPoint, sf::Vector2f endPoint, float thickness, sf::Color color)
{
    // calculate the length and angle of the line
    float length = float(std::sqrt(std::pow(endPoint.x - startPoint.x, 2) + std::pow(endPoint.y - startPoint.y, 2)));
    float angle = float(std::atan2(endPoint.y - startPoint.y, endPoint.x - startPoint.x) * 180 / M_PI);

    // create the rectangle shape
    sf::RectangleShape rectangle(sf::Vector2f(length, thickness));
    rectangle.setFillColor(color);
    rectangle.setOrigin(0, thickness/2);

    // set the position and rotation of the rectangle
    rectangle.setPosition(startPoint);
    rectangle.setRotation(angle);

    return rectangle;
}