#include "renderer.h"

Renderer::Renderer()
{

}

void Renderer::renderTriangle(QPainter *painter, const Point3D<double> &P0, const Point3D<double> &P1, const Point3D<double> &P2)
{
    if (P1.y() < P0.y())
        qSwap(P1, P0);
    if (P2.y() < P0.y())
        qSwap(P2, P0);
    if (P2.y() < P1.y())
        qSwap(P2, P1);

    x01 = Interpolate(y0, x0, y1, x1)
    x12 = Interpolate(y1, x1, y2, x2)
    x02 = Interpolate(y0, x0, y2, x2)


            remove_last(x01)
            x012 = x01 + x12

            m = x012.length / 2
            if x02[m] < x012[m] {
        x_left = x02
                x_right = x012
    } else {
    x_left = x012
            x_right = x02
}

    for y = y0 to y2 {
            for x = x_left[y - y0] to x_right[y - y0] {
            canvas.PutPixel(x, y, color)
}
}
}


template<typename T>
double *Renderer::inerpolate(const T &x0, const T &y0, const T &x1, const T &y1) const
{
    if (x1 < x0)
    {
        std::swap(x1, x0);
        std::swap(y1, y0);
    }
    else if (x0 == x1)
        return new double[1] {y0};
int length = static_cast<int>(round(x1 - x0));
double *result = new double [length];
double a = static_cast<double>(y1 - y0) / length;
double y = y0;
for (int i = x0; i <= x1; i++)
{
    result[i] = y;
    y += a;
}
return result;
}
