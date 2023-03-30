# ![Tower Defense](/data/logoTexture.png)

<!-- TABLE OF CONTENTS -->
<details>
  <summary>Table of Contents</summary>
  <ol>
    <li><a href="#about-the-project">About The Project</a></li>
    <li><a href="#installation">Installation</a></li>
    <li><a href="#wiki">Wiki</a></li>
      <ul>
        <li><a href="#basics">Basics</a></li>
        <li><a href="#towers">Towers</a></li>
        <li><a href="#enemys">Enemys</a></li>
      </ul>
  </ol>
</details>

## About The Project
- ChoasCrystalDefender is a classic TowerDefense game made with SFML writen in C++.
- There are no levels just an open grid where you can place towers. The enemys will ajust the movement automatically to the path that was created.
- Have Fun!
## Installation
- The project is build using SFML and Eigen.
- With the provided CMakeLists.txt you should be able to compile the project on Windows and Linux.
- 

## Wiki
### Basics
- ![Spawn](/data/spawnTexture.png) Spawn
- ![Base](/data/baseTexture.png) Base
- Enemys will spawn at the "Spawn" and move towards the "Base".
- If they have reache the "Base" they will do damage to the "Base".
- If the Health of the Base is 0 indicated by the healthbar in the top rigth corner the game will end.
- The prevent enemys from reaching the base the player can place 5 unique towers that will attack the enemys.
### Towers
- ![Zapper](/data/zapperIconTexture.png) Zapper
  - Zapper is a single target tower that does damage to one enemy at a time.
- ![Pulser](/data/pulserIconTexture.png) Pulser
  - Pulser is a multi target tower that does damage to all enemys in its range.
- ![Freezer](/data/freezerIconTexture.png) Freezer
  - Freezer is a multi target tower that does no damage but will slow all enemys in its range.
- ![Sniper](/data/sniperIconTexture.png) Sniper
  - Sniper is a single target tower that does high damage but is limited by its speed.
  - Sniper will also add a marker to the enemy that will increase all damage done to this enemy by 1.25 * damage.
- ![Focuser](/data/focuserIconTexture.png) Focuser
  - Focuser is a single target tower that does more damag when attacking the same enemy for extended time.
  - If an enemy is targeted for a long period it will deal high amount of damage that no other tower is capable of.
### Enemys
 - ![Fraber](/data/fraberTexture.png) Fraber
 - ![hermer](/data/hermerIconTexture.png) Hermer
 - ![Tanker](/data/tankerIconTexture.png) Tanker
