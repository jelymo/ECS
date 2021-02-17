#include "ComponentsManager.h"


void ComponentsManager::DeleteData()
{
	for (auto data : registeredComponents)
	{
		delete data.second;
	}

	registeredComponents.clear();
}

ComponentsManager::ComponentsManager():
	registeredComponentsCount(0)
{
	
}
//
//template <typename e>
//e* Component::Add_I()
//{
//	e* vector = GetVector_I();
//	if (vector != nullptr)
//	{
//		vector->emplace_back();
//		return &((*vector)[vector->size() - 1]);
//	}
//}
//
//template<typename e>
//std::vector<e>* Component::GetVector_I()
//{
//	std::size_t hashCode = typeid(e).hash_code(e);
//	switch (hashCode)
//	{
//	case PositionAngleHashCode:
//		if (positionAngleComponents == nullptr)
//		{
//			positionAngleComponents = new std::vector<PositionAngle>();
//		}
//		return positionAngleComponents;
//	case SizeHashCode:
//		if (sizeComponents == nullptr)
//		{
//			sizeComponents = new std::vector<Size>();
//		}
//		return sizeComponents;
//	default:
//		return nullptr;
//	}
//}
//
