#pragma once

#include <map>

template <class T>
class Creator
{
public:
	virtual ~Creator() {}
	virtual T* Create() = 0;
};

// DerivedCreator is Creator<BaseType> which creates a 
// DerivedType, not a Creator<DerivedType>
template <class DerivedType, class BaseType>
class DerivedCreator : public Creator<BaseType>
{
public:
	BaseType* Create()
	{
		return new DerivedType;
	}
};

template <class T, class Key>
class Factory
{
public:
	void Register(Key Id, Creator<T>* Fn)
	{
		FunctionMap[Id] = Fn;
	}

	T* Create(Key Id)
	{
		return FunctionMap[Id]->Create();
	}

	~Factory()
	{
		auto i = FunctionMap.begin();
		while (i != FunctionMap.end())
		{
			delete (*i).second;
			++i;
		}
	}
private:
	std::map<Key, Creator<T>*> FunctionMap;
};