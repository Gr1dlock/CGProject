#ifndef RENDERMANAGER_H
#define RENDERMANAGER_H

#include <vector>
#include "color/color.h"

class RenderManager
{
public:
    RenderManager();
private:
    int screen_width;
    int screen_height;
    std::vector<std::vector<float>> depth_buffer;
    std::vector<std::vector<Color>> frame_buffer;
};

#endif // RENDERMANAGER_H
