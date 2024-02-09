#include "ModelLoader.h"

#include <iostream>
#include <fstream>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <glad/glad.h>
#include <stb_image.h>

#include "Shader.h"
#include "Texture.h"

ModelLoader::ModelLoader()
{
}

ModelLoader::~ModelLoader()
{
}

Model* ModelLoader::Load(const std::string& filepath)
{
    Model* model = new Model();
    _meshes.clear();
    _fileExtension = filepath.substr(filepath.find_last_of(".") + 1);

    stbi_set_flip_vertically_on_load(false); 
    
    Assimp::Importer import;
    const aiScene *scene = import.ReadFile(filepath, aiProcess_Triangulate | aiProcess_FlipUVs);	
	
    if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) 
    {
        std::cout << "Error on Assimp load : " << filepath.c_str() << std::endl;
        return model;
    }
    
    // On charge le model.
    LoadNode(scene->mRootNode, scene);
    
    for(auto mesh : _meshes) model->AddMesh(mesh);

    return model;
}

void ModelLoader::LoadNode(aiNode *node, const aiScene *scene)
{
    // process all the node's meshes (if any)
    for(unsigned int i = 0; i < node->mNumMeshes; i++)
    {
        aiMesh *aimesh = scene->mMeshes[node->mMeshes[i]]; 
        _meshes.push_back(LoadMesh(aimesh, scene));			
    }
    // then do the same for each of its children
    for(unsigned int i = 0; i < node->mNumChildren; i++)
    {
        LoadNode(node->mChildren[i], scene);
    }
}  

Mesh* ModelLoader::LoadMesh(aiMesh *aimesh, const aiScene *scene)
{
    auto mesh = new Mesh();
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture*> textures;

    for(unsigned int i = 0; i < aimesh->mNumVertices; i++)
    {
        Vertex vertex;
        
        vertex.Position.x = aimesh->mVertices[i].x;
        vertex.Position.y = aimesh->mVertices[i].y;
        vertex.Position.z = aimesh->mVertices[i].z;

        if (aimesh->HasNormals())
        {
            vertex.Normal.x = aimesh->mNormals[i].x;
            vertex.Normal.y = aimesh->mNormals[i].y;
            vertex.Normal.z = aimesh->mNormals[i].z;
        }
        
        if(aimesh->mTextureCoords[0])
        {
            vertex.TexCoords.x = aimesh->mTextureCoords[0][i].x; 
            vertex.TexCoords.y = aimesh->mTextureCoords[0][i].y;
        }
        else
            vertex.TexCoords = glm::vec2(0.0f, 0.0f);

        vertices.push_back(vertex);
    }
    
    for(unsigned int i = 0; i < aimesh->mNumFaces; i++)
    {
        aiFace face = aimesh->mFaces[i];

        for(unsigned int j = 0; j < face.mNumIndices; j++)
            indices.push_back(face.mIndices[j]);        
    }

    aiMaterial* material = scene->mMaterials[aimesh->mMaterialIndex];  

    if (_fileExtension == "glb") 
    {
        aiString str;
        material->GetTexture(aiTextureType_DIFFUSE, 0, &str);
        const aiTexture* aitexture = scene->GetEmbeddedTexture(str.C_Str());

        auto texture = _textureLoader.Load((const char*)aitexture->pcData, aitexture->mWidth, !strcmp(aitexture->achFormatHint, "png"));
        texture->type = aiTextureType_DIFFUSE;
        texture->path = aitexture->mFilename.C_Str();
        textures.push_back(texture);

    }
    else 
    {
        aiString str;
        material->GetTexture(aiTextureType_DIFFUSE, 0, &str);
        auto texture = _textureLoader.Load(str.C_Str());
        texture->type = aiTextureType_DIFFUSE;
        texture->path = str.C_Str();
        textures.push_back(texture);

    }

    return new Mesh(vertices, indices, textures);
}