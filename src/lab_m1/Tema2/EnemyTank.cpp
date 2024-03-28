#include "EnemyTank.h"

EnemyTank::EnemyTank() {
    angle = 0.f;
    forward = glm::vec3(0, 0, -1);
    readyToFire = false;
    position = glm::vec3(0);
    state = MovementState::GoingForward;
    imobil = false;
    turela = new Turela(forward);
}

EnemyTank::~EnemyTank() {}

void EnemyTank::CreateRandomPosition() {
    int mapLength = 25;
    int sign, sign2;

    sign = rand() % 10;
    sign2 = rand() % 10;

    if (sign % 2 == 0) {
        sign = -1;
    }
    else {
        sign = 1;
    }

    if (sign2 % 2 == 0) {
        sign2 = -1;
    }
    else {
        sign2 = 1;
    }

    position.x = sign * (rand() % mapLength);
    position.z = sign * (rand() % mapLength);
    position.y = 0;
}

void EnemyTank::MoveForward(float distance) {
    if (!imobil) {
        glm::vec3 dir = glm::normalize(glm::vec3(forward.x, 0, forward.z));
        position += dir * distance;
    }
}

void EnemyTank::RotateRight(float angle) {
    if (!imobil) {
        this->angle += angle;
        glm::vec4 newVector = glm::rotate(glm::mat4(1.0f), angle, glm::vec3(0, 1, 0)) * glm::vec4(forward, 1);
        forward = glm::normalize(glm::vec3(newVector));

        glm::vec4 newVector2 = glm::rotate(glm::mat4(1.0f), angle, glm::vec3(0, 1, 0)) * glm::vec4(turela->forward, 1);
        turela->forward = glm::normalize(glm::vec3(newVector2));
    }
}

void EnemyTank::Move(float distance) {
    if (!imobil) {
        float cameraSpeed = 3.0f;

        timeState += distance;

        if (timeState >= 5) {
            state = GetNextMovementState(state);
            timeState = 0.f;
        }

        if (GetMovementStateName(state) == "GoingForward") {
            MoveForward(-distance);
        }
        else if (GetMovementStateName(state) == "GoingBackward") {
            MoveForward(distance);
        }
        else if (GetMovementStateName(state) == "InPlaceRotationLeft") {
            RotateRight(distance * 0.5f);
        }
        else {
            RotateRight(-distance * 0.5f);
        }
    }
}

void EnemyTank::Attack(PlayerTank* player, float deltaTimeSeconds, std::vector<Bullet*>& bullets) {
    if (!imobil) {
        float distance = glm::distance(position, player->position);
        glm::vec3 direction = normalize(position - player->position);
        float angle = orientedAngle(normalize(turela->forward), normalize(direction), glm::vec3(0, 1, 0));
      
        if (distance <= 16) {
            
            if (angle > 0.1f) {
                turela->RotateRight(deltaTimeSeconds * 2);
            }
            else if (angle < -0.1f) {
                turela->RotateRight(-deltaTimeSeconds * 2);
            }
            else {
                Fire(bullets);
            }
        }
    }
}


void EnemyTank::Fire(std::vector<Bullet*>& bullets) {
    if (!imobil) {
        if (timeBulletSpawn >= 1.f) {
            bullets.push_back(new Bullet(position + -3.2f * turela->forward + glm::vec3(0, 0.9f, 0), -turela->forward));
            timeBulletSpawn = 0.f;
        }
    } 
}