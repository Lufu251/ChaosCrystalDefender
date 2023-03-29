#include <hermer.h>

hermer::hermer(Eigen::Vector2f position, int wave)
{
    pos = position;
    type = "hermer";
    if(wave <= 15){
        maxHealth = 6  + float(wave * 1);
        speed = 60  + float(wave * 1.5f);
    }
    else if(wave <= 40){
        maxHealth = 6  + float(wave * 3);
        speed = 60  + float(wave * 2.0f);
    }
    else{
        maxHealth = 6  + float(wave * 6);
        speed = 60  + float(wave * 2.5f);
    }
    currentHealth = maxHealth;
    size = 20;
}