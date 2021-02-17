#pragma once
#include <cstring>
class ComponentArray
{
private:
    char* data;
    unsigned int dataTypeSize;
    unsigned int reservedSize;
    unsigned int currentSize;
public:
    ComponentArray(const unsigned int& size);
    ~ComponentArray();
    unsigned int GetDataTypeSize();
    unsigned int GetCount();
    char* Get(const unsigned int& index);
    void PushBack(char * dataToAdd);
    void Reserve(const unsigned int& count);
    void Erase(const unsigned int& index);
    char* operator [](const unsigned int& index);

    template<class e>
    void PushBack(const e& element)
    {
        if(sizeof(e) == dataTypeSize)
        {
            PushBack((char*)(&element));
        }
    }

    template<class e>
    e& Get(const unsigned int& index)
    {
        return *((e*)Get(index));
    }


private:
    void Resize(const unsigned int& additionalSize);

};