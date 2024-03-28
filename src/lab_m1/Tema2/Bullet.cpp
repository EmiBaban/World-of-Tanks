#include "Bullet.h"

Bullet::Bullet(glm::vec3 position, glm::vec3 forward) {
	this->position = position;
	this->forward = forward;
	toBeErased = false;
	time = 0;
}

Bullet::~Bullet() {}

void Bullet::MoveForward(float distance) {
	if (isAvailable()) {
		glm::vec3 dir = glm::normalize(glm::vec3(forward.x, 0, forward.z));
		position += dir * distance;
		time += distance;
	}
}

bool Bullet::isAvailable() {
	if (time >= 20) {
		toBeErased = true;
		return false;
	}
	return true;
}