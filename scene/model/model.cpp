#include "model.h"
#include "model.h"

Cube::Cube(const ModelAttributes &attributes)
{
    computeVertices(attributes);
    computeTriangles(attributes.nVerts);
}

void Cube::changeVerticesCount(const int &nVerts)
{
    ModelAttributes attributes;
    attributes.lengthTop = vertices[0].x();
    attributes.lengthBot = vertices[countVertices() / 2].x();
    attributes.height = -vertices[0].y() * 2;
    attributes.nVerts = nVerts;
    vertices.clear();
    triangles.clear();
    computeVertices(attributes);
    computeTriangles(nVerts);
}

void Cube::changeTopLength(const double &length)
{
    int verts = countVertices();
    double d_angle = 4 * M_PI / verts;
    double angle = 0;
    for (int i = verts / 2; i < verts; i++)
    {
        vertices[i].setX(length * cos(angle));
        vertices[i].setZ(length * sin(angle));
        angle -= d_angle;
    }
}

void Cube::changeBotLength(const double &length)
{
    int verts = countVertices() / 2;
    double d_angle = 2 * M_PI / verts;
    double angle = 0;
    for (int i = 0; i < verts; i++)
    {
        vertices[i].setX(length * cos(angle));
        vertices[i].setZ(length * sin(angle));
        angle += d_angle;
    }
}

void Cube::changeHeight(const double &height)
{
    int verts = countVertices() / 2;
    double half_height = height / 2;
    for (int i = 0; i < verts; i++)
    {
        vertices[i].setY(-half_height);
        vertices[i + verts].setY(half_height);
    }
}

void Cube::computeVertices(const ModelAttributes &attributes)
{
    double d_angle = 2 * M_PI / attributes.nVerts;
    double angle = 0;
    double half_height = attributes.height / 2;
    for (int i = 0; i < attributes.nVerts; i++)
    {
        vertices.emplace_back(attributes.lengthBot * cos(angle), -half_height, attributes.lengthBot * sin(angle));
        angle += d_angle;
    }
    for (int i = 0; i < attributes.nVerts; i++)
    {
        vertices.emplace_back(attributes.lengthTop * cos(angle), half_height, attributes.lengthTop * sin(angle));
        angle -= d_angle;
    }
}

void Cube::computeTriangles(const int &nVerts)
{
    MathVector<double> normal(3);
    for (int i = 0; i < nVerts - 2; i++)
    {
        triangles.push_back(0);
        triangles.push_back(i + 1);
        triangles.push_back(i + 2);
        normal = MathVector<double>(vertices[i + 1] - vertices[0]) ^ MathVector<double>(vertices[i + 2] - vertices[i + 1]);
        normal.normalize();
        normals.push_back(normal);
        triangles.push_back(nVerts);
        triangles.push_back(nVerts + i + 1);
        triangles.push_back(nVerts + i + 2);
        normal = MathVector<double>(vertices[nVerts + i + 1] - vertices[nVerts]) ^ MathVector<double>(vertices[nVerts + i + 2] - vertices[nVerts + i + 1]);
        normal.normalize();
        normals.push_back(normal);
    }
    for (int i = 0; i < nVerts; i++)
    {
        int first = nVerts + i;
        int second = nVerts - i;
        int third = nVerts - i - 1;
        int fourth = nVerts + i + 1;
        second = second == nVerts ? 0 : second;
        fourth = fourth == nVerts * 2 ? nVerts : fourth;
        triangles.push_back(first);
        triangles.push_back(second);
        triangles.push_back(third);
        normal = MathVector<double>(vertices[second] - vertices[first]) ^ MathVector<double>(vertices[third] - vertices[second]);
        normal.normalize();
        normals.push_back(normal);
        triangles.push_back(first);
        triangles.push_back(third);
        triangles.push_back(fourth);
        normal = MathVector<double>(vertices[third] - vertices[first]) ^ MathVector<double>(vertices[fourth] - vertices[third]);
        normal.normalize();
        normals.push_back(normal);
    }
}
