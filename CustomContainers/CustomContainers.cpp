#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include "Vector.h"
#include "LinkedList.h"


int main()
{

    Vector2 v;
    KDNode* root = nullptr;
    for (int i = 0; i < 20; ++i)
    {
        v.x = rand() % 101;
        v.y = rand() % 101;
        KDNode* newNode = Insert(v, root, 0);
        if (root == nullptr)
        {
            root = newNode;
        }
        std::cout << "(" << v.x << ", " << v.y << ")\n";
    }

    DeleteKDTree(root);
}