#include "Texture.h"

#define STB_IMAGE_IMPLEMENTATION

#include <iostream>
#include <stb/stb_image.h>
#include <glad/glad.h>

Texture::Texture(int width, int height, std::string type, std::string path)
{
	_width = width;
	_height = height;
	_type = type;
	_path = path;
	_nrChannels = 3;

	glGenTextures(1, &_id);
	glBindTexture(GL_TEXTURE_2D, _id);
	std::cout << glGetError() << std::endl;

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	std::cout << glGetError() << std::endl;

	
	unsigned char* data = stbi_load(path.c_str(), &_width, &_height, &_nrChannels, 3);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, _width, _height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
		std::cout << glGetError() << std::endl;
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);
}

void Texture::ActiveTexture()
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, _id);
}

unsigned int Texture::GetId()
{
	return _id;
}