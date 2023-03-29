#include <fraber.h>

fraber::fraber(Eigen::Vector2f position, int wave)
{
    pos = position;
    type = "fraber";
    if(wave <= 20){
        maxHealth = 7 + float(wave * 2.5);
        speed = 25 + float(wave * 0.5);
    }
    else if(wave <= 40){
        maxHealth = 8 + float(wave * 7);
        speed = 25 + float(wave * 0.5);
    }
    else{
        maxHealth = 8 + float(wave * 14);
        speed = 25 + float(wave * 0.5);
    }
    currentHealth = maxHealth;
    size = 20;
}