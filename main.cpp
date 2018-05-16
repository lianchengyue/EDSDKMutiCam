//#include <QCoreApplication>
#include <QApplication>
//wrapper
#include "CanonCameraWrapper.h"
//UI
#include "CameraControlDlg.h"

int main(int argc, char *argv[])
#if 0
{
//    QCoreApplication a(argc, argv);

//    return a.exec();

    CanonCameraWrapper ESCamera;
//    ESCamera.setup(0);
    ESCamera.setup(0);
    //ESCamera.openSession();
    Sleep(200);
    //ESCamera.beginLiveView();
    Sleep(200);
    ESCamera.takePicture();
    Sleep(200);
    ESCamera.downloadLastImage();
    //while(1){};
    return 0;
}

#else
{
    QApplication a(argc, argv);
    MainWindow w;

    //test for单例测试，是否成功
    /*
    CanonCameraWrapper* singleton1 = CanonCameraWrapper::getInstance();
    CanonCameraWrapper* singleton2 = CanonCameraWrapper::getInstance();
    if (singleton1 == singleton2)
        printf("singleton1 = singleton2\n");
    */
    //test for单例测试，是否成功end

    //北斗初始化
    //BeiDou *mBDGPS = new BeiDou();

    //相机初始化
    CanonCameraWrapper* ESCamera = CanonCameraWrapper::getInstance();
    //ESCamera->InitCam(0);
    ESCamera->InitMutiCam();
    ESCamera->setDownloadPath("d:\\EDSDK_File\\");

    ESCamera->beginLiveView();

    printf("InitESCamera() finish.\n");

    w.show();
    return a.exec();
}
#endif
