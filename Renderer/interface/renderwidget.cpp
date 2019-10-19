#include "renderwidget.h"
#include <QtDebug>

RenderWidget::RenderWidget(QWidget *parent) : QWidget(parent)
{
    widget_width = 960;
    widget_height = 960;
    image = new QImage(widget_width, widget_height, QImage::Format_RGB32);
    image->fill(Qt::black);
    setGeometry(10, 10, widget_width, widget_height);
}

void RenderWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.drawImage(0, 0, *image);
    Q_UNUSED(event)
}

