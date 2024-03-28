#pragma once

#include "components/simple_scene.h"
#include "lab_m1/Tema2/Bullet.h"
#include "lab_m1/Tema2/Turela.h"
#include <iostream>
#include <vector>

using namespace std;

class PlayerTank {
    public:
        float hp;
        float size = 3;
        float angle, timeBulletSpawn;
        glm::vec3 forward;
        glm::vec3 position;
        bool readyToFire, destroyed;
        Turela* turela;
        PlayerTank(float x, float y);
        ~PlayerTank();

        void MoveForward(float distance);
        void RotateRight(float angle);
        void Fire(std::vector<Bullet*>& bullets);
};