#pragma once

#include <string>

class Texture
{
public:
    Texture(int width, int height, std::string type, std::string path);
    void ActiveTexture();
    unsigned int GetId();

private:
    int _width;
    int _height;
    int _nrChannels;
    unsigned int _id;
    std::string _type;
    std::string _path;
};