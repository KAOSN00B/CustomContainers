#pragma once
#include <algorithm>
#include <functional>
#include "Vector.h"

// Useful for RTS games, RPGs, nearest-neighbor queries
template <typename T, std::size_t K>
class KDTree
{
private:
    struct KDNode
    {
        const T* point = nullptr;
        const void* userData = nullptr;
        KDNode* left = nullptr;
        KDNode* right = nullptr;
    };

public:
    KDTree() = default;

    ~KDTree()
    {
        Terminate();
    }

    void AddItem(const T* point, const void* userData)
    {
        KDNode* node = new KDNode();
        node->point = point;
        node->userData = userData;
        mNodes.PushBack(node);
    }

    void RemoveItem(const void* userData)
    {
        std::size_t count = mNodes.Size();
        for (std::size_t i = 0; i < count; ++i)
        {
            if (mNodes[i]->userData == userData)
            {
                KDNode* temp = mNodes[i];
                mNodes[i] = mNodes[count - 1];
                mNodes[count - 1] = temp;

                delete temp;
                mNodes.PopBack();
                break;
            }
        }
    }

    void BuildTree()
    {
        Clear(mRoot);
        mRoot = BuildTree(mNodes, 0);
    }

    void FindInRange(
        Vector<const void*>& result,
        const T* minRange,
        const T* maxRange,
        std::function<bool(const void*)> filterCB = nullptr)
    {
        FindInRange(result, minRange, maxRange, mRoot, 0, filterCB);
    }

    const void* FindNearest(const T* target)
    {
        KDNode* node = FindNearest(target, mRoot, 0);
        return node ? node->userData : nullptr;
    }

    void Terminate()
    {
        for (std::size_t i = 0; i < mNodes.Size(); ++i)
        {
            delete mNodes[i];
            mNodes[i] = nullptr;
        }
        mNodes.Clear();
        mRoot = nullptr;
    }

private:
    KDNode* BuildTree(Vector<KDNode*>& nodes, int depth)
    {
        if (nodes.Size() == 0)
            return nullptr;

        std::sort(nodes.Begin(), nodes.End(),
            [depth](const KDNode* a, const KDNode* b)
            {
                return a->point[depth] < b->point[depth];
            });

        int median = nodes.Size() / 2;
        KDNode* node = nodes[median];

        Vector<KDNode*> left;
        Vector<KDNode*> right;

        left.Resize(median);
        right.Resize(nodes.Size() - median - 1);

        int index = 0;
        for (auto it = nodes.Begin(); it != nodes.Begin() + median; ++it)
            left[index++] = *it;

        index = 0;
        for (auto it = nodes.Begin() + median + 1; it != nodes.End(); ++it)
            right[index++] = *it;

        node->left = BuildTree(left, (depth + 1) % K);
        node->right = BuildTree(right, (depth + 1) % K);

        return node;
    }

    void FindInRange(
        Vector<const void*>& found,
        const T* minRange,
        const T* maxRange,
        KDNode* node,
        int depth,
        std::function<bool(const void*)>& filterCB)
    {
        if (!node)
            return;

        bool valid = (!filterCB || filterCB(node->userData));

        if (valid)
        {
            for (std::size_t i = 0; i < K; ++i)
            {
                if (node->point[i] < minRange[i] || node->point[i] > maxRange[i])
                {
                    valid = false;
                    break;
                }
            }
        }

        if (valid)
            found.PushBack(node->userData);

        if (minRange[depth] < node->point[depth])
            FindInRange(found, minRange, maxRange, node->left, (depth + 1) % K, filterCB);

        if (maxRange[depth] > node->point[depth])
            FindInRange(found, minRange, maxRange, node->right, (depth + 1) % K, filterCB);
    }

    float DistanceSquared(const T* a, const T* b) const
    {
        float dist = 0.0f;
        for (std::size_t i = 0; i < K; ++i)
        {
            float d = a[i] - b[i];
            dist += d * d;
        }
        return dist;
    }

    KDNode* Closest(KDNode* a, KDNode* b, const T* target) const
    {
        if (!a) return b;
        if (!b) return a;
        return (DistanceSquared(a->point, target) <
            DistanceSquared(b->point, target)) ? a : b;
    }

    KDNode* FindNearest(const T* target, KDNode* node, int depth)
    {
        if (!node)
            return nullptr;

        KDNode* next =
            (target[depth] < node->point[depth]) ? node->left : node->right;
        KDNode* other =
            (target[depth] < node->point[depth]) ? node->right : node->left;

        KDNode* best = Closest(
            FindNearest(target, next, (depth + 1) % K),
            node,
            target);

        float axisDist = node->point[depth] - target[depth];
        if (DistanceSquared(best->point, target) >= axisDist * axisDist)
        {
            best = Closest(
                FindNearest(target, other, (depth + 1) % K),
                best,
                target);
        }

        return best;
    }

    void Clear(KDNode* node)
    {
        if (!node)
            return;

        Clear(node->left);
        Clear(node->right);

        node->left = nullptr;
        node->right = nullptr;
    }

private:
    Vector<KDNode*> mNodes;
    KDNode* mRoot = nullptr;
};
