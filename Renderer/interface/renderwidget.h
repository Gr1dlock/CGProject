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
protected:
    void paintEvent(QPaintEvent *event);

private:
    QImage *image;
    int widget_height;
    int widget_width;
};

#endif // RENDERWIDGET_H
