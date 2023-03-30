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
- Have FUN!
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
- ![Pulser](/data/pulserIconTexture.png) Pulser
- ![Freezer](/data/freezerIconTexture.png) Freezer
- ![Sniper](/data/sniperIconTexture.png) Sniper
- ![Focuser](/data/focuserIconTexture.png) Focuser
### Enemys
