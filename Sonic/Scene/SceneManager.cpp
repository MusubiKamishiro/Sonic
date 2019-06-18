#include "SceneManager.h"
#include "Scene.h"
#include "TitleScene.h"



SceneManager::SceneManager()
{
	scene = std::make_unique<TitleScene>();
}


SceneManager::~SceneManager()
{
}

void SceneManager::ChangeScene(std::unique_ptr<Scene> newScene)
{
	scene = std::move(newScene);
}

void SceneManager::Update(Peripheral & p)
{
	scene->Update(p);
}

