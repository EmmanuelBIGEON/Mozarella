#include "Model.h"

#include "ModelLoader.h"
#include "Shader.h"

Model::Model()
{
    _shader = Shader::GetShader(SHADER_MATERIAL);
}

Model::~Model() 
{
    for (auto mesh : _meshes) delete mesh;
}

void Model::SetShader(Shader* shader)
{
    _shader = shader;   
}

void Model::AddMesh(Mesh* mesh)
{
    _meshes.push_back(mesh);
}

void Model::Compute()
{
    _shader->Use(); // inutile mais on sait jamais.
    for(unsigned int i = 0; i < _meshes.size(); i++)
        _meshes[i]->Compute();
}

void Model::Render()
{
    _shader->Use();
    auto model = glm::mat4(1.0f);
    model = glm::rotate(model, glm::radians(90.0f), glm::vec3(-1.0f, 0.0f, 0.0f));
    _shader->SetMat4("model", model);

    for(unsigned int i = 0; i < _meshes.size(); i++)
        _meshes[i]->Render();
}
