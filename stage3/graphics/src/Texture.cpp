#include "../include/Texture.h"
#include "../stbi/stb_image.h"

#include <iostream>
#include <GL/glew.h>

Texture::Texture(std::string fileName)
{
	/*
	Here lies the death of a ridiculous bug
	 here it is
	GLuint textureID;
	this created a new local variable called textureID and it was the one that 
	was passed to the glGenTextures function, rather than the data member of 
	the class instance. This meant that when I bound the texture it 
	was binding the automatic value of textureID, usually garbage, and being
	rejected... Rest in peace bug, many hours were wasted on your existence
	*/

	glGenTextures(1, &(this->textureID));
	glActiveTexture(textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	this->data = stbi_load(fileName.c_str(), &width, &height, &numChannels, 0);

	if (data == nullptr)
	{
		std::cerr << "ERROR: CANNOT LOAD IMAGE FILE: " << fileName << "!!!" << std::endl;
	}
	else
	{
		//this loads the image data into the currently bound texture object
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	}
}

Texture::~Texture()
{
	//gotta free that data B)
	stbi_image_free(data);
}

void Texture::bind()
{
	glActiveTexture(textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);
}