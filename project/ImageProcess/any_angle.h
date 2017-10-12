#ifndef ANY_ANGLE_H
#define ANY_ANGLE_H

#include <QDialog>

namespace Ui {
class Any_Angle;
}

class Any_Angle : public QDialog
{
    Q_OBJECT

public:
    explicit Any_Angle(QWidget *parent = 0);
    ~Any_Angle();
    void ResetDialog();

private slots:
    void on_slider_value_changed(int value);

signals:
    void slider_value_changed(int angle);

private:
    Ui::Any_Angle *ui;
};

#endif // ANY_ANGLE_H
