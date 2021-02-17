#include "ECS.h"

ECS::ECS():
	hasStarted(false),componentsManager(), registry(componentsManager)
{

}

void ECS::AddEntityToSystem_I(std::vector<TypelessComponentPointer>& pointers, std::vector<std::size_t>& hashes)
{
	for (int i = 0; i < systems.size(); i++)
	{
		std::vector<int> marchingIndices = systems[i].GetMatchingTypeIndices(hashes);
		if (marchingIndices.size()>0)
		{
			for (auto componentIndex : marchingIndices)
			{
				if (componentIndex < pointers.size())
				{
					if (!hasStarted || !systems[i].HasComponentID(pointers[componentIndex].ID()))
					{
						systems[i].AddComponent(hashes[componentIndex], pointers[componentIndex]);
					}
				}
			}
		}
	}
}

void ECS::OnStart_I()
{
	for (int i = 0; i < registry.entities.size(); i++)
	{
		AddEntityToSystem_I(registry.entities[i].pointers, registry.entities[i].componentHashes);
	}
	hasStarted = true;
}

void ECS::OnUpdate_I()
{
	for (int i = 0; i < systems.size(); i++)
	{
		systems[i].OnUpdate();
	}
}

void ECS::DeleteSystems_I()
{
	systems.clear();
}

