#pragma once
#include "Turela.h"

Turela::Turela(glm::vec3 forward) {
	this->forward = forward;
    angle = 0;
}

Turela::~Turela() {}

void Turela::RotateRight(float angle) {
    this->angle += angle;

    glm::vec4 newVector = glm::rotate(glm::mat4(1.0f), angle, glm::vec3(0, 1, 0)) * glm::vec4(forward, 1);
    forward = glm::normalize(glm::vec3(newVector));
}