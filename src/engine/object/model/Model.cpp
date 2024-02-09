#include "Model.h"

#include "ModelLoader.h"
#include "Shader.h"

Model::Model()
{
}

Model::~Model() 
{
    for (auto mesh : _meshes) delete mesh;
}

void Model::AddMesh(Mesh* mesh)
{
    _meshes.push_back(mesh);
}

void Model::Compute()
{
    for(unsigned int i = 0; i < _meshes.size(); i++)
        _meshes[i]->Compute();
}

void Model::Render()
{
    auto shader = Shader::GetShader(SHADER_MATERIAL);
    shader->Use();
    auto model = glm::mat4(1.0f);
    model = glm::rotate(model, glm::radians(90.0f), glm::vec3(-1.0f, 0.0f, 0.0f));
    shader->SetMat4("model", model);

    for(unsigned int i = 0; i < _meshes.size(); i++)
        _meshes[i]->Render();
}
