#pragma once
#include <memory>
#include"EntityRegistry.h"
#ifdef _DEBUG
#define CHECK_IF_TYPE_IS_ENTITY Entity* check = e * (0);
#else
#define CHECK_IF_TYPE_IS_ENTITY
#endif 

class Entity
{
protected:
	
	EntityRegistry& registry;
public:
	unsigned int index;
	Entity(EntityRegistry& entityRegistyPointer);
	~Entity();

	template<typename e>
	ComponentPointer<e> GetComponentPointer()
	{
		CHECK_IF_COMPONENT_TYPE_IS_VALID
				
		std::size_t hashCode = typeid(e).hash_code();
		auto componentPointer = registry.GetComponent(index, hashCode);
		if (componentPointer.IsValid())
		{
			return (*(ComponentPointer<e>*) & componentPointer);
		}
		return ComponentPointer<e>();
	}
	
protected:
	void UpdateSystems();
	template<typename e, typename... Args>
	void AddComponent(Args&&... args)
	{
		registry.AddComponent<e>(index, std::forward<Args>(args)...);
	}

private:
};

