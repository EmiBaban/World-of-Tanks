#pragma once

#include "components/simple_scene.h"
#include <iostream>
#include <vector>

using namespace std;

class Bullet {
	public:
		glm::vec3 position, forward;
		float time;
		bool toBeErased;
		Bullet(glm::vec3 position, glm::vec3 forward);
		~Bullet();

		void MoveForward(float distance);
		bool isAvailable();
};