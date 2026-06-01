#pragma once

#include "scene.h"

namespace Gabr
{
	class GABR_API SceneManager
	{
	public:
		SceneManager(EntityManager* manager);
		
		
		// Get root scene
		Scene* GetRootScene();
		
		// Update
		void Update(float deltaTime);
		
		// Render
		void Render(Renderer* renderer);
		
	private:
		EntityManager* mEntityManager = nullptr;
		std::unique_ptr<Scene> mRootScene;
	};
}