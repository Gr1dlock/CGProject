#include "perspective.h"

Perspective::Perspective()
{

}

Perspective::Perspective(const double &fov, const double &near, const double &far, const double &ratio)
    : field_of_view(fov),
      near_plane(near),
      far_plane(far),
      aspect_ratio(ratio)
{
}

Matrix<double> Perspective::perspectiveProjection()
{
    Matrix<double> projection(4,4);
    projection[1][1] = 1 / tan(field_of_view / 2 * M_PI / 180);
    projection[0][0] = projection[1][1] / aspect_ratio;
    projection[2][2] = (far_plane + near_plane) / (far_plane - near_plane);
    projection[3][2] = -2 * near_plane * far_plane / (far_plane - near_plane);
    projection[2][3] = 1;
    return projection;
}
