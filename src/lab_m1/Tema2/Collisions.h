#pragma once

#include "lab_m1/Tema2/playerTank.h"
#include "lab_m1/Tema2/EnemyTank.h"
#include "lab_m1/Tema2/Bullet.h"
#include "lab_m1/Tema2/Building.h"
#include "lab_m1/Tema2/lab_camera.h"

#include <vector>
#include <string>
#include <iostream>

namespace m1
{
    class Collisions
    {
    public:
        Collisions();
        ~Collisions();

        static void BulletTankCollision(Bullet* bullet, EnemyTank* enemy, int& score);
        static void PlayerEnemyCollision(PlayerTank* player, EnemyTank* tank, implemented::Camera* camera);
        static void PlayerBuildingsCollision(PlayerTank* player, Building* building, implemented::Camera* camera);
        static void EnemyBuildingsCollision(EnemyTank* enemy, Building* building);
        static void EnemyEnemyCollision(EnemyTank* enemy1, EnemyTank* enemy2);
        static void BulletBuildingsCollision(Bullet* bullet, Building* building);
        static void BulletPlayerCollision(Bullet* bullet, PlayerTank* player);
    };
} // namespace m1
