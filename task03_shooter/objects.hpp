#ifndef TASK03_SHOOTER_OBJECTS_H
#define TASK03_SHOOTER_OBJECTS_H

#include <set>
#include <memory>

#include <GL/glew.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <glm/gtx/norm.hpp>

#include <common/shader.hpp>
#include <common/texture.hpp>
#include <common/controls.hpp>
#include <common/objloader.hpp>


class CollidableObject
{
public:
	glm::vec3 position;
	glm::vec3 rotation;
	float colliderRadius;

	bool isCollides(CollidableObject* other);
};


class Enemy : public CollidableObject
{
public:
	Enemy(const glm::vec3& position, const glm::vec3& rotation);
	void update();

	int anchor = 0.0;
	float yAmplitude = 0.5;
	float rotationSpeed = 0.02;
	float floatingSpeed = 0.02;
};


class Fireball : public CollidableObject
{
public:
	Fireball(const glm::vec3& position, const glm::vec3& moveSpeed_, const glm::vec3& rotationSpeed_);
	void update();

	glm::vec3 moveSpeed;
	glm::vec3 rotationSpeed;
};


class Enemies
{
public:
	Enemies();
	~Enemies();

	void render(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix);
	void update(const int tick);
	void spawnEnemy();
	void killEnemy(const std::shared_ptr<Enemy>& enemy);
	const std::set<std::shared_ptr<Enemy>>& getSet() const;

private:
	GLuint programID;
	GLuint matrixID;
	GLuint vertexbuffer;
	GLuint colorbuffer;

	std::set<std::shared_ptr<Enemy>> enemies;

	static const char VERTEX_SHADER[];
	static const char FRAGMENT_SHADER[];

	static const int MIN_ENEMY_SPAWN_DISTANCE;
	static const int MAX_ENEMY_SPAWN_DISTANCE;
	static const int ENEMY_SPAWN_FREQUENCY;
	static const int MAX_ENEMY_COUNT;
};


class Fireballs
{
public:
	Fireballs();
	~Fireballs();

	void render(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix);
	void update(const int tick);
	void spawnFireball(const glm::vec3& position, const glm::vec3& moveSpeed);
	int checkCollisions(Enemies& enemies);

private:
	GLuint programID;
	GLuint matrixID;
	GLuint texture;
	GLuint textureID;
	GLuint vertexbuffer;
	GLuint uvbuffer;
	size_t vertices_size;

	std::set<std::shared_ptr<Fireball>> fireballs;

	static const char FIREBALL_VERTEX_SHADER[];
	static const char FIREBALL_FRAGMENT_SHADER[];
	static const char FIREBALL_TEXTURE[];
	static const char FIREBALL_OBJECT_MESH[];

	static const int MAX_FIREBALL_COUNT;
	static const int FIREBALL_SPAWN_FREQUENCY;
	static const int MAX_FIREBALL_DISTANCE;
};

#endif // TASK03_SHOOTER_OBJECTS_H