#pragma once

#include "ComponentData.h"
#include <memory>
#include <unordered_map>
#include <list>

#ifdef _DEBUG
#define CHECK_IF_SYSTEM_TYPE_IS_VALID System* s = (e*)0;
#else
#define CHECK_IF_SYSTEM_TYPE_IS_VALID
#endif 

struct TypelessSystemComponentPointerList 
{
protected:
	std::vector<int> indices;
public:
	void* vector;

	TypelessSystemComponentPointerList() :
		vector(nullptr), indices()
	{
	}

	size_t Size()
	{
		return indices.size();
	}

	void AddIndices(int i)
	{
		indices.emplace_back(i);
	}
};

template <typename e>
struct TypedSystemComponentPointerList : public TypelessSystemComponentPointerList
{
protected:
	std::vector<e>* GetTypedVector()
	{
		return ((std::vector<e>*)(vector));
	}
public:
	TypedSystemComponentPointerList() :
		TypelessSystemComponentPointerList()
	{

	}

	e& operator[] (unsigned i)
	{
		return (*GetTypedVector())[i];
	}
};


class System
{
protected:
	std::list<std::size_t> hashes;
	std::list<int> registeredComponentIDs;
	std::unordered_map<std::size_t,TypelessSystemComponentPointerList> componentPointers;
public:
	System() {};

	std::vector<int> GetMatchingTypeIndices(std::vector<std::size_t>& entityHashes);
	bool HasComponentID(const int& registeredComponentID);
	void AddComponent(std::size_t& hash, TypelessComponentPointer& pointer);

	virtual void OnUpdate();
protected:
	template<typename e>
	TypedSystemComponentPointerList<e>& GetComponentPointer()//TODO this should return a pointer
	{
		CHECK_IF_COMPONENT_TYPE_IS_VALID
		std::size_t hashCode = typeid(e).hash_code();
		if (componentPointers.find(hashCode) != componentPointers.end())
		{
			return (TypedSystemComponentPointerList<e>&)(componentPointers[hashCode]);
		}
	}

	/*
	* Note: Only call on constructor
	*/
	template<typename e>
	void InitializeSystemComponentList()
	{
		CHECK_IF_COMPONENT_TYPE_IS_VALID
		std::size_t hashCode = typeid(e).hash_code();
		componentPointers[hashCode] =  TypelessSystemComponentPointerList();
		hashes.emplace_back(hashCode);
		hashes.sort();
	}
};

class TestSystem :public System
{
public:
	TestSystem()
	{
		InitializeSystemComponentList<Size>();
	}
	void OnUpdate() override
	{
		auto a = GetComponentPointer<Size>();
		for (int i = 0; i < a.Size(); i++)
		{
			a[i] = 25;
		}
	}
};