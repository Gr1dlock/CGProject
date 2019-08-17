#include "renderwidget.h"

RenderWidget::RenderWidget(QWidget *parent) : QWidget(parent)
{
    widget_width = 960;
    widget_height = 960;
    depth = 255;
    image = new QImage(widget_width, widget_height, QImage::Format_RGB32);
    image->fill(Qt::black);
    setGeometry(10, 10, widget_width, widget_height);
}

void RenderWidget::renderTriangle(QColor color, const Point2D<int> *triangle)
{
    QPainter painter(image);
    painter.setPen(color);
}

void RenderWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.drawImage(0, 0, *image);
    Q_UNUSED(event);
}

