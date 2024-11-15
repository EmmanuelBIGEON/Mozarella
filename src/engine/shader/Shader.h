#pragma once

#include <glm/ext.hpp>

enum ShaderID
{
    SHADER_BASE,
    SHADER_MATERIAL,
    SHADER_LIGHT,
    SHADER_SIMPLEMESH,
    SHADER_MESH,
    SHADER_DEPTH,
    SHADER_BACKGROUND,
    SHADER_SPHERE_TEST,
    SHADER_SCREEN,
    SHADER_SKYBOX
};

class Shader
{
    public:
        Shader(const char* vertexPath, const char* fragmentPath);
        virtual ~Shader();

        void Use();

        void SetBool(const char* name, bool value) const;
        void SetInt(const char* name, int value) const;
        void SetFloat(const char* name, float value) const;
        void SetVec2(const char* name, const glm::vec2& value) const;
        void SetVec3(const char* name, const glm::vec3& value) const;
        void SetVec4(const char* name, const glm::vec4& value) const;
        void SetMat2(const char* name, const glm::mat2& value) const;
        void SetMat3(const char* name, const glm::mat3& value) const;
        void SetMat4(const char* name, const glm::mat4& value) const;

        unsigned int shaderID;

        static void InitShaders();
        static Shader* GetShader(ShaderID shader);

        static void UpdateProjectionMatrix(const glm::mat4& projectionMatrix);
        static void UpdateViewMatrix(const glm::mat4& viewMatrix);

    protected:

        static Shader* shader_base;
        static Shader* shader_material;
        static Shader* shader_light;
        static Shader* shader_simplemesh;
        static Shader* shader_mesh;
        static Shader* shader_depth;
        static Shader* shader_background;
        static Shader* shader_sphere_test;
        static Shader* shader_screen;
        static Shader* shader_skybox;

};