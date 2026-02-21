#include <ctime>
#include "Vector.h"
#include "Entity.h"
#include "Globals.h"
#include "Map.h"

void TestUnorderedMap()
{
    
}

int main()
{
    srand(static_cast<unsigned>(time(nullptr)));
    Map<int, int> myMap;
    for (int i = 0; i < 10; ++i)
    {
        int value = rand() % 1000;
        myMap.Insert(i, value);
        std::cout << value << " ";
    }
    std::cout << "\n";
    std::cout << "Has Key 3: " << myMap.Has(3) << "\n";
    std::cout << "Has Key 30: " << myMap.Has(30) << "\n";

    Vector<int> allKeys;
    myMap.ObtainKeys(allKeys);

    for (std::size_t i = 0; i < allKeys.Size(); ++i)
    {
        std::cout << allKeys[i] << " ";
    }
    std::cout << "\n";
    std::cout << "Value with key 7: " << myMap[7] << "\n";
    myMap.Remove(6);
    allKeys.Clear();
    std::cout << "Obtain all keys without 6:\n";

    for (std::size_t i = 0; i < allKeys.Size(); ++i)
    {
        std::cout << allKeys[i] << " ";
    }
    myMap.Clear();
    return 0;
}
