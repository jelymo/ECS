#pragma once
#include <vector>
#ifdef _DEBUG
#define CHECK_IF_COMPONENT_TYPE_IS_VALID static ComponentData* check = (e*)0;//Check to see if e is derrived from ComponentData
#else
#define CHECK_IF_COMPONENT_TYPE_IS_VALID
#endif 

struct ComponentData
{
};

struct PositionAngle :ComponentData
{
public:
	float x, y, angle;
	PositionAngle() :x(0.0f), y(0.0f), angle(0.0f) {};
	PositionAngle(float xp, float yp, float anglep) :
		x(xp), y(yp), angle(anglep) {};
};

struct Size :ComponentData
{
public:
	float size;
	Size() :size(0.0f) {};
	Size(float sizep) :size(sizep) {};
};

struct TypelessComponentPointer
{
protected:
	unsigned int id;
	bool isValid;
	unsigned int index;
	void* vector;
public:
	TypelessComponentPointer() :id(0), isValid(false), index(0), vector(nullptr)
	{
	}

	TypelessComponentPointer(const unsigned int& idp,const unsigned int i, void* vec) :
		id(idp), isValid(true), index(i), vector(vec) {}

	friend bool operator== (TypelessComponentPointer& lhs, TypelessComponentPointer& rhs)
	{
		return (lhs.index == rhs.index);
	}

	bool IsValid() { return isValid; }
	unsigned int Index() { return index; }
	void* VoidVector() { return (vector); }
	unsigned int ID() { return id; }
};

template <typename e>
struct ComponentPointer: public TypelessComponentPointer
{
public:
	ComponentPointer() :TypelessComponentPointer()
	{
	}

	ComponentPointer(int idp, int i, std::vector<e>* vec) :
		TypelessComponentPointer(idp, i,vec) {}

	//This is read only
	e Get()
	{
		return (*((std::vector<e>*)vector))[index];
	}

	template  <typename... Args>
	void Set(Args&&...args)//TODO: This would be a scheduled job also this is bad
	{
		if (isValid)
		{
			(*((std::vector<e>*)vector))[index] = e(std::forward<Args>(args)...);
		}
	}

	bool IsValid() { return isValid; }
	int Index() { return index; }
	std::vector<e>* Vector() { return ((std::vector<e>*)vector); }
};
