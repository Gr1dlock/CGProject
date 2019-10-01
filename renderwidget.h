#ifndef RENDERWIDGET_H
#define RENDERWIDGET_H

#include <QWidget>
#include <QPainter>

#include "geometry/geometry.hpp"
#include "render/renderer.h"
#include "model/model.h"

using namespace GeometrySpace;

class RenderWidget : public QWidget
{
    Q_OBJECT
public:
    explicit RenderWidget(QWidget *parent = nullptr);
    void renderModel(QColor color, const BaseModel &model);
protected:
    void paintEvent(QPaintEvent *event);

private:
    QImage *image;
    int widget_height;
    int widget_width;
    int depth;
};

#endif // RENDERWIDGET_H
