#include "any_angle.h"
#include "ui_any_angle.h"

Any_Angle::Any_Angle(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Any_Angle)
{
    ui->setupUi(this);
    connect(ui->horizontalSlider, &QSlider::valueChanged, this, &Any_Angle::on_slider_value_changed);
}

void Any_Angle::ResetDialog() {
    ui->horizontalSlider->setValue(180);
}

void Any_Angle::on_slider_value_changed(int value) {
    int angle = value - 180;
    emit slider_value_changed(angle);
}

Any_Angle::~Any_Angle()
{
    delete ui;
}
