#include "SceneFactory.h"
#include "ViewFactory.h"

#include "SceneColor.h"
#include "SceneCube.h"
#include "SceneCamera.h"
#include "SceneMesh.h"
#include "SceneLight.h"
#include "SceneSphere.h"

Scene* SceneFactory::CreateDefaultScene()
{
    return new Scene();
}

Scene* SceneFactory::CreateColorScene(const glm::vec3& pColor)
{
    auto scene = new SceneColor(pColor);
    return scene;
}

Scene* SceneFactory::CreateCubeScene()
{
    auto scene = new SceneCube();
    return scene;
}

Scene* SceneFactory::CreateMeshScene()
{
    auto scene = new SceneMesh();
    return scene;
}

Scene* SceneFactory::CreateLightScene()
{
    auto scene = new SceneLight();
    return scene;
}

Scene* SceneFactory::CreateSphereScene()
{
    auto scene = new SceneSphere();
    return scene;
}