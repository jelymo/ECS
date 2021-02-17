#pragma once
#include "System.h"
#include "EntityPointer.h"
#include "EntityRegistry.h"

//TODO: Delete entity, might need to write a custom container that doesnt need type and just saves how many bytes
//TODO: 
class ECS
{
private:
	std::vector<System> systems;
	std::vector<Entity> entities;
	ComponentsManager componentsManager;
	bool hasStarted;
	EntityRegistry registry;
public:
	static ECS& GetInstance()
	{
		static ECS instance;
		return instance;
	}

	static void  DeleteSystems()
	{
		GetInstance().DeleteSystems_I();
	}

	template<class e, typename... Args>
	static void AddSystem(Args&&...args)
	{
		GetInstance().AddSystem_I<e>(std::forward<Args>(args)...);
	}

	static void OnStart()
	{
		GetInstance().OnStart_I();
	}
	
	static void OnUpdate()
	{
		GetInstance().OnUpdate_I();
	}

	template<class e, typename...Args>
	static EntityPointer<e> CreateEntity(Args&&...args)
	{
		return GetInstance().CreateEntity_I<e>(std::forward<Args>(args)...);
	}

	template<class e,class EntityType, typename...Args>
	static void AddComponentToEntity(EntityType& entity, Args&&...args)
	{
		GetInstance().AddComponentToEntity_I<e>(entity, std::forward<Args>(args)...);
	}

private:
	void AddEntityToSystem_I(std::vector<TypelessComponentPointer>& pointers, std::vector<std::size_t>& hashes);
	void OnStart_I();
	void OnUpdate_I();
	void DeleteSystems_I();

	template<class e, typename... Args>
	void AddSystem_I(Args&&...args)
	{
		CHECK_IF_SYSTEM_TYPE_IS_VALID
		systems.emplace_back(e(std::forward<Args>(args)...));
	}

	template<class e, typename...Args>
	EntityPointer<e> CreateEntity_I(Args&&...args)
	{
		entities.emplace_back(registry,std::forward<Args>(args)...);
		size_t lastIndex = entities.size()-1;
		return EntityPointer<e>(&entities, lastIndex);
	}

	template<class e, class EntityType, typename...Args>
	void AddComponentToEntity_I(EntityType& entity, Args&&...args)
	{
		auto ent = entity.Get();
		registry.AddComponent<e>(ent.index, std::forward<Args>(args)...);
		if (hasStarted)
		{
			AddEntityToSystem_I(registry.entities[ent.index].pointers, registry.entities[ent.index].componentHashes);
		}
	}

	ECS();
	ECS(const ECS&) = delete;
};

