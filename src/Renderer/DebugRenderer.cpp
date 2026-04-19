#include "DebugRenderer.h"

#include <glad/glad.h>

#include <Game/ResourceManager.h>
#include <Core/Engine.h>

void DebugRenderer::setup()
{
	glGenVertexArrays(1, &_vao);
	glGenBuffers(1, &_vbo);

	glBindVertexArray(_vao);
	glBindBuffer(GL_ARRAY_BUFFER, _vbo);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	_shader = ResourceManager::GetInstance().GetShader("ColliderShader", "res/DebugRes/Shaders/ColliderVertex.glsl", "res/DebugRes/Shaders/ColliderFragment.glsl").get();
}

void DebugRenderer::setPhysicsWorld(rp3d::PhysicsWorld* physicsWorld)
{
	_physicsWorld = physicsWorld;
	
	if (_physicsWorld)
	{
		_rp3dDebugRenderer = new reactphysics3d::DebugRenderer(_physicsWorld->getMemoryManager().getHeapAllocator());

		_rp3dDebugRenderer->setIsDebugItemDisplayed(reactphysics3d::DebugRenderer::DebugItem::COLLISION_SHAPE, true);
	}
}

void DebugRenderer::render()
{
	_rp3dDebugRenderer->reset();
	_rp3dDebugRenderer->computeDebugRenderingPrimitives(*_physicsWorld);
	convertToVertices();
	if (_vertices.empty())
	{
		return;
	}

	updateVbo();

	_shader->use();

	glLineWidth(2.0f);

	glm::mat4 projection = Engine::getActiveScenePtr()->GetCameraPtr()->GetProjection();
	glm::mat4 view = Engine::getActiveScenePtr()->GetCameraPtr()->GetView();
	glm::mat4 model = glm::mat4(1.0f);

	_shader->setMat4("projection", projection);
	_shader->setMat4("view", view);
	_shader->setMat4("model", model);

	glDisable(GL_DEPTH_TEST);
	glDepthMask(GL_FALSE);

	glDrawArrays(GL_LINES, 0, _vertices.size() / 3);

	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_TRUE);
}

void DebugRenderer::updateVbo()
{
	glBindVertexArray(_vao);
	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	glBufferData(GL_ARRAY_BUFFER, _vertices.size() * sizeof(float), _vertices.data(), GL_DYNAMIC_DRAW);

	glBufferData(GL_ARRAY_BUFFER, _vertices.size() * sizeof(float), _vertices.data(), GL_DYNAMIC_DRAW);
}

void DebugRenderer::convertToVertices()
{
    _vertices.clear();

	if (!_rp3dDebugRenderer)
	{
		return;
	}

    const auto& triangles = _rp3dDebugRenderer->getTriangles();
    for (int i = 0; i < _rp3dDebugRenderer->getNbTriangles(); i++)
    {
        const auto& tri = triangles[i];

        addVertex(glm::vec3(tri.point1.x, tri.point1.y, tri.point1.z));
        addVertex(glm::vec3(tri.point2.x, tri.point2.y, tri.point2.z));
        addVertex(glm::vec3(tri.point3.x, tri.point3.y, tri.point3.z));
    }

    const auto& lines = _rp3dDebugRenderer->getLines();

    for (int i = 0; i < _rp3dDebugRenderer->getNbLines(); i++)
    {
        const auto& line = lines[i];

        glm::vec3 p1(line.point1.x, line.point1.y, line.point1.z);
        glm::vec3 p2(line.point2.x, line.point2.y, line.point2.z);

        addVertex(p1);
        addVertex(p2);
    }
}

void DebugRenderer::addVertex(const glm::vec3& pos)
{
    _vertices.push_back(pos.x);
    _vertices.push_back(pos.y);
    _vertices.push_back(pos.z);
}


void DebugRenderer::cleanUp()
{
	if (_rp3dDebugRenderer)
	{
		delete _rp3dDebugRenderer;
		_rp3dDebugRenderer = nullptr;
	}

	if (_vbo)
	{
		glDeleteBuffers(1, &_vbo);
	}

	if (_vao)
	{
		glDeleteVertexArrays(1, &_vao);
	}
}