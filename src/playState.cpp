#include <playState.h>
#include <zapper.h>
#include <enemy.h>
#include <fraber.h>

#include <iostream>

playState::playState(/* args */)
{
    init();
}

void playState::init()
{
    std::cout << "play init \n";
    dataH.setTextureDirectory("data",3);
    dataH.loadFont("arial.ttf");
    dataH.loadTexture("tile1", "tileTexture1.png");
    dataH.loadTexture("tile2", "tileTexture2.png");
    dataH.loadTexture("tile3", "tileTexture3.png");

    dataH.loadTexture("zapperBase", "zapperBaseTexture.png");
    dataH.loadTexture("zapperTop", "zapperTopTexture.png");
    dataH.loadTexture("zapperIcon", "zapperIconTexture.png");

    dataH.loadTexture("focuserBase", "focuserBaseTexture.png");
    dataH.loadTexture("focuserTop", "focuserTopTexture.png");
    dataH.loadTexture("focuserIcon", "focuserIconTexture.png");

    dataH.loadTexture("sniperBase", "sniperBaseTexture.png");
    dataH.loadTexture("sniperTop", "sniperTopTexture.png");
    dataH.loadTexture("sniperIcon", "sniperIconTexture.png");

    dataH.loadTexture("pulser", "pulserTexture.png");

    dataH.loadTexture("freezer", "freezerTexture.png");

    dataH.loadTexture("buttonStyle", "buttonStyle.png");

    dataH.loadTexture("fraber", "fraberTexture.png");
    dataH.loadTexture("hermer", "hermerTexture.png");
    dataH.loadTexture("tanker", "tankerTexture.png");

    dataH.loadTexture("spawnTile", "spawnTexture.png");
    dataH.loadTexture("baseTile", "baseTexture.png");
    dataH.loadTexture("waveCount", "waveCountTexture.png");
    dataH.loadTexture("hourglass", "hourglassTexture.png");
    dataH.loadTexture("selectedTile", "selectedTileTexture.png");
    dataH.loadTexture("upgrade", "upgradeTexture.png");

    dataH.loadTexture("pulserAttack", "pulserAttackTexture.png");
    dataH.loadTexture("freezerAttack", "freezerAttackTexture.png");
    dataH.loadTexture("focuserAttack", "focuserAttackTexture.png");
    dataH.loadTexture("zapperAttack", "zapperAttackTexture.png");
    dataH.loadTexture("sniperAttack", "sniperAttackTexture.png");
    
    dataH.loadTexture("sell", "sellTexture.png");
    dataH.loadTexture("freezed", "freezedTexture.png");
    dataH.loadTexture("targeted", "targetedTexture.png");

    music.openFromFile(dataH.texturePath.string() + "/" + "playMusic.wav");
    music.play();
    music.setLoop(true);
    music.setVolume(5);
    buttonH.addButton(button(60,6,100,20,"SKIP TIMER", 12), [this]{gameAssets.nextWave = 0;});
    buttonH.setTextStyle(dataH.font, sf::Color::Black);
    buttonH.setButtonStyle(dataH.getTexture("buttonStyle"), 16);

    gameAssets.grid.setTileSize(32);

    gameAssets.grid.calculateFlowfield();

    std::cout << "init" << std::endl;
    gameH.generateWave(gameAssets);
}

void playState::update(sf::RenderWindow &rWindow, inputHandler &rInputH)
{
    // get elapsed time
    sf::Time elapsed = clock.restart();

    // update the View according to the winodws size
    gameView.reset(sf::FloatRect(0.f, 0.f, float(rWindow.getSize().x), float(rWindow.getSize().y)));
    guiView.reset(sf::FloatRect(0.f, 0.f, float(rWindow.getSize().x), float(rWindow.getSize().y)));
    gameView.updateView();
    guiView.updateView();

    moveView(rInputH, gameView);
    zoomView(rInputH, gameView);

    // set view
    rWindow.setView(gameView.view);

    buttonH.updateButtons(rWindow, rInputH);

    gameH.checkCrystalIsDead(gameAssets, stateInfo);
    gameH.updateWave(gameAssets);
    gameH.updateHoveredTower(gameAssets, rInputH, rWindow);
    gameH.updateSelectedTile(gameAssets, rInputH, rWindow);
    gameH.updateSelectedTower(gameAssets, rInputH, rWindow);
    gameH.checkMenuButtonPressed(gameAssets, rInputH, rWindow);
    gameH.updateGameCooldowns(gameAssets, elapsed);

    enemyH.updateStatus(gameAssets, elapsed);
    enemyH.moveEnemys(gameAssets.enemys, gameAssets.grid, elapsed);
    enemyH.isAtBase(gameAssets);

    towerH.checkAttackedEnemyIsDead(gameAssets);
    towerH.updateCooldown(gameAssets.towers, elapsed);
    towerH.attack(gameAssets);
    towerH.calculateRotation(gameAssets);

    attackH.updateTime(gameAssets, elapsed);
    attackH.doDamage(gameAssets);
    attackH.checkTime(gameAssets);
    attackH.checkDeadEnemyAndSetLastEnemyPosition(gameAssets);

    // remove all dead enemys
    enemyH.removeDead(gameAssets);

    // remove all dead attacks
    attackH.removeDeadAttacks(gameAssets);

    // update entities vector
    gameAssets.entities.clear();
    for(int i=0; i<gameAssets.enemys.size(); i++){
        gameAssets.entities.push_back(gameAssets.enemys.at(i).get());
    }
    for(int i=0; i<gameAssets.towers.size(); i++){
        gameAssets.entities.push_back(gameAssets.towers.at(i).get());
    }
}

void playState::draw(sf::RenderWindow &rWindow, inputHandler &rInputH)
{
    // draw game assets
    rWindow.setView(gameView.view);
    tileR.renderTiles(rWindow, dataH, gameAssets.grid);
    guiR.renderSelectedTower(rWindow,gameAssets, gameH, dataH);
    entityR.renderEntities(rWindow, dataH, gameAssets.entities);
    guiR.renderTowerRange(rWindow,gameAssets, gameH);
    attackR.renderAttacks(rWindow,gameAssets, dataH);
    guiR.renderGameMenu(rWindow,gameAssets, gameH, dataH);

    // draw gui asstes
    rWindow.setView(guiView.view);
    guiR.renderBaseHealth(rWindow,gameAssets, dataH);
    guiR.renderMoney(rWindow,gameAssets, dataH);
    guiR.renderWaveDisplay(rWindow,gameAssets, dataH);
    guiR.renderMessage(rWindow,gameAssets, gameH, dataH);
    buttonH.drawButtons(rWindow);
}

void playState::moveView(inputHandler &rInputH, dachView &rDachView){
    Eigen::Vector2f position = rInputH.getMousePosition().cast<float>() * rDachView.zoomFactor;
    if(rInputH.isMousePressed("right")){
        if(position != positionOld){
            rDachView.move(positionOld.x() - position.x(), positionOld.y() - position.y());
        }
    }
    positionOld = position;
}

void playState::zoomView(inputHandler &rInputH, dachView &rDachView){
    float ticks = float(rInputH.getMouseWeelState());
    if(ticks != 0){
        rDachView.zoom(ticks/10);
    }
}