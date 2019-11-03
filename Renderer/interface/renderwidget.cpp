#include "renderwidget.h"

#include <QtDebug>

RenderWidget::RenderWidget(QWidget *parent) : QWidget(parent)
{
    widgetWidth = 1280;
    widgetHeight = 720;
    cameraRotating = false;
    cameraMoving = {false, false, false, false};
    image = new QImage(widgetWidth, widgetHeight, QImage::Format_RGB32);
    setGeometry(10, 10, widgetWidth, widgetHeight);
    CameraAttributes attributes { Point<3, double>(0,0,500), -90, 0, MathVector<double>(0,1,0), {90, 0.2, 600, 16 / 9.0}};
    sceneManager = SceneManager(image, widgetWidth, widgetHeight, attributes);
    ModelAttributes attrs { 100, 100, 200, 6};
    setFocusPolicy(Qt::StrongFocus);
    sceneManager.addModel(attrs);
    update();
}

void RenderWidget::mousePressEvent(QMouseEvent *event)
{
    QPointF position = event->screenPos();
    if (event->button() == Qt::RightButton)
    {
        int index = sceneManager.getObjectIndex(position.x(), position.y());
        if (index < 0)
        {
        }
        else
        {
        }
    }
    else if (event->button() == Qt::LeftButton)
    {
        cameraRotating = true;
        setCursor(Qt::ClosedHandCursor);
        curPosition = position;
    }
}

void RenderWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.drawImage(0, 0, *image);
    Q_UNUSED(event)
}

void RenderWidget::mouseMoveEvent(QMouseEvent *event)
{
    if (cameraRotating)
    {
        QPointF newPosition = event->screenPos();
        CameraTransformation transformation(CameraRotation{newPosition.x() - curPosition.x(), curPosition.y() - newPosition.y()});
        sceneManager.changeCamera(transformation);
        curPosition = newPosition;
        update();
    }
}

void RenderWidget::mouseReleaseEvent(QMouseEvent *event)
{
    if (cameraRotating && event->button() == Qt::LeftButton)
    {
        cameraRotating = false;
        setCursor(Qt::ArrowCursor);
    }
}

void RenderWidget::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_W || event->key() == Qt::Key_S || event->key() == Qt::Key_A || event->key() == Qt::Key_D)
    {
        if (event->key() == Qt::Key_W)
        {
            cameraMoving.forward = true;
        }
        else if (event->key() == Qt::Key_S)
        {
            cameraMoving.backward = true;
        }
        else if (event->key() == Qt::Key_A)
        {
            cameraMoving.left = true;
        }
        else if (event->key() == Qt::Key_D)
        {
            cameraMoving.right = true;
        }
        CameraTransformation transformation(cameraMoving);
        sceneManager.changeCamera(transformation);
        update();
    }
}

void RenderWidget::keyReleaseEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_W || event->key() == Qt::Key_S || event->key() == Qt::Key_A || event->key() == Qt::Key_D)
    {
        if (event->key() == Qt::Key_W)
        {
            cameraMoving.forward = false;
        }
        else if (event->key() == Qt::Key_S)
        {
            cameraMoving.backward = false;
        }
        else if (event->key() == Qt::Key_A)
        {
            cameraMoving.left = false;
        }
        else if (event->key() == Qt::Key_D)
        {
            cameraMoving.right = false;
        }
    }
}

