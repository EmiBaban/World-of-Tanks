#pragma once

#include "components/simple_scene.h"
#include <iostream>
#include <vector>

using namespace std;

class Turela {
	public:
		glm::vec3 forward;
		float angle;
		Turela(glm::vec3 forward);
		~Turela();

		void RotateRight(float angle);
};
