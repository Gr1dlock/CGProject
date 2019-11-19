#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "interface/renderwidget.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pitchSlider_sliderMoved(int position);
    void on_pitchSpinBox_editingFinished();
    void on_yawSlider_sliderMoved(int position);
    void on_yawSpinBox_editingFinished();
    void updateYaw(double yaw);
    void updatePitch(double pitch);
    void on_cameraXSpinBox_editingFinished();
    void on_cameraYSpinBox_editingFinished();
    void on_cameraZSpinBox_editingFinished();
    void on_nearPlaneSpinBox_editingFinished();
    void on_farPlaneSpinBox_editingFinished();
    void on_fovSpinBox_editingFinished();
    void on_speedSpinBox_editingFinished();
    void on_sensSpinBox_editingFinished();
    void on_createButton_clicked();
    void switchCreatePage();
    void switchConfigurePage(ModelAttributes attributes);
    void on_changeTopLengthSpinBox_editingFinished();
    void on_changeBotLengthSpinBox_editingFinished();
    void on_changeHeightSpinBox_editingFinished();
    void on_changeVertsSpinBox_editingFinished();
    void on_deleteModelButton_clicked();

    void on_rotateXButton_clicked();

    void on_rotateYButton_clicked();

    void on_rotateZButton_clicked();

    void on_transferButton_clicked();

    void on_clearSceneButton_clicked();

private:
    Ui::MainWindow *ui;
    RenderWidget *renderWidget;

signals:
    void cameraParamChanged(CameraChange);
    void modelParamChanged(ModelChange);

};
#endif // MAINWINDOW_H
