#pragma once

#include <entity/entityManager.h>

namespace Gabr
{
	class GABR_API Scene
	{
	public:
		Scene(EntityManager* manager);
		~Scene();
		
		Scene(const Scene&) = delete;
		Scene& operator=(const Scene&) = delete;
		
		
		// --Entity--
		
		// Add entity to scene
		void AddEntity(EntityHandle handle);
		
		// Remove entity from scene
		void RemoveEntity(EntityHandle handle);
		
		
		// --Sub scenes--
		
		// Create sub scene
		Scene* CreateSubScene();
		
		// Destroy sub scene
		void DestroySubScene(Scene* scene);
		
		
		// --Update / Render--
		
		// Update entities and sub scenes in scene
		void Update(float deltaTime);
		
		// Render entities and sub scenes in scene
		void Render(Renderer* renderer);
		
	private:
		// Destroy all entities in scene
		void DestroyAllEntities();
	
		EntityManager* mEntityManager = nullptr;
		
		std::vector<EntityHandle> mEntities;
		std::vector<std::unique_ptr<Scene>> mSubScenes;
	};
}