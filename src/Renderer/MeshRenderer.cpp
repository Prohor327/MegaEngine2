#include "MeshRenderer.h"

MeshRenderer::MeshRenderer(GameObject* gameObject, int baseIndex, int amountIndices, std::string shaderName)
	: MeshRenderer(gameObject)
{
	this->baseIndex = baseIndex;
	this->amountIndices = amountIndices;
	this->shaderName = shaderName;
}

MeshRenderer::MeshRenderer(GameObject* gameObject) : Component(gameObject)
{
	shaderName = "asda";
}