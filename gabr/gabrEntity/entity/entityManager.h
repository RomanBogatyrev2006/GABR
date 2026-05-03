#pragma once

#include "entity.h"

namespace Gabr
{
	struct EntityHandle
	{
		uint32_t id = 0;
		uint32_t generation = 0;

		bool IsValid() const { return manager != nullptr; }

		Entity* Get() const;

		Entity* operator->() const { return Get(); }
	
	private:
		class EntityManager* manager = nullptr;

		friend class EntityManager;
	};

	class GABR_API EntityManager
	{
	public:
		EntityManager() = default;

		EntityManager(const EntityManager&) = delete;
		EntityManager& operator=(const EntityManager&) = delete;

		template<typename T, typename... Args>
		EntityHandle Create(Args&&... args)
		{
			static_assert(std::is_base_of<Entity, T>::value, "T must derive from Entity");

			uint32_t id;

			if (!freeIds.empty())
			{
				id = freeIds.back();
				freeIds.pop_back();
			}
			else
			{
				id = static_cast<uint32_t>(entities.size());
				entities.emplace_back(nullptr);
				generations.push_back(0);
			}

			entities[id] = std::make_unique<T>(std::forward<Args>(args)...);

			EntityHandle handle;
			handle.id = id;
			handle.generation = generations[id];
			handle.manager = this;

			return handle;
		}

		void Destroy(EntityHandle handle)
		{
			if (!IsAlive(handle)) return;
			
			entities[handle.id].reset();
			generations[handle.id]++;
			freeIds.push_back(handle.id);
		}

		Entity* Get(EntityHandle handle)
		{
			if (!IsAlive(handle)) return nullptr;

			return entities[handle.id].get();
		}

		bool IsAlive(EntityHandle handle) const
		{
			return	handle.manager == this &&
					handle.id < entities.size() &&
					generations[handle.id] == handle.generation &&
					entities[handle.id] != nullptr;
		}

	private:
		std::vector<std::unique_ptr<Entity>> entities;
		std::vector<uint32_t> generations;
		std::vector<uint32_t> freeIds;
	};
}