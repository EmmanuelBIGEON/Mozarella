#include "ObjectFactory.h"

#include "ModelLoader.h"

Cube* ObjectFactory::CreateCube(const glm::vec3& position)
{
    return new Cube(position, {0.0f, 0.0f, 1.0f});
}

Cube* ObjectFactory::CreateCube(const glm::vec3& position, const glm::vec3& color)
{
    return new Cube(position, color);
}

Cube* ObjectFactory::CreateCube(const glm::vec3& position, ColourGroup* colorGroup)
{
    auto cube = new Cube(position, {1.0f, 0.0f, 0.0f});
    cube->Assign(colorGroup);
    return cube;
}

LightSource* ObjectFactory::CreateLightSource(const glm::vec3& position)
{
    return new LightSource(position, {0.0f, 0.0f, 1.0f});
}

LightSource* ObjectFactory::CreateLightSource(const glm::vec3& position, const glm::vec3& lightColor)
{
    return new LightSource(position, lightColor);
}

TexturedCube* ObjectFactory::CreateTexturedCube(const glm::vec3& position)
{
    return new TexturedCube(position);
}

ColoredCube* ObjectFactory::CreateColoredCube(const glm::vec3& position, ColourGroup* colourgroup)
{
    auto cube = new ColoredCube(position, {0.0f, 0.0f , 1.0f});
    cube->Assign(colourgroup);
    return cube;
}

ColoredCube* ObjectFactory::CreateColoredCube(const glm::vec3& position, float width, ColourGroup* colourgroup)
{
    auto cube = new ColoredCube(position, width, {0.0f, 0.0f , 1.0f});
    cube->Assign(colourgroup);
    return cube;
}

Rectangle* ObjectFactory::CreateRectangle()
{
    return new Rectangle();
}

Rectangle* ObjectFactory::CreateRectangle(const glm::vec3& p1, const glm::vec3& p2, const glm::vec3& p3, const glm::vec3& p4)
{
    return new Rectangle(p1, p2, p3, p4);
}

Sphere* ObjectFactory::CreateSphere(const glm::vec3& position)
{
    return new Sphere(position);
}

Sphere* ObjectFactory::CreateSphere(const glm::vec3& position, unsigned int subdivisionCount)
{
    return new Sphere(position, subdivisionCount);
}

Model* ObjectFactory::LoadModel(const std::string& filePath)
{
    ModelLoader loader;
    return loader.Load(filePath);
}