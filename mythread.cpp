#include "mythread.h"

myThread::myThread(QObject *parent)
    : QThread{parent}
{
    Lpool.resize(7);
    //True analygraph
    Lpool[0]=(Mat_<double>(3, 3) << 0.299, 0.587, 0.114, 0., 0., 0., 0., 0., 0.);
    //Gray analygraph
    Lpool[1]=(Mat_<double>(3, 3) << 0.299, 0.587, 0.114, 0., 0., 0., 0., 0., 0.);
    //Color analygraph
    Lpool[2]=(Mat_<double>(3, 3) << 1., 0., 0., 0., 0., 0., 0., 0., 0.);
    //Half-Color analygraph
    Lpool[3]=(Mat_<double>(3, 3) << 0.299, 0.587, 0.114, 0., 0., 0., 0., 0., 0.);
    //3DTV-optimized analygraph
    Lpool[4]=(Mat_<double>(3, 3) << 0., 0.7, 0.3, 0., 0., 0., 0., 0., 0.);
    //DuBois analygraph
    Lpool[5]=(Mat_<double>(3, 3) << 0.437, 0.449, 0.164, -0.062, -0.062, -0.024, -0.048, -0.050, -0.017);
    //Roscolux analygraph
    Lpool[6]=(Mat_<double>(3, 3) << 0.3185, 0.0769, 0.0109, 0.1501, 0.0767, 0.0056, 0.0007, 0.0020, 0.0156);
    Rpool.resize(7);
    //True analygraph
    Rpool[0]=(Mat_<double>(3, 3) << 0., 0., 0., 0., 0., 0.,0.299, 0.587, 0.114);
    //Gray analygraph
    Rpool[1]=(Mat_<double>(3, 3) << 0., 0., 0., 0.299, 0.587, 0.114,0.299, 0.587, 0.114);
    //Color analygraph
    Rpool[2]=(Mat_<double>(3, 3) << 0., 0., 0., 0., 1., 0., 0., 0., 1.);
    //Half-Color analygraph
    Rpool[3]=(Mat_<double>(3, 3) << 0., 0., 0., 0., 1., 0., 0., 0., 1.);
    //3DTV-optimized analygraph
    Rpool[4]=(Mat_<double>(3, 3) << 0., 0., 0., 0., 1., 0., 0., 0., 1.);
    //DuBois analygraph
    Rpool[5]=(Mat_<double>(3, 3) << -0.011, -0.032, -0.007, 0.377, 0.761, 0.009, -0.026, -0.093, 1.234);
    //Roscolux analygraph
    Rpool[6]=(Mat_<double>(3, 3) << 0.0174, 0.0484, 0.1402, 0.0184, 0.1807, 0.0458, 0.0286, 0.0991, 0.7662);
}
void myThread::run()
{
    Mat& Lfilter=Lpool[index];
    Mat& Rfilter=Rpool[index];
    img=left.clone();
    Mat temp;
    for(int i=0;i<img.rows;++i)
    {
        for(int j=0;j<img.cols;++j)
        {
            temp=Lfilter*Vec3bToMat(left.at<Vec3b>(i,j));
            temp+=Rfilter*Vec3bToMat(right.at<Vec3b>(i,j));
            img.at<Vec3b>(i,j)[0]=temp.at <double>(2,0);
            img.at<Vec3b>(i,j)[1]=temp.at <double>(1,0);
            img.at<Vec3b>(i,j)[2]=temp.at <double>(0,0);
        }
    }
    emit sendimg(img);
}
void myThread::setimg(Mat& m)
{
    img=m;
    this->left=this->img(cv::Range(0,img.rows),cv::Range(0,img.cols/2)).clone();
    this->right=this->img(cv::Range(0,img.rows),cv::Range(img.cols/2,img.cols)).clone();
}
Mat myThread::Vec3bToMat(const Vec3b& in)
{
    cv::Mat mat(3,1, CV_64FC1);
    mat.at <double>(0,0) = in [2];
    mat.at <double>(1,0) = in [1];
    mat.at <double>(2,0) = in [0];
    return mat;
}
