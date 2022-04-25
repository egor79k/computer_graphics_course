#include <stdio.h>
#include <vector>

#include "objects.hpp"
#include "enemy_model.hpp"


bool CollidableObject::isCollides(CollidableObject* other)
{
	return glm::distance(position, other->position) < colliderRadius + other->colliderRadius;
}


Enemy::Enemy(const glm::vec3& position, const glm::vec3& rotation) :
	CollidableObject{position, rotation, 1.0}
{}


void Enemy::update()
{
	position[1] += floatingSpeed;

	if (position[1] > anchor + yAmplitude || position[1] < anchor - yAmplitude)
	{
		floatingSpeed *= -1;
	}

	rotation[1] += rotationSpeed;
}


Fireball::Fireball(const glm::vec3& position, const glm::vec3& moveSpeed_, const glm::vec3& rotationSpeed_) :
	CollidableObject{position, glm::vec3(0.0), 1.0},
	moveSpeed(moveSpeed_),
	rotationSpeed(rotationSpeed_)
{}


void Fireball::update()
{
	position += moveSpeed;
	rotation += rotationSpeed;
}

const char Enemies::VERTEX_SHADER[]         = "EnemyVertexShader.vertexshader";
const char Enemies::FRAGMENT_SHADER[]       = "EnemyFragmentShader.fragmentshader";
const int Enemies::MIN_ENEMY_SPAWN_DISTANCE = 3;
const int Enemies::MAX_ENEMY_SPAWN_DISTANCE = 30;
const int Enemies::ENEMY_SPAWN_FREQUENCY    = 120;
const int Enemies::MAX_ENEMY_COUNT          = 30;


Enemies::Enemies()
{
	// Create and compile our GLSL program from the shaders
    programID = LoadShaders(VERTEX_SHADER, FRAGMENT_SHADER);

    // Get a handle for our "MVP" uniform
    matrixID = glGetUniformLocation(programID, "MVP");

    glGenBuffers(1, &vertexbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(enemyModel::g_vertex_buffer_data), enemyModel::g_vertex_buffer_data, GL_STATIC_DRAW);

    glGenBuffers(1, &colorbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(enemyModel::g_color_buffer_data), enemyModel::g_color_buffer_data, GL_STATIC_DRAW);
}


Enemies::~Enemies()
{
	glDeleteBuffers(1, &vertexbuffer);
	glDeleteBuffers(1, &colorbuffer);
	glDeleteProgram(programID);
}


void Enemies::render(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix)
{
	// Use our shader
    glUseProgram(programID);

    // 1rst attribute buffer : vertices
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

    // 2nd attribute buffer : colors
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

    for (auto enemy : enemies)
    {
    	//glm::mat4 modelMatrix = glm::mat4(1.0);
	    glm::mat4 modelMatrix(glm::translate(glm::mat4(1.0), enemy->position) * glm::toMat4(glm::quat(enemy->rotation)));
	    glm::mat4 MVP = projectionMatrix * viewMatrix * modelMatrix;

	    // Send our transformation to the currently bound shader, 
	    // in the "MVP" uniform
	    glUniformMatrix4fv(matrixID, 1, GL_FALSE, &MVP[0][0]);

	    glDrawArrays(GL_TRIANGLES, 0, 24*3);
    }

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
}


void Enemies::update(const int tick)
{
	for (auto enemy : enemies)
    {
    	enemy->update();
	}

	if (tick % ENEMY_SPAWN_FREQUENCY == 0 && enemies.size() < MAX_ENEMY_COUNT)
	{
		spawnEnemy();
	}
}


void Enemies::spawnEnemy()
{
	// Get random number in [MIN_ESD, MAX_ESD]
	float x = rand() % (MAX_ENEMY_SPAWN_DISTANCE - MIN_ENEMY_SPAWN_DISTANCE) + MIN_ENEMY_SPAWN_DISTANCE;
	// Set random sign
	x *= (rand() % 2) == 0 ? 1 : -1;

	float z = rand() % (MAX_ENEMY_SPAWN_DISTANCE - MIN_ENEMY_SPAWN_DISTANCE) + MIN_ENEMY_SPAWN_DISTANCE;
	z *= (rand() % 2) == 0 ? 1 : -1;

	enemies.insert(std::make_shared<Enemy>(glm::vec3(x, 0.0, z), glm::vec3(0.0)));
}


void Enemies::killEnemy(const std::shared_ptr<Enemy>& enemy)
{
	enemies.erase(enemy);
}


const std::set<std::shared_ptr<Enemy>>& Enemies::getSet() const
{
	return enemies;
}


const char Fireballs::FIREBALL_VERTEX_SHADER[]   = "FireballVertexShader.vertexshader";
const char Fireballs::FIREBALL_FRAGMENT_SHADER[] = "FireballFragmentShader.fragmentshader";
const char Fireballs::FIREBALL_TEXTURE[]         = "fireball.dds";
const char Fireballs::FIREBALL_OBJECT_MESH[]     = "fireball.obj";
const int Fireballs::MAX_FIREBALL_COUNT          = 20;
const int Fireballs::FIREBALL_SPAWN_FREQUENCY    = 20;
const int Fireballs::MAX_FIREBALL_DISTANCE       = 50;


Fireballs::Fireballs()
{
	// Create and compile our GLSL program from the shaders
	programID = LoadShaders(FIREBALL_VERTEX_SHADER, FIREBALL_FRAGMENT_SHADER);

	// Get a handle for our "MVP" uniform
	matrixID = glGetUniformLocation(programID, "MVP");

	// Load the texture
	texture = loadDDS(FIREBALL_TEXTURE);
	
	// Get a handle for our "textureSampler" uniform
	textureID  = glGetUniformLocation(programID, "textureSampler");

	// Read our .obj file
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec2> uvs;
	std::vector<glm::vec3> normals; // Won't be used at the moment.
	if (!loadOBJ(FIREBALL_OBJECT_MESH, vertices, uvs, normals))
	{
		printf("Impossible to load object\n");
		getchar();
		exit(1);
	}
	vertices_size = vertices.size();

	// Load it into a VBO
	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);

	glGenBuffers(1, &uvbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
	glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(glm::vec2), &uvs[0], GL_STATIC_DRAW);
}


Fireballs::~Fireballs()
{
	glDeleteBuffers(1, &vertexbuffer);
	glDeleteBuffers(1, &uvbuffer);
	glDeleteProgram(programID);
	glDeleteTextures(1, &texture);
}


void Fireballs::render(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix)
{
	// Use our shader
	glUseProgram(programID);

	// Bind our texture in Texture Unit 0
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	// Set our "myTextureSampler" sampler to use Texture Unit 0
	glUniform1i(textureID, 0);

	// 1rst attribute buffer : vertices
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	// 2nd attribute buffer : UVs
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

	for (auto fireball : fireballs)
    {
	    glm::mat4 modelMatrix(glm::translate(glm::mat4(1.0), fireball->position) * glm::toMat4(glm::quat(fireball->rotation)));
	    glm::mat4 MVP = projectionMatrix * viewMatrix * modelMatrix;

	    // Send our transformation to the currently bound shader, 
	    // in the "MVP" uniform
	    glUniformMatrix4fv(matrixID, 1, GL_FALSE, &MVP[0][0]);

	    glDrawArrays(GL_TRIANGLES, 0, vertices_size);
    }

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
}


void Fireballs::update(const int tick)
{
	std::vector<std::shared_ptr<Fireball>> toKill;

	for (auto fireball : fireballs)
    {
    	fireball->update();

    	if(glm::length(fireball->position) > MAX_FIREBALL_DISTANCE)
		{
			toKill.push_back(fireball);	
		}
	}

	for (auto fireball : toKill)
	{
		fireballs.erase(fireball);
	}
}


void Fireballs::spawnFireball(const glm::vec3& position, const glm::vec3& moveSpeed)
{
	glm::vec3 rotationSpeed((float) rand() / RAND_MAX + 1.0, (float) rand() / RAND_MAX + 1.0, (float) rand() / RAND_MAX + 1.0);
	fireballs.insert(std::make_shared<Fireball>(position, moveSpeed, rotationSpeed));
}


int Fireballs::checkCollisions(Enemies& enemies)
{
	int collisions = 0;

	std::vector<std::shared_ptr<Fireball>> toKill;

	for (auto fireball : fireballs)
    {
    	for (auto enemy : enemies.getSet())
    	{
    		if (fireball->isCollides(enemy.get()))
    		{
    			enemies.killEnemy(enemy);
    			toKill.push_back(fireball);
    			++collisions;
    			break;
    		}
    	}
	}

	for (auto fireball : toKill)
	{
		fireballs.erase(fireball);
	}

	return collisions;
}