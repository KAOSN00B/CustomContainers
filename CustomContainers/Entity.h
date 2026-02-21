#pragma once
#include "TextureManager.h"
#include "Vector2.h"
#include <cstdlib>
#include <iostream>

class Entity
{
private:
    size_t mTextureId;
    Vector2 mPosition;

public:
    void Initialize(const std::string& textureFilePath)
    {
        mTextureId = TextureManager::GetInstance().LoadTexture(textureFilePath);

        mPosition.x = static_cast<float>(rand() % 100 - 50);
        mPosition.y = static_cast<float>(rand() % 100 - 50);
    }

    void Update()
    {
        mPosition.x += static_cast<float>(rand() % 11 - 5);
        mPosition.y += static_cast<float>(rand() % 11 - 5);
    }

    void Render()
    {
        Texture* texture = TextureManager::GetInstance().GetTexture(mTextureId);

        if (texture)
        {
            texture->Print();
        }

        std::cout << "Position: ("
            << mPosition.x
            << ", "
            << mPosition.y
            << ")\n";
    }



    float DistanceFromOrigin() const
    {
        return sqrt(mPosition.x * mPosition.x +
            mPosition.y * mPosition.y);
    }
};
