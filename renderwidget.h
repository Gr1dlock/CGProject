#ifndef RENDERWIDGET_H
#define RENDERWIDGET_H

#include <QWidget>
#include <QPainter>

#include "geometry/geometry.hpp"

using namespace GeometrySpace;

class RenderWidget : public QWidget
{
    Q_OBJECT
public:
    explicit RenderWidget(QWidget *parent = nullptr);
    void renderTriangle(QColor color, const Point2D<int> *triangle);
protected:
    void paintEvent(QPaintEvent *event);

private:
    QImage *image;
    int widget_height;
    int widget_width;
    int depth;
};

#endif // RENDERWIDGET_H
