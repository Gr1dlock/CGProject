#include "renderwidget.h"
#include <QtDebug>

RenderWidget::RenderWidget(QWidget *parent) : QWidget(parent)
{
    widget_width = 960;
    widget_height = 960;
    depth = 255;
    image = new QImage(widget_width, widget_height, QImage::Format_RGB32);
    image->fill(Qt::black);
    setGeometry(10, 10, widget_width, widget_height);
}

void RenderWidget::renderModel(QColor color, const BaseModel &model)
{
    QPainter painter(image);
    painter.setPen(color);
    Renderer renderer;
    renderer.setView(widget_width, widget_height);
    renderer.setCamera(Point<3, double>(0, 50, 200), Point<3, double>(0, 0, 0), MathVector<double>(0, 1, 0));
    renderer.setPerspective(90, 0.1, 100, 1);
    for (int i = 0; i < model.countTriangles(); i++)
    {
        std::vector<Point<3, double>> triangle(3);
        model.getTriangle(triangle, i);
        renderer.renderTriangle(&painter, triangle);
    }
    update();
}

void RenderWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.drawImage(0, 0, *image);
    Q_UNUSED(event)
}

