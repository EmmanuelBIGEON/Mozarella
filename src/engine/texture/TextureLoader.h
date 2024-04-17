#pragma once 

#include "Texture.h"

#include <string> 
#include <vector> 

class TextureLoader 
{
    public:
        TextureLoader();
        virtual ~TextureLoader();

        Texture* Load(const std::string& filePath);
        
        Texture* Load(const char *filePath);

        // Used for embedded textures.
        Texture* Load(const char *bufferedData, int datalen, bool ispng = false);

        Texture* LoadCubemap(const std::vector<std::string>& filepaths, const std::string& name = "cubemap");
}; 