#include "TextureLoader.h"

#include <glad/glad.h>
#include <stb_image.h>

#include <iostream>

TextureLoader::TextureLoader()
{
}

TextureLoader::~TextureLoader()
{
}

Texture* TextureLoader::Load(const std::string& filePath)
{
    return Load(filePath.c_str());
}

Texture* TextureLoader::Load(const char *filePath)
{
    Texture* texture = new Texture();
    texture->path = filePath;

    glGenTextures(1, &texture->ID);

    int width, height, nbChannels;
    unsigned char *data = stbi_load(filePath, &width, &height, &nbChannels, 0);
    if (data)
    {
        GLenum format = GL_RGB;
        if      (nbChannels == 3) format = GL_RGB;
        else if (nbChannels == 4) format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, texture->ID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);
    }
    else
    {
        std::cout << "Texture failed to load at path: " << filePath << std::endl;
        stbi_image_free(data);
    }
    return texture;
}


Texture* TextureLoader::Load(const char *bufferedData, int datalen, bool ispng)
{
    Texture* texture = new Texture();

    glGenTextures(1, &texture->ID);
    
    int width, height;
    int nbChannels = 3;
    if(ispng) 
        nbChannels = 4;

	unsigned char *data = stbi_load_from_memory((unsigned char*)bufferedData, datalen, &width, &height, &nbChannels, nbChannels);

    if (data)
    {
        glBindTexture(GL_TEXTURE_2D, texture->ID);
        if(ispng)
        {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        }else 
        {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        }

        glGenerateMipmap(GL_TEXTURE_2D);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);
    }
    else
    {
        std::cout << "Failed to load texture." << std::endl;
        stbi_image_free(data);
    }

    return texture;
}