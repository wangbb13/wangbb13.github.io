#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    resize_lock(false)
{
    ui->setupUi(this);
    graphics_scene = new QGraphicsScene(this);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setScene(graphics_scene);
    graphics_scene->addItem(&pixmap_item);

    // dialog
    any_angle_dialog = new Any_Angle(this);
    connect(any_angle_dialog, &Any_Angle::slider_value_changed, this, &MainWindow::on_any_angle_slider_changed);
}

QImage MainWindow::mat_to_qimage(const cv::Mat &mat) {
    if(mat.type()==CV_8UC1) {
        QVector<QRgb> colorTable;
        for (int i=0; i<256; i++)
            colorTable.push_back(qRgb(i,i,i));
        const uchar *qImageBuffer = (const uchar*)mat.data;
        QImage img(qImageBuffer, mat.cols, mat.rows, mat.step, QImage::Format_Indexed8);
        img.setColorTable(colorTable);
        return img;
    } else if(mat.type()==CV_8UC3) {
        const uchar *qImageBuffer = (const uchar*)mat.data;
        QImage img(qImageBuffer, mat.cols, mat.rows, mat.step, QImage::Format_RGB888);
        return img.rgbSwapped();
    } else {
        return QImage();
    }
}

void MainWindow::show_image(cv::Mat mat) {
    int uw = ui->centralWidget->width();
    int uh = ui->centralWidget->height();
    int ox = (uw - mat.cols) / 2;
    int oy = (uh - mat.rows) / 2;
//    ui->statusBar->showMessage(QString::number(mat.rows) + " X " + QString::number(mat.cols));
//    ui->statusBar->showMessage(QString::number(ox) + " X " + QString::number(oy));
    ui->graphicsView->setGeometry(ox, oy, mat.cols + 2, mat.rows + 2);
    pixmap_item.setPixmap(QPixmap::fromImage(mat_to_qimage(mat)));
    ui->graphicsView->show();
}

void MainWindow::on_actionOpen_File_triggered() {
    ui->statusBar->showMessage("打开文件");
    QString filename = QFileDialog::getOpenFileName(this, tr("Load Image"), "", "Image (*.bmp | *.png | *.jpg)");
    src_mat = cv::imread(filename.toStdString());
    cur_mat = src_mat.clone();
    pre_mat = src_mat.clone();
    show_image(cur_mat);
}

void MainWindow::on_actionSave_File_triggered() {
    ui->statusBar->showMessage("保存文件");
}

void MainWindow::on_actionClockWise_90_triggered() {
    ui->statusBar->showMessage("顺时针旋转九十度");
    pre_mat = cur_mat.clone();
    int c = pre_mat.cols, r = pre_mat.rows;
    cur_mat = cv::Mat(c, r, pre_mat.type());
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            cur_mat.at<cv::Vec3b>(j, r - 1 - i) = pre_mat.at<cv::Vec3b>(i, j);
        }
    }
    show_image(cur_mat);
}

void MainWindow::on_actionAnti_ClockWise_90_triggered() {
    ui->statusBar->showMessage("逆时针旋转九十度");
    pre_mat = cur_mat.clone();
    int c = pre_mat.cols, r = pre_mat.rows;
    cur_mat = cv::Mat(c, r, pre_mat.type());
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            cur_mat.at<cv::Vec3b>(c - 1 - j, i) = pre_mat.at<cv::Vec3b>(i, j);
        }
    }
    show_image(cur_mat);
}

void MainWindow::on_actionAnyAngle_triggered() {
    ui->statusBar->showMessage("旋转任意角度");
    any_angle_dialog->show();
}

void MainWindow::on_actionHorizontalFlip_triggered() {
    ui->statusBar->showMessage("左右翻转");
    pre_mat = cur_mat.clone();
    int c = pre_mat.cols, r = pre_mat.rows;
    cur_mat = cv::Mat(r, c, pre_mat.type());
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            cur_mat.at<cv::Vec3b>(i, c - 1 - j) = pre_mat.at<cv::Vec3b>(i, j);
        }
    }
    show_image(cur_mat);
}

void MainWindow::on_actionVertical_Flip_triggered() {
    ui->statusBar->showMessage("上下翻转");
    pre_mat = cur_mat.clone();
    int c = pre_mat.cols, r = pre_mat.rows;
    cur_mat = cv::Mat(r, c, pre_mat.type());
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            cur_mat.at<cv::Vec3b>(r - 1 - i, j) = pre_mat.at<cv::Vec3b>(i, j);
        }
    }
    show_image(cur_mat);
}

void MainWindow::on_any_angle_slider_changed(int angle) {
    QString s = QString::number(angle);
    ui->statusBar->showMessage(s);
}

bool MainWindow::event(QEvent *event) {
    if (event->type() == QEvent::Resize) {
        if (!resize_lock) {
            resize_lock = true;
        } else {
            ui->statusBar->showMessage("窗口大小改变");
            show_image(cur_mat);
        }
    }
    return QWidget::event(event);
}

MainWindow::~MainWindow()
{
    delete ui;
}
