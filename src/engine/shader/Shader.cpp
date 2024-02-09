#include "Shader.h"

#ifdef __EMSCRIPTEN__
#include <GLES3/gl3.h>
#else
#include <glad/glad.h>
#endif

#include <iostream>
#include <fstream>
#include <sstream>

#include <glm/ext.hpp>

Shader* Shader::shader_base = nullptr;
Shader* Shader::shader_material = nullptr;
Shader* Shader::shader_light = nullptr;
Shader* Shader::shader_simplemesh = nullptr;
Shader* Shader::shader_mesh = nullptr;
Shader* Shader::shader_background = nullptr;
Shader* Shader::shader_sphere_test = nullptr;


Shader::Shader(const char* vertexPath, const char* fragmentPath)
{
    std::string vertexCode;
    std::string fragmentCode;

    std::ifstream vShaderFile(vertexPath);
    std::ifstream fShaderFile(fragmentPath); 

    std::stringstream vShaderStream, fShaderStream;

    vShaderStream << vShaderFile.rdbuf();
    fShaderStream << fShaderFile.rdbuf();

    vShaderFile.close();
    fShaderFile.close();

    vertexCode = vShaderStream.str();
    fragmentCode = fShaderStream.str();

    const char* vertexCodeStr = vertexCode.c_str();
    const char* fragmentCodeStr = fragmentCode.c_str();

    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexCodeStr, NULL);
    glCompileShader(vertexShader);

    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED" << std::endl << infoLog << std::endl;
    }

    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentCodeStr, NULL);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED" << std::endl << infoLog << std::endl;
    }

    shaderID = glCreateProgram();
    glAttachShader(shaderID, vertexShader);
    glAttachShader(shaderID, fragmentShader);
    glLinkProgram(shaderID);

    glGetProgramiv(shaderID, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(shaderID, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED" << std::endl << infoLog << std::endl;
    }
    
    std::cout << "Shader created." << std::endl;
    // Needs to be updated.


    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

Shader::~Shader()
{
}

void Shader::Use()
{
    glUseProgram(shaderID);
}


void Shader::SetBool(const char* name, bool value) const
{
    glUniform1i(glGetUniformLocation(shaderID, name), (int)value);
}

void Shader::SetInt(const char* name, int value) const
{
    glUniform1i(glGetUniformLocation(shaderID, name), value);
}

void Shader::SetFloat(const char* name, float value) const
{
    glUniform1f(glGetUniformLocation(shaderID, name), value);
}

void Shader::SetVec2(const char* name, const glm::vec2& value) const
{
    glUniform2fv(glGetUniformLocation(shaderID, name), 1, glm::value_ptr(value));
}

void Shader::SetVec3(const char* name, const glm::vec3& value) const
{
    glUniform3fv(glGetUniformLocation(shaderID, name), 1, glm::value_ptr(value));
}

void Shader::SetVec4(const char* name, const glm::vec4& value) const
{
    glUniform4fv(glGetUniformLocation(shaderID, name), 1, glm::value_ptr(value));
}

void Shader::SetMat2(const char* name, const glm::mat2& value) const
{
    glUniformMatrix2fv(glGetUniformLocation(shaderID, name), 1, GL_FALSE, glm::value_ptr(value));
}

void Shader::SetMat3(const char* name, const glm::mat3& value) const
{
    glUniformMatrix3fv(glGetUniformLocation(shaderID, name), 1, GL_FALSE, glm::value_ptr(value));
}

void Shader::SetMat4(const char* name, const glm::mat4& value) const
{
    glUniformMatrix4fv(glGetUniformLocation(shaderID, name), 1, GL_FALSE, glm::value_ptr(value));
}


void Shader::InitShaders()
{
    shader_base = new Shader("shaders/base.vs", "shaders/base.fs");
    shader_material = new Shader("shaders/material.vs", "shaders/material.fs");
    shader_light = new Shader("shaders/light.vs", "shaders/light.fs");
    shader_simplemesh = new Shader("shaders/simplemesh.vs", "shaders/simplemesh.fs");
    shader_mesh = new Shader("shaders/mesh.vs", "shaders/mesh.fs");
    shader_background = new Shader("shaders/background.vs", "shaders/background.fs");
    shader_sphere_test = new Shader("shaders/spheretest.vs", "shaders/spheretest.fs");
}

Shader* Shader::GetShader(ShaderID shader)
{
    switch (shader)
    {
        case SHADER_BASE:
            return shader_base;
        case SHADER_MATERIAL:
            return shader_material;
        case SHADER_LIGHT:
            return shader_light;
        case SHADER_SIMPLEMESH:
            return shader_simplemesh;
        case SHADER_MESH:
            return shader_mesh;
        case SHADER_BACKGROUND:
            return shader_background;
        case SHADER_SPHERE_TEST:
            return shader_sphere_test;
        default:
            throw new std::runtime_error("Couldn't find shader.");
            return nullptr;
    }
}

void Shader::UpdateProjectionMatrix(const glm::mat4& projectionMatrix)
{
    if (shader_base != nullptr)
    {
        shader_base->Use();
        shader_base->SetMat4("projection", projectionMatrix);
    }
    if (shader_material != nullptr)
    {
        shader_material->Use();
        shader_material->SetMat4("projection", projectionMatrix);
    }
    if (shader_light != nullptr)
    {
        shader_light->Use();
        shader_light->SetMat4("projection", projectionMatrix);
    }
    if (shader_simplemesh != nullptr)
    {
        shader_simplemesh->Use();
        shader_simplemesh->SetMat4("projection", projectionMatrix);
    }
    if (shader_mesh != nullptr)
    {
        shader_mesh->Use();
        shader_mesh->SetMat4("projection", projectionMatrix);
    }
    
    if (shader_sphere_test != nullptr)
    {
        shader_sphere_test->Use();
        shader_sphere_test->SetMat4("projection", projectionMatrix);
    }
}

void Shader::UpdateViewMatrix(const glm::mat4& viewMatrix)
{
    if (shader_base != nullptr)
    {
        shader_base->Use();
        shader_base->SetMat4("view", viewMatrix);
    }
    
    if (shader_material != nullptr)
    {
        shader_material->Use();
        shader_material->SetMat4("view", viewMatrix);
    }
    
    if (shader_light != nullptr)
    {
        shader_light->Use();
        shader_light->SetMat4("view", viewMatrix);
    }
    
    if (shader_simplemesh != nullptr)
    {
        shader_simplemesh->Use();
        shader_simplemesh->SetMat4("view", viewMatrix);
    }
    
    if (shader_mesh != nullptr)
    {
        shader_mesh->Use();
        shader_mesh->SetMat4("view", viewMatrix);
    }
    
    if (shader_sphere_test != nullptr)
    {
        shader_sphere_test->Use();
        shader_sphere_test->SetMat4("view", viewMatrix);
    }
}