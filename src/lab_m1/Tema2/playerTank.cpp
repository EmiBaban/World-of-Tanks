#include "playerTank.h"

PlayerTank::PlayerTank(float x, float z) {
    angle = 0.f;
    forward = glm::vec3(0, 0, -1);
    position = glm::vec3(x, 0, z);
    readyToFire = false;
    timeBulletSpawn = 0.f;
    hp = 0;
    turela = new Turela(forward);
}

PlayerTank::~PlayerTank() {}

void PlayerTank::MoveForward(float distance) {
    glm::vec3 dir = glm::normalize(glm::vec3(forward.x, 0,forward.z));
    position += dir * distance;
}

void PlayerTank::RotateRight(float angle) {
    this->angle += angle;
    glm::vec4 newVector = glm::rotate(glm::mat4(1.0f), angle, glm::vec3(0, 1, 0)) * glm::vec4(forward, 1);
    forward = glm::normalize(glm::vec3(newVector));

    glm::vec4 newVector2 = glm::rotate(glm::mat4(1.0f), angle, glm::vec3(0, 1, 0)) * glm::vec4(turela->forward, 1);
    turela->forward = glm::normalize(glm::vec3(newVector2));
}

void PlayerTank::Fire(std::vector<Bullet*>& bullets) {
    if (timeBulletSpawn >= 1.f) {
        bullets.push_back(new Bullet(position + 3.2f * turela->forward + glm::vec3(0, 1.1f, 0), turela->forward));
        timeBulletSpawn = 0.f;
    }
}