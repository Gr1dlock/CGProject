#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    renderWidget = new RenderWidget(this);
    connect(renderWidget, SIGNAL(cameraXChanged(double)), ui->cameraXSpinBox, SLOT(setValue(double)));
    connect(renderWidget, SIGNAL(cameraYChanged(double)), ui->cameraYSpinBox, SLOT(setValue(double)));
    connect(renderWidget, SIGNAL(cameraZChanged(double)), ui->cameraZSpinBox, SLOT(setValue(double)));
    connect(renderWidget, SIGNAL(yawChanged(double)), this, SLOT(updateYaw(double)));
    connect(renderWidget, SIGNAL(pitchChanged(double)), this, SLOT(updatePitch(double)));
    connect(this, SIGNAL(cameraParamChanged(CameraChange)), renderWidget, SLOT(changeCamera(CameraChange)));
    connect(this, SIGNAL(modelParamChanged(ModelChange)), renderWidget, SLOT(changeModel(ModelChange)));
    connect(renderWidget, SIGNAL(catchedNothing()), this, SLOT(switchCreatePage()));
    connect(renderWidget, SIGNAL(catchedModel(ModelAttributes)), this, SLOT(switchConfigurePage(ModelAttributes)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pitchSlider_sliderMoved(int position)
{
    ui->pitchSpinBox->setValue(position);
    CameraChange change{CameraParam::PITCH, static_cast<double>(position)};
    emit cameraParamChanged(change);
}

void MainWindow::on_pitchSpinBox_editingFinished()
{
    ui->pitchSlider->setValue(static_cast<int>(ui->pitchSpinBox->value()));
    CameraChange change{CameraParam::PITCH, ui->pitchSpinBox->value()};
    emit cameraParamChanged(change);
}

void MainWindow::on_yawSlider_sliderMoved(int position)
{
    ui->yawSpinBox->setValue(position);
    CameraChange change{CameraParam::YAW, static_cast<double>(position)};
    emit cameraParamChanged(change);
}

void MainWindow::on_yawSpinBox_editingFinished()
{
    ui->yawSlider->setValue(static_cast<int>(ui->yawSpinBox->value()));
    CameraChange change{CameraParam::YAW, ui->yawSpinBox->value()};
    emit cameraParamChanged(change);
}

void MainWindow::updateYaw(double yaw)
{
    ui->yawSlider->setValue(static_cast<int>(yaw));
    ui->yawSpinBox->setValue(yaw);
}

void MainWindow::updatePitch(double pitch)
{
    ui->pitchSlider->setValue(static_cast<int>(pitch));
    ui->pitchSpinBox->setValue(pitch);
}


void MainWindow::on_cameraXSpinBox_editingFinished()
{
    CameraChange change{CameraParam::POS_X, ui->cameraXSpinBox->value()};
    emit cameraParamChanged(change);
}

void MainWindow::on_cameraYSpinBox_editingFinished()
{
    CameraChange change{CameraParam::POS_Y, ui->cameraYSpinBox->value()};
    emit cameraParamChanged(change);
}

void MainWindow::on_cameraZSpinBox_editingFinished()
{
    CameraChange change{CameraParam::POS_Z, ui->cameraZSpinBox->value()};
    emit cameraParamChanged(change);
}

void MainWindow::on_nearPlaneSpinBox_editingFinished()
{
    CameraChange change{CameraParam::NEAR_PLANE, ui->nearPlaneSpinBox->value()};
    emit cameraParamChanged(change);
}

void MainWindow::on_farPlaneSpinBox_editingFinished()
{
    CameraChange change{CameraParam::FAR_PLANE, ui->farPlaneSpinBox->value()};
    emit cameraParamChanged(change);
}

void MainWindow::on_fovSpinBox_editingFinished()
{
    CameraChange change{CameraParam::FOV, ui->fovSpinBox->value()};
    emit cameraParamChanged(change);
}

void MainWindow::on_speedSpinBox_editingFinished()
{
    renderWidget->setCameraSpeed(ui->speedSpinBox->value());
}

void MainWindow::on_sensSpinBox_editingFinished()
{
    CameraChange change{CameraParam::SENSITIVITY, ui->sensSpinBox->value()};
    emit cameraParamChanged(change);
}

void MainWindow::on_createButton_clicked()
{
    ModelAttributes attributes;
    attributes.lengthTop = ui->createTopLengthSpinBox->value();
    attributes.lengthBot = ui->createBotLengthSpinBox->value();
    attributes.height = ui->createHeightSpinBox->value();
    attributes.nVerts = ui->createVertsSpinBox->value();
    int nModels = renderWidget->addModel(attributes);
    if (nModels == MAX_MODELS)
    {
        ui->createButton->setEnabled(false);
    }
}

void MainWindow::switchCreatePage()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::switchConfigurePage(ModelAttributes attributes)
{
    ui->stackedWidget->setCurrentIndex(0);
    ui->changeTopLengthSpinBox->setValue(attributes.lengthTop);
    ui->changeBotLengthSpinBox->setValue(attributes.lengthBot);
    ui->changeHeightSpinBox->setValue(attributes.height);
    ui->changeVertsSpinBox->setValue(attributes.nVerts);
}

void MainWindow::on_changeTopLengthSpinBox_editingFinished()
{
    ModelChange change{ModelParam::TOP, ui->changeTopLengthSpinBox->value()};
    emit modelParamChanged(change);
}

void MainWindow::on_changeBotLengthSpinBox_editingFinished()
{
    ModelChange change{ModelParam::BOT, ui->changeBotLengthSpinBox->value()};
    emit modelParamChanged(change);
}

void MainWindow::on_changeHeightSpinBox_editingFinished()
{
    ModelChange change{ModelParam::HEIGHT, ui->changeHeightSpinBox->value()};
    emit modelParamChanged(change);
}

void MainWindow::on_changeVertsSpinBox_editingFinished()
{
    ModelChange change{ModelParam::VERTS, static_cast<double>(ui->changeVertsSpinBox->value())};
    emit modelParamChanged(change);
}

void MainWindow::on_deleteModelButton_clicked()
{
    renderWidget->deleteModel();
    ui->stackedWidget->setCurrentIndex(1);
    ui->createButton->setEnabled(true);
}

void MainWindow::on_rotateXButton_clicked()
{
    ModelMovement move{ui->angleXSpinBox->value(), 0, 0, 0, 0, 0};
    renderWidget->moveModel(move);
}

void MainWindow::on_rotateYButton_clicked()
{
    ModelMovement move{0, ui->angleYSpinBox->value(), 0, 0, 0, 0};
    renderWidget->moveModel(move);
}

void MainWindow::on_rotateZButton_clicked()
{
    ModelMovement move{0, 0, ui->angleZSpinBox->value(), 0, 0, 0};
    renderWidget->moveModel(move);
}

void MainWindow::on_transferButton_clicked()
{
    ModelMovement move{0, 0, 0, ui->dxSpinBox->value(), ui->dySpinBox->value(), ui->dzSpinBox->value()};
    renderWidget->moveModel(move);
}

void MainWindow::on_clearSceneButton_clicked()
{
    renderWidget->deleteAllModels();
    ui->createButton->setEnabled(true);
}
