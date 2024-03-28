#pragma once

#include "components/simple_scene.h"
#include "lab_m1/Tema2/Bullet.h"
#include "lab_m1/Tema2/PlayerTank.h"
#include "lab_m1/Tema2/MovementState.h"
#include "lab_m1/Tema2/Turela.h"
#include <vector>
#include <iostream>
#include <random>
#include <map>
#include <string>
#include <glm/gtx/vector_angle.hpp>

using namespace std;

class EnemyTank {
    public:
        bool imobil;
        float hp = 0;
        float size = 3;
        float timeState = 0.f;
        MovementState state;
        float angle, timeBulletSpawn = 0;
        glm::vec3 forward, position;
        bool readyToFire;
        std::vector<Bullet*> bullets;
        Turela* turela;

        EnemyTank();
        ~EnemyTank();

        void MoveForward(float distance);
        void RotateRight(float angle);
        void Fire(std::vector<Bullet*>& bullets);
        void CreateRandomPosition();
        void Move(float distance);
        void Attack(PlayerTank* player, float angle, std::vector<Bullet*>& bullets);
};