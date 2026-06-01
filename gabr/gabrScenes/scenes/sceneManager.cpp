#include "sceneManager.h"

namespace Gabr
{
	SceneManager::SceneManager(EntityManager* manager):mEntityManager(manager)
	{
		mRootScene = std::make_unique<Scene>(mEntityManager);
	}
	
	Scene* SceneManager::GetRootScene() { return mRootScene.get(); }
	
	void SceneManager::Update(float deltaTime) { mRootScene->Update(deltaTime); }
	
	void SceneManager::Render(Renderer* renderer) { mRootScene->Render(renderer); }
}