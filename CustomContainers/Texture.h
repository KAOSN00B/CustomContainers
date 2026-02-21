#pragma once
#include <string>
#include <iostream>

class Texture
{
private:
    std::string mFilePath;

public:

    Texture() : mFilePath("") {}

    Texture(const std::string& filePath)
        : mFilePath(filePath)
    {
    }

    void Print() const
    {
        std::cout << "Rendering " << mFilePath << std::endl;
    }
};
