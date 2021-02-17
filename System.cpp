#include "System.h"
#include <algorithm>

std::vector<int> System::GetMatchingTypeIndices(std::vector<std::size_t>& entityHashes)
{
    size_t size = hashes.size();
    int count = 0;
    std::vector<int> indices;
    indices.reserve(size);
    size_t entityHashesSize = entityHashes.size();
    for (int i = 0; i < entityHashesSize;i++)
    {
        if (std::binary_search(hashes.begin(), hashes.end(), entityHashes[i]))
        {
            count++;
            indices.emplace_back(i);
            if (count == size)
            {
                return indices;
            }
        }
    }

    return indices;
}

bool System::HasComponentID(const int& registeredComponentID)
{
    return std::binary_search(registeredComponentIDs.begin(), registeredComponentIDs.end(), registeredComponentID);
}

void System::AddComponent(std::size_t& hash, TypelessComponentPointer& pointer)
{
    if (componentPointers[hash].vector == nullptr)
    {
        componentPointers[hash].vector = pointer.VoidVector();
    }
    componentPointers[hash].AddIndices(pointer.Index());
    registeredComponentIDs.emplace_back(pointer.ID());
}

void System::OnUpdate()
{
}
