#include "Entity.h"
#include "ECS.h"

Entity::Entity(EntityRegistry& entityRegistyPointer):
registry(entityRegistyPointer)
{
	index = registry.RegisterEntity();
}

Entity::~Entity()
{

}



void Entity::UpdateSystems()
{
	//ECS::AddEntityToSystem(componentPointer, componentHashes);
}


