#pragma once

#include <vector>
#include <deque>
#include <iostream>
#include <Eigen/Core>
#include <chrono>

#include <tile.h>

class tileGrid
{
private:
    std::vector<tile> data;
    int x_size;
    int y_size;

public:
    Eigen::Vector2i spawn;
    Eigen::Vector2i base;

    int tileSize = 10;

    tileGrid(int x, int y);
    ~tileGrid();

    int getSizeX();
    int getSizeY();
    void resize(int x, int y);
    tile& operator()(size_t i, size_t j);
    const tile& operator()(size_t i, size_t j) const;

    void setTileSize(int size);

    void setSpawnPoint(Eigen::Vector2i spawnPoint);
    void setBasePoint(Eigen::Vector2i basePoint);

    void calculateFlowfield();
};