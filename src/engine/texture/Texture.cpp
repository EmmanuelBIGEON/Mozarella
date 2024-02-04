#include "Texture.h"

#include <glad/glad.h>
#include <stb_image.h>
#include <iostream>
#include <filesystem>

Texture::Texture() : _ID(0), _data(nullptr)
{
}

Texture::~Texture()
{
}

Texture* Texture::Load(const std::string& filePath)
{
    // load and create a texture 
    Texture* texture = new Texture;

    if(!std::filesystem::exists(filePath))
    {
        std::cout << "Texture Filepath : " << filePath << " doesn't exist." << std::endl;
        return texture;
    }


    glGenTextures(1, &texture->_ID);
    glBindTexture(GL_TEXTURE_2D, texture->_ID);
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load image, create texture and generate mipmaps
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
    unsigned char *data = stbi_load(filePath.c_str(), &width, &height, &nrChannels, 0);
    if (data)
    {
        if(filePath.substr(filePath.find_last_of(".") + 1) == "png") {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
        }else
        {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
        }
    }
    else
    {
        std::cout << "Failed to load texture : " << filePath << std::endl;
    }

    return texture;
}

void Texture::Bind(unsigned int slot)
{
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_2D, _ID);
}

unsigned int Texture::GetID()
{
    return _ID;
}
