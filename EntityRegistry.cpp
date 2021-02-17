#include "EntityRegistry.h"
#include "algorithm"

unsigned int EntityRegistry::RegisterEntity()
{
	entities.emplace_back();
	return entities.size() - 1;
}

TypelessComponentPointer EntityRegistry::GetComponent(const unsigned int& index, const std::size_t& componentType)
{
	auto& entityComponentHash = entities[index].componentHashes;
	auto componentLocation = std::find(entityComponentHash.begin(), entityComponentHash.end(), componentType);
	if (componentLocation != entityComponentHash.end())
	{
		auto componentPointer = entities[index].pointers[componentLocation - entityComponentHash.begin()];
		return TypelessComponentPointer(componentPointer.ID(), componentPointer.Index(), componentPointer.VoidVector());
	}
	return TypelessComponentPointer();
}

