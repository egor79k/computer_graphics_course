#ifndef TASK03_SHOOTER_SCENE_H
#define TASK03_SHOOTER_SCENE_H

//#include <GL/glew.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
/*
#include <common/shader.hpp>
#include <common/texture.hpp>
#include <common/controls.hpp>
#include <common/objloader.hpp>*/

#include "objects.hpp"


class Scene
{
public:
	Scene();

	void render(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix);
	void update(const int tick);
	int checkCollisions();
	void shoot(const glm::vec3& position, const glm::vec3& moveSpeed);

private:
	Enemies enemies;
	Fireballs fireballs;
};

#endif // TASK03_SHOOTER_SCENE_H