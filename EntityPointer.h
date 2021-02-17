#pragma once
#include "Entity.h"
template<typename e>
class EntityPointer
{
private:
	std::vector<Entity>* vector;
	int index;
public:
	EntityPointer(std::vector<Entity>* vectorPointer, const int& entityIndexInVector) :
		vector(vectorPointer), index(entityIndexInVector){}

	e& Get()
	{
		return (*vector)[index];
	}
private:
	EntityPointer();
};
