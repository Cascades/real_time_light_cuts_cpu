#pragma once
#include "glm/vec3.hpp"

struct UBO
{
	glm::vec3 color;
	glm::vec3 Ka;
	glm::vec3 Kd;
	glm::vec3 Ke;
	glm::vec3 Ks;
};
