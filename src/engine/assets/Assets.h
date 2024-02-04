#pragma once

#include <unordered_map>

#include "Ressources.h"

#include "Texture.h"

enum AssetType
{
    AssetType_None,
    AssetType_All,
    AssetType_Textures
};

class Assets 
{
    public: 
        static bool LoadAssets(AssetType type);
        static void Bind(assets::Texture textureName, unsigned int slot);

    protected: 
        static bool LoadTextures();

        static std::unordered_map<assets::Texture, Texture*> mapTextures;
};