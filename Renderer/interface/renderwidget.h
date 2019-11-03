#ifndef RENDERWIDGET_H
#define RENDERWIDGET_H

#include <QWidget>
#include <QPainter>
#include <QPaintEvent>

#include "geometry/geometry.hpp"
#include "scene/scenemanager.h"

using namespace GeometrySpace;

class RenderWidget : public QWidget
{
    Q_OBJECT
public:
    explicit RenderWidget(QWidget *parent = nullptr);

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;

private:
    QImage *image;
    SceneManager sceneManager;
    int widgetHeight;
    int widgetWidth;
    QPointF curPosition;
    CameraMovement cameraMoving;
    bool cameraRotating;
};

#endif // RENDERWIDGET_H
