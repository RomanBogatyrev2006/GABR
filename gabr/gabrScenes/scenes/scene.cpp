#include "scene.h"

namespace Gabr
{
	Scene::Scene(EntityManager* manager):mEntityManager(manager) {}
	
	Scene::~Scene() { DestroyAllEntities(); }
	
	// Add entity to scene
	void Scene::AddEntity(EntityHandle handle)
	{
		if (mEntityManager && mEntityManager->IsAlive(handle))
		{
			mEntities.push_back(handle);
		}
	}
	
	// Remove entity from scene
	void Scene::RemoveEntity(EntityHandle handle)
	{
		mEntities.erase(std::remove_if(mEntities.begin(), mEntities.end(),
			[&](const EntityHandle& h)
			{
				return h.id == handle.id && h.generation == handle.generation;
			}),
		mEntities.end());
	}
	
	// Create sub scene
	Scene* Scene::CreateSubScene()
	{
		mSubScenes.push_back(std::make_unique<Scene>(mEntityManager));
		return mSubScenes.back().get();
	}
	
	// Destroy sub scene
	void Scene::DestroySubScene(Scene* scene)
	{
		mSubScenes.erase(std::remove_if(mSubScenes.begin(), mSubScenes.end(),
			[&](const std::unique_ptr<Scene>& ptr)
			{
				return ptr.get() == scene;
			}),
			mSubScenes.end());
	}
	
	// Update entities and sub scenes in scene
	void Scene::Update(float deltaTime)
	{
		for (auto& handle : mEntities)
		{
			if (mEntityManager->IsAlive(handle)) { handle->Update(deltaTime); }
		}
		
		for (auto& sub : mSubScenes)
		{
			sub->Update(deltaTime);
		}
	}
	
	// Render entities and sub scenes in scene
	void Scene::Render(Renderer* renderer)
	{
		for (auto& handle : mEntities)
		{
			if (mEntityManager->IsAlive(handle)) { handle->Render(renderer); }
		}
		
		for (auto& sub : mSubScenes)
		{
			sub->Render(renderer);
		}
	}
	
	// Destroy all entities in scene
	void Scene::DestroyAllEntities()
	{
		if (!mEntityManager) return;
		
		for (auto& handle : mEntities)
		{
			if (mEntityManager->IsAlive(handle))
			{
				mEntityManager->Destroy(handle);
			}
		}
		
		mEntities.clear();
	}
}