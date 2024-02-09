#pragma once 

#include <vector> 
#include <string> 

#include "Model.h"
#include "Mesh.h"
#include "TextureLoader.h"

#include <assimp/scene.h>

class ModelLoader 
{
    public: 
        ModelLoader();
        virtual ~ModelLoader();

        Model* Load(const std::string& filepath);
    protected:
        void LoadNode(aiNode *node, const aiScene *scene);
        Mesh* LoadMesh(aiMesh *aimesh, const aiScene *scene);

        std::vector<Mesh*> _meshes;
        std::string _fileExtension;
        TextureLoader _textureLoader;
};