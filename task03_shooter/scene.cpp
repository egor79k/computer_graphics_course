#include <stdlib.h>
#include <vector>

#include "scene.hpp"


Scene::Scene()
{
	//objects.insert(std::make_shared<Enemy>(glm::vec3(0.5, 0.5, 0.5), glm::vec3(0.0, 0.0, 0.0)));
	srand(42);
}

void Scene::render(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix)
{
	enemies.render(viewMatrix, projectionMatrix);
	fireballs.render(viewMatrix, projectionMatrix);
}


void Scene::update(const int tick)
{
	enemies.update(tick);
	fireballs.update(tick);
}


int Scene::checkCollisions()
{
	return fireballs.checkCollisions(enemies);
}


void Scene::shoot(const glm::vec3& position, const glm::vec3& moveSpeed)
{
	fireballs.spawnFireball(position, moveSpeed);
}