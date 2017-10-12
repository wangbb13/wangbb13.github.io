#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QImage>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QFileDialog>
#include <QEvent>
#include <QWidget>
#include <QString>
#include <opencv2/opencv.hpp>
#include "any_angle.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionOpen_File_triggered();
    void on_actionSave_File_triggered();
    void on_actionClockWise_90_triggered();
    void on_actionAnti_ClockWise_90_triggered();
    void on_actionAnyAngle_triggered();
    void on_actionHorizontalFlip_triggered();
    void on_actionVertical_Flip_triggered();

private slots:
    void on_any_angle_slider_changed(int angle);

private:
    void show_image(cv::Mat mat);
    QImage mat_to_qimage(const cv::Mat &mat);
    bool event(QEvent *event);

private:
    Ui::MainWindow *ui;
    QGraphicsScene *graphics_scene;
    QGraphicsPixmapItem pixmap_item;
    cv::Mat cur_mat;
    cv::Mat pre_mat;
    cv::Mat src_mat;

    // not elegant
    bool resize_lock;

    // dialog
    Any_Angle *any_angle_dialog;
};

#endif // MAINWINDOW_H
