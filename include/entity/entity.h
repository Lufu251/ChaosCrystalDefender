#pragma once

#include <Eigen/Core>

class entity
{

public:
    Eigen::Vector2f pos;
    std::string type;
    std::string category;
    float size;
    
    virtual ~entity() = default;
};