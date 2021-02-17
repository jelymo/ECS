#pragma once


#pragma once
#include <unordered_map>
#include <typeinfo>
#include "ComponentData.h"
/*
* How do add Component:
* 1. Increment COMPONENT_TYPE_COUNT
* 2. Add to ComponentType enum
* 3. Get the hash code of the type via typeid(PositionAngle).hash_code()
* 4. Make a vector of components
* 5. 
*/

class ComponentsManager
{
private:
	std::unordered_map <std::size_t, void*> registeredComponents;
	int registeredComponentsCount;
public:
	ComponentsManager();

	template <typename e, typename... Args>
	ComponentPointer<e> Add(Args&&... args)
	{
		std::vector<e>* vector = GetVector<e>();
		if (vector != nullptr)
		{
			registeredComponentsCount++;
			vector->emplace_back(std::forward<Args>(args)...);
			return ComponentPointer<e>(registeredComponentsCount, vector->size() - 1, vector);
		}
		return ComponentPointer<e>();
	}

	template <typename e>
	std::vector<e>* GetVector()
	{
		std::size_t hashCode = typeid(e).hash_code();
		std::vector<e>* vector = nullptr;
		if (registeredComponents.find(hashCode) != registeredComponents.end())
		{
			vector = (std::vector<e>*)registeredComponents[hashCode];
		}
		else
		{
			vector = new std::vector<e>();
			registeredComponents[hashCode] = vector;
		}
		return vector;
	}

	void DeleteData();

private:

	ComponentsManager(const ComponentsManager&) = delete;

};

