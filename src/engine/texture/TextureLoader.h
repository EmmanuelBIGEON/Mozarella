#pragma once 

#include "Texture.h"

#include <string> 

class TextureLoader 
{
    public:
        TextureLoader();
        virtual ~TextureLoader();

        Texture* Load(const std::string& filePath);
        
        Texture* Load(const char *filePath);

        // Used for embedded textures.
        Texture* Load(const char *bufferedData, int datalen, bool ispng = false);
}; 