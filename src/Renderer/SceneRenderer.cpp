#include "SceneRenderer.h"

#include <glad/glad.h>
#include <iostream>
#include <Renderer/MeshRenderer.h>
#include <yaml-cpp/yaml.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <Core/Core.h>
#include <Tools/Vector.h>
#include <Core/Engine.h>

void SceneRenderer::setup(std::vector<MeshRenderer*>* meshRenderers)
{
    _meshRenderers = meshRenderers;
}

void SceneRenderer::Render()
{
    int amountMeshs = _meshRenderers->size();

    glm::mat4 projection = Engine::getActiveScenePtr()->GetCameraPtr()->GetProjection();
    glm::mat4 view = Engine::getActiveScenePtr()->GetCameraPtr()->GetView();

    for (int i = 0; i < amountMeshs; i++)
    {
        MeshRenderer& renderer = *_meshRenderers->at(i);
        renderer.shader->use();

        glm::mat4 model = renderer.transform->GetModel();

        renderer.shader->setMat4("projection", projection);
        renderer.shader->setMat4("view", view);
        renderer.shader->setMat4("model", model);
        renderer.Draw();
    }
}

void SceneRenderer::cleanUp()
{
    _meshRenderers->clear();
}