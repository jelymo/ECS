#pragma once
#include<list>
#include<optional>
#include<algorithm>
#include "ComponentsManager.h"

struct EntityData
{
	std::vector<TypelessComponentPointer> pointers;
	std::vector<std::size_t> componentHashes;
	EntityData() {}
};

struct EntityRegistryAddress
{
	unsigned int typeIndex;
	unsigned int index;
	EntityRegistryAddress() : typeIndex(0), index(0) {}
	EntityRegistryAddress(const unsigned int& t,const unsigned int& i) : typeIndex(t), index(i) {}
};

class EntityRegistry
{
private:
	ComponentsManager& componentsManager;
public:
	std::vector<EntityData> entities;
	EntityRegistry(ComponentsManager& componentsManagerPointer) :componentsManager(componentsManagerPointer) {}
	unsigned int RegisterEntity();

	template<class e, typename...Args>
	void AddComponent(const unsigned int& index, Args&&...args)
	{
		if (entities.size() < index)
		{
			return;
		}

		std::size_t componentToAddHash = typeid(e).hash_code();
		auto& componentHash = entities[index].componentHashes;
		if (std::find(componentHash.begin(), componentHash.end(), componentToAddHash) != componentHash.end())
		{
			return;
		}

		ComponentPointer<e> pointer = componentsManager.Add<e>(std::forward<Args>(args)...);//TODO: Component pointer is created multiple times then saved into heap, might be better if its created once. But if Add would return a pointer it might cause memory leak when the pointer is not saved. Maybe use a shared pointer?
		if (pointer.IsValid())
		{
			entities[index].pointers.emplace_back(pointer.ID(), pointer.Index(), pointer.Vector());
			entities[index].componentHashes.emplace_back(componentToAddHash);
		}
	}
	
	TypelessComponentPointer GetComponent(const unsigned int& index, const std::size_t& componentType);
};

