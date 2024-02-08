#pragma once 

#include "Mesh.h"

#include <string> 
#include <vector>

#include <assimp/scene.h>

class Model : public GraphicObject
{
    public:
        Model(const char *path);
        virtual ~Model();

        virtual void Compute() override;
        virtual void Render() override;
        
    private:

        std::vector<Texture*> textures_loaded;
        std::vector<Mesh> _meshes;
        std::string _directory;
        std::string _path;
        const aiScene* _scene;

        void loadModel(std::string path);
        void processNode(aiNode *node, const aiScene *scene);
        Mesh processMesh(aiMesh *mesh, const aiScene *scene);

        std::vector<Texture*> loadMaterialTextures(aiMaterial *mat, aiTextureType type, 
                                             std::string typeName);

        std::vector<Texture*> loadEmbeddedMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName);
};
