#include "Assets.h"

#include <iostream>
#include <vector>
#include <string> 

#include <glad/glad.h>

#include "TextureLoader.h"

std::unordered_map<assets::Texture, Texture*> Assets::mapTextures = {};

bool Assets::LoadAssets(AssetType type)
{
    switch(type)
    {
        case AssetType_All:
        {
            if(!LoadTextures())
            {
                std::cout << "Failed to LoadTextures()" << std::endl;
            }
            break;
        }
        case AssetType_Textures:
        {
            if(!LoadTextures())
            {
                std::cout << "Failed to LoadTextures()" << std::endl;
            }
            break;
        }
        default: 
        {
            break;
        }
    }
    return true;
}
void Assets::Bind(assets::Texture textureName, unsigned int slot)
{
    glActiveTexture(GL_TEXTURE0 + slot);
    mapTextures[textureName]->Bind(slot);
}

std::string BuildTexturePath(const std::string& file)
{
    return "textures/" + file;
}

bool Assets::LoadTextures()
{
    if(!mapTextures.empty())
    {
        std::cout << "Warning : Textures already loaded" << std::endl;
        return false;
    }
    TextureLoader loader;

    mapTextures[assets::Texture::Texture_None] = nullptr;
    mapTextures[assets::Texture::Texture_Cube] = Texture::Load(BuildTexturePath("awesomeface.png"));
    mapTextures[assets::Texture::Texture_Cube2] = Texture::Load(BuildTexturePath("abstract-ink-alcohol-min.jpg"));
    mapTextures[assets::Texture::Texture_Cube3] = Texture::Load(BuildTexturePath("oldwood-min.jpg"));
    mapTextures[assets::Texture::Texture_Plane] = Texture::Load(BuildTexturePath("oldwood-min.jpg"));
    mapTextures[assets::Texture::Texture_Background] = Texture::Load(BuildTexturePath("background-min.png"));
    mapTextures[assets::Texture::Texture_Woodfloor] = Texture::Load(BuildTexturePath("wood.png"));

    // load skybox.
    {    
        std::vector<std::string> filepaths
        {
            BuildTexturePath("skybox/right.jpg"),
            BuildTexturePath("skybox/left.jpg"),
            BuildTexturePath("skybox/top.jpg"),
            BuildTexturePath("skybox/bottom.jpg"),
            BuildTexturePath("skybox/front.jpg"),
            BuildTexturePath("skybox/back.jpg")
        };
        mapTextures[assets::Texture::Texture_Skybox] = loader.LoadCubemap(filepaths, "Skybox");
    }
}
