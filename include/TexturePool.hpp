#pragma once

#include <string>
#include <unordered_map>

#include "MTexture.hpp"

class TexturePool{

    std::unordered_map<std::string, MTexture> m_texturepool;

public:
    TexturePool() { }


private:

};