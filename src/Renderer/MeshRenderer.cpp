#include "MeshRenderer.h"

void MeshRenderer::Draw()
{
	if (texture != nullptr)
	{
		glActiveTexture(GL_TEXTURE0);
		shader->setInt("texture1", 0);
		glBindTexture(GL_TEXTURE_2D, texture->GetId());
	}
	glBindVertexArray(model->meshes[0]->Vao);
	glDrawElements(GL_TRIANGLES, model->meshes[0]->indexCount, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}