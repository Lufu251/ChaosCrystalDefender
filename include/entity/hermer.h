#pragma once

#include <enemy.h>

class hermer : public enemy
{
private:
    /* data */
public:
    hermer(Eigen::Vector2f position, int wave);
};