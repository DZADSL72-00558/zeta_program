#ifndef WIDGET_H
#define WIDGET_H

#include "mythread.h"
QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_pushButton_clicked();
    void readPictures(const QString& str);
    void update_img();
    void process(int);
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_4_clicked();
    void on_pushButton_5_clicked();
    void on_pushButton_6_clicked();
    void on_pushButton_7_clicked();
    void on_pushButton_8_clicked();
private:
    Ui::Widget *ui;
    Mat img;
    myThread* t;
signals:
    void starting(int i);
};
#endif // WIDGET_H
