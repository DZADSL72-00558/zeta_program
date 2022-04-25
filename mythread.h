#ifndef MYTHREAD_H
#include <QWidget>
#include <QFileDialog>
#include <QMessageBox>
#include <QString>
#include <optional>
#include <QDebug>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <QVector>
#include <QThread>
using namespace cv;
using namespace std;
class myThread : public QThread
{
    Q_OBJECT
public:
    explicit myThread(QObject *parent = nullptr);
    void setimg(Mat&);
    int index=0;
protected:
    void run() override;
signals:
    void sendimg(cv::Mat);
private:
    Mat Vec3bToMat(const Vec3b& );
    Mat left;
    Mat right;
    QVector<Mat> Lpool;
    QVector<Mat> Rpool;
    Mat img;
};

#endif // MYTHREAD_H
