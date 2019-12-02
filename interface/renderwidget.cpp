#include "renderwidget.h"

#include <QtDebug>

RenderWidget::RenderWidget(QWidget *parent) : QWidget(parent)
{
    widgetWidth = 1030;
    widgetHeight = 710;
    cameraSpeed = 100;
    cameraRotating = false;
    cameraMovement = {false, false, false, false};
    movementTimer.setInterval(1000 / cameraSpeed);
    image = new QImage(widgetWidth, widgetHeight, QImage::Format_RGB32);
    setGeometry(20, 20, widgetWidth, widgetHeight);
    CameraAttributes attributes { Vector3D<double>(0,0,500), -90, 0, Vector3D<double>(0,1,0),
        {90, 0.1, 1000, widgetWidth / static_cast<double>(widgetHeight)}};
    controller = Controller(image, widgetWidth, widgetHeight, attributes);

    setFocusPolicy(Qt::StrongFocus);

    connect(&movementTimer, SIGNAL(timeout()), this, SLOT(moveCamera()));
    update();
}

void RenderWidget::setCameraSpeed(const int &speed)
{
    cameraSpeed = speed;
    movementTimer.setInterval(1000 / cameraSpeed);
}

int RenderWidget::addModel(const ModelAttributes &attributes)
{
    int nModels = controller.addModel(attributes);
    update();
    return nModels;
}

void RenderWidget::moveModel(const ModelMovement &movement)
{
    ModelTransformation transformation(movement);
    controller.changeModel(transformation, currentModel);
    update();
}

void RenderWidget::deleteModel()
{
    controller.deleteModel(currentModel);
    update();
}

void RenderWidget::deleteAllModels()
{
    controller.deleteAllModels();
    update();
}

void RenderWidget::mousePressEvent(QMouseEvent *event)
{
    QPointF position = event->localPos();
    if (event->button() == Qt::RightButton)
    {
        currentModel = controller.getObjectIndex(position.x(), position.y());
        if (currentModel < 0)
        {
            emit catchedNothing();
        }
        else
        {
            ModelAttributes attributes = controller.getModelAttributes(currentModel);
            emit catchedModel(attributes);
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
        QPointF newPosition = event->localPos();
        CameraTransformation transformation(CameraRotation{newPosition.x() - curPosition.x(), newPosition.y() - curPosition.y()});
        controller.changeCamera(transformation);
        curPosition = newPosition;
        emit pitchChanged(controller.getPitch());
        emit yawChanged(controller.getYaw());
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
            cameraMovement.forward = true;
        }
        else if (event->key() == Qt::Key_S)
        {
            cameraMovement.backward = true;
        }
        else if (event->key() == Qt::Key_A)
        {
            cameraMovement.left = true;
        }
        else if (event->key() == Qt::Key_D)
        {
            cameraMovement.right = true;
        }
        if (!movementTimer.isActive())
        {
            movementTimer.start();
        }
    }
}

void RenderWidget::keyReleaseEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_W || event->key() == Qt::Key_S || event->key() == Qt::Key_A || event->key() == Qt::Key_D)
    {
        if (event->key() == Qt::Key_W)
        {
            cameraMovement.forward = false;
        }
        else if (event->key() == Qt::Key_S)
        {
            cameraMovement.backward = false;
        }
        else if (event->key() == Qt::Key_A)
        {
            cameraMovement.left = false;
        }
        else if (event->key() == Qt::Key_D)
        {
            cameraMovement.right = false;
        }
        if (!(cameraMovement.forward || cameraMovement.backward || cameraMovement.left || cameraMovement.right))
        {
            movementTimer.stop();
        }
    }
}

void RenderWidget::moveCamera()
{
    CameraTransformation transformation(cameraMovement);
    controller.changeCamera(transformation);
    Vector3D<double> position(controller.getCameraPos());
    emit cameraXChanged(position.x());
    emit cameraYChanged(position.y());
    emit cameraZChanged(position.z());
    update();
}

void RenderWidget::changeCamera(CameraChange change)
{
    CameraTransformation transformation(change);
    controller.changeCamera(transformation);
    update();
}

void RenderWidget::changeModel(ModelChange change)
{
    ModelTransformation transformation(change);
    controller.changeModel(transformation, currentModel);
    update();
}

