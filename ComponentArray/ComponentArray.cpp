#include "ComponentArray.h"
#include <stdlib.h>

ComponentArray::ComponentArray(const unsigned int& size)
    :dataTypeSize(size) ,  reservedSize(0), currentSize(0), data((char*)malloc(size))
{

}

ComponentArray::~ComponentArray()
{
    delete data;
}

unsigned int ComponentArray::GetDataTypeSize()
{
    return dataTypeSize;
}

unsigned int ComponentArray::GetCount()
{
    return currentSize/dataTypeSize;
}

char* ComponentArray::Get(const unsigned int& index)
{
    return data+(index*dataTypeSize);
}

void ComponentArray::PushBack(char* dataToAdd)
{
    if(reservedSize<currentSize+dataTypeSize)
    {
        Resize(dataTypeSize);
    }
    memcpy(data+currentSize,dataToAdd,dataTypeSize);
    currentSize+=dataTypeSize;
}

void ComponentArray::Reserve(const unsigned int& count)
{
    Resize(count*dataTypeSize);
}

void ComponentArray::Erase(const unsigned int& index)
{   
    if(index<=GetCount())
    {
        memcpy(data+(index*dataTypeSize),data+((index+1)*dataTypeSize),currentSize-((index+1)*dataTypeSize));
        currentSize-=dataTypeSize;
    }
}

void ComponentArray::Resize(const unsigned int& additionalSize)
{
    char* newLocation = (char*)malloc(currentSize+additionalSize);
    memcpy(newLocation,data,currentSize);
    delete data;
    data = newLocation;
    reservedSize += additionalSize;
}

char* ComponentArray::operator [](const unsigned int& index)
{
    return Get(index);
}