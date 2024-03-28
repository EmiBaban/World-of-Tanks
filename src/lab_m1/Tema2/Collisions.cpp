#include "Collisions.h"

using namespace std;
using namespace m1;

Collisions::Collisions()
{
}

Collisions::~Collisions()
{
}

void Collisions::BulletTankCollision(Bullet* bullet, EnemyTank* enemy, int& score) {
    if (bullet->position.x > enemy->position.x - enemy->size / 2 &&
        bullet->position.x < enemy->position.x + enemy->size / 2 &&
        bullet->position.z > enemy->position.z - enemy->size / 2 &&
        bullet->position.z < enemy->position.z + enemy->size / 2 &&
        !enemy->imobil
        ) {
        bullet->toBeErased = true;
        enemy->hp++;

        if (enemy->hp == 5) {
            enemy->imobil = true;
            score += 1;
        }
    }   
}

void Collisions::BulletPlayerCollision(Bullet* bullet, PlayerTank* player) {
    if (bullet->position.x > player->position.x - player->size / 2 &&
        bullet->position.x < player->position.x + player->size / 2 &&
        bullet->position.z > player->position.z - player->size / 2 &&
        bullet->position.z < player->position.z + player->size / 2
        ) {
        bullet->toBeErased = true;
        player->hp += 0.25f;

        if (player->hp >= 5) {
            player->destroyed = true;
        }
    }
}

void Collisions::PlayerEnemyCollision(PlayerTank* player, EnemyTank* enemy, implemented::Camera* camera)
{
    glm::vec3 diff = player->position - enemy->position;
    float distance = glm::length(diff);

    if (distance < player->size / 2 + enemy->size / 2) {
        float P = (player->size / 2 + enemy->size / 2 - distance);
        glm::vec3 direction = glm::normalize(diff);
        glm::vec3 displacement = P * direction;

        player->position += displacement * 0.5f;
        camera->position += displacement * 0.5f;
        enemy->position += displacement * -0.5f;
    }
}

void Collisions::EnemyEnemyCollision(EnemyTank* enemy1, EnemyTank* enemy2)
{
    glm::vec3 diff = enemy1->position - enemy2->position;
    float distance = glm::length(diff);

    if (distance < enemy1->size / 2 + enemy2->size / 2) {
        float P = (enemy1->size / 2 + enemy2->size / 2 - distance);
        glm::vec3 direction = glm::normalize(diff);
        glm::vec3 displacement = P * direction;

        enemy1->position += displacement * 0.5f;
        enemy2->position += displacement * -0.5f;
    }
}


void Collisions::PlayerBuildingsCollision(PlayerTank* player, Building* building, implemented::Camera* camera) {
    glm::vec3 diff = player->position - building->position;
    float distance = glm::length(diff);

    float halfLength = building->length / 2 - building->length / 8;
    float halfWidth = building->width / 2 - building->width / 8;

    float diffX = std::max(0.0f, std::abs(diff.x) - halfLength);
    float diffZ = std::max(0.0f, std::abs(diff.z) - halfWidth);

    if (diffX < player->size / 2 && diffZ < player->size / 2) {
        float penetrationX = player->size / 2 - diffX;
        float penetrationZ = player->size / 2 - diffZ;

        if (penetrationX < penetrationZ) {
            float normalX = (diff.x < 0.0f) ? -1.0f : 1.0f;
            player->position.x += penetrationX * normalX;
            camera->position.x += penetrationX * normalX;
        }
        else {
            float normalZ = (diff.z < 0.0f) ? -1.0f : 1.0f;
            player->position.z += penetrationZ * normalZ;
            camera->position.z += penetrationZ * normalZ;
        }
    }
}

void Collisions::EnemyBuildingsCollision(EnemyTank* enemy, Building* building) {
    glm::vec3 diff = enemy->position - building->position;
    float distance = glm::length(diff);

    float halfLength = building->length / 2 - building->length / 8;
    float halfWidth = building->width / 2 - building->width / 8;

    float diffX = std::max(0.0f, std::abs(diff.x) - halfLength);
    float diffZ = std::max(0.0f, std::abs(diff.z) - halfWidth);

    if (diffX < enemy->size / 2 && diffZ < enemy->size / 2) {
        float penetrationX = enemy->size / 2 - diffX;
        float penetrationZ = enemy->size / 2 - diffZ;

        if (penetrationX < penetrationZ) {
            float normalX = (diff.x < 0.0f) ? -1.0f : 1.0f;
            enemy->position.x += penetrationX * normalX;
        }
        else {
            float normalZ = (diff.z < 0.0f) ? -1.0f : 1.0f;
            enemy->position.z += penetrationZ * normalZ;
        }
    }
}

void Collisions::BulletBuildingsCollision(Bullet* bullet, Building* building) {
    if (bullet->position.x > building->position.x - building->length / 2 &&
        bullet->position.x < building->position.x + building->length / 2 &&
        bullet->position.z > building->position.z - building->width / 2 &&
        bullet->position.z < building->position.z + building->width / 2
        ) {
        bullet->toBeErased = true;
    }
}
