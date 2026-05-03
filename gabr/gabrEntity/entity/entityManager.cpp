#include "entityManager.h"

namespace Gabr
{
	Entity* EntityHandle::Get() const
	{
		if (!manager) return nullptr;

		return manager->Get(*this);
	}
}