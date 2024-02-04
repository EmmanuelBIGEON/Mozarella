#include "Assets.h"

#include <iostream>

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

    mapTextures[assets::Texture::Texture_None] = nullptr;
    mapTextures[assets::Texture::Texture_Cube] = Texture::Load(BuildTexturePath("awesomeface.png"));
    mapTextures[assets::Texture::Texture_Cube2] = Texture::Load(BuildTexturePath("abstract-ink-alcohol.jpg"));
    mapTextures[assets::Texture::Texture_Cube3] = Texture::Load(BuildTexturePath("oldwood.jpg"));
    mapTextures[assets::Texture::Texture_Plane] = Texture::Load(BuildTexturePath("awesomeface.png"));
}
