#include <tanker.h>

tanker::tanker(Eigen::Vector2f position, int wave)
{
    pos = position;
    type = "tanker";
    if(wave <= 25){
        maxHealth = 5 + float((wave-1) * 4);
        speed = 25;
    }
    else if(wave <= 45){
        maxHealth = 5 + float(wave* 9);
        speed = 25;
    }
    else if(wave <= 65){
        maxHealth = 5 + float(wave* 18);
        speed = 25 + float((wave-40) * 0.2);
    }
    else{
        maxHealth = 50 + float(wave* 25);
        speed = 25 + float((wave-40) * 0.2);
    }
    currentHealth = maxHealth;
    size = 20;
}