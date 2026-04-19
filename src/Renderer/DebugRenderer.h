#pragma once

#include <glm/glm.hpp>
#include <reactphysics3d/reactphysics3d.h>

#include <Game/Transform.h>
#include <Renderer/Shader.h>

#include <vector>

class DebugRenderer
{
public:
	void setPhysicsWorld(rp3d::PhysicsWorld* physicsWorld);

	void setup();
	void render();
	void cleanUp();

private:
	unsigned int _vbo = 0, _vao = 0;
	std::vector<float> _vertices;
	Shader* _shader = nullptr;

	reactphysics3d::PhysicsWorld* _physicsWorld;
	reactphysics3d::DebugRenderer* _rp3dDebugRenderer;

	void updateVbo();
	void convertToVertices();
	void addVertex(const glm::vec3& pos);
};