#pragma once 

#include "Mesh.h"

#include <string> 
#include <vector>

#include "Shader.h"

#include <assimp/scene.h>

class Model : public GraphicObject
{
    public:
        Model();
        virtual ~Model();
    
        void SetShader(Shader* shader);

        void AddMesh(Mesh* mesh);

        virtual void Compute() override;
        virtual void Render() override;
        
    private:
        std::vector<Mesh*> _meshes;
        
        Shader* _shader;
};
