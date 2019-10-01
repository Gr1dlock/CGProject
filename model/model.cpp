#include "model.h"


Cube::Cube(const int &verts, const double &length_top,const double &length_bot, const double &height)
{
    computeVertices(verts, length_top, length_bot, height);
    computeTriangles(verts);
}

void Cube::computeVertices(const int &verts, const double &length_top,const double &length_bot, const double &height)
{
    double d_angle = 2 * M_PI / verts;
    double angle = 0;
    double half_height = height / 2;
    for (int i = 0; i < verts; i++)
    {
        vertices.push_back(Point<3, double>(length_bot * cos(angle), -half_height, length_bot * sin(angle)));
        angle += d_angle;
    }
    for (int i = 0; i < verts; i++)
    {
        vertices.push_back(Point<3, double>(length_top * cos(angle), half_height, length_top * sin(angle)));
        angle -= d_angle;
    }
}

void Cube::computeTriangles(const int &verts)
{
    for (int i = 0; i < verts - 2; i++)
    {
        triangles.push_back(0);
        triangles.push_back(i + 1);
        triangles.push_back(i + 2);
        triangles.push_back(verts);
        triangles.push_back(verts + i + 1);
        triangles.push_back(verts + i + 2);
    }
    for (int i = 0; i < verts; i++)
    {
        int first = verts + i;
        int second = verts - i;
        int third = verts - i - 1;
        int fourth = verts + i + 1;
        second = second == verts ? 0 : second;
        fourth = fourth == verts * 2 ? verts : fourth;
        triangles.push_back(first);
        triangles.push_back(second);
        triangles.push_back(third);
        triangles.push_back(first);
        triangles.push_back(third);
        triangles.push_back(fourth);
    }
}
