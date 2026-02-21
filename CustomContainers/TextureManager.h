#pragma once
#include "UnorderedMap.h"
#include "Texture.h"
#include "Globals.h"

class TextureManager
{
private:
    UnorderedMap<std::size_t, Texture> mTextures;

    static TextureManager* sInstance;

    TextureManager() {}

public:
    static TextureManager& GetInstance()
    {
        if (!sInstance)
            sInstance = new TextureManager();

        return *sInstance;
    }

    std::size_t LoadTexture(const std::string& filePath)
    {
        std::size_t uniqueId = Globals::HashFunction(filePath);

        if (!mTextures.Has(uniqueId))
        {
            mTextures.Insert(uniqueId, Texture(filePath));
        }

        return uniqueId;
    }

    Texture* GetTexture(std::size_t id)
    {
        std::size_t index;
        Texture temp("");

        if (mTextures.Find(id, temp))
        {
            return &mTextures[id];
        }

        return nullptr;
    }

};

TextureManager* TextureManager::sInstance = nullptr;
