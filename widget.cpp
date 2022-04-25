#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->setWindowTitle("Zeta Surgical Programming Challenge");
    t=new myThread;
    connect(this,&Widget::starting,t,[=](int i)
    {
        t->index=i;
        t->start();
    });
    connect(t,&myThread::sendimg,this,[=](Mat m)
    {
        this->img=m;
        this->update_img();
    },Qt::DirectConnection);
}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_pushButton_clicked()
{
    QString str="";
    optional<QString> file_path=QFileDialog::getOpenFileName(this,tr("select a picture"),str,"Image file(*.png *.jpg *.jpeg *.bmp)");
    if(!file_path.has_value())
    {
        return;
    }
    readPictures(file_path.value());
}
void Widget::readPictures(const QString& str)
{
    this->img=imread(str.toLatin1().data(),IMREAD_COLOR);
    if(img.empty()) return;
    t->setimg(img);
    update_img();
}
void Widget::update_img()
{
    Mat temp;
    ui->label->clear();
    cv::cvtColor(this->img,temp,cv::COLOR_BGR2RGB);
    cv::resize(temp,temp,Size(ui->label->width(),ui->label->height()), 0, 0, cv::INTER_AREA);
    QImage qimg = QImage((uchar*)temp.data,temp.cols,temp.rows,temp.step,QImage::Format_RGB888);
    ui->label->setPixmap(QPixmap::fromImage(qimg));
}

void Widget::process(int i)
{
    if(img.empty()) return;
    emit starting(i);
}
void Widget::on_pushButton_2_clicked()
{
    process(0);
}


void Widget::on_pushButton_3_clicked()
{
    process(1);
}


void Widget::on_pushButton_4_clicked()
{
    process(2);
}


void Widget::on_pushButton_5_clicked()
{
     process(3);
}


void Widget::on_pushButton_6_clicked()
{
     process(4);
}


void Widget::on_pushButton_7_clicked()
{
     process(5);
}


void Widget::on_pushButton_8_clicked()
{
     process(6);
}

