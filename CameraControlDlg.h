/** ===========================================================
 * @file
 *
 * This file is a part of libface project
 * <a href="http://libface.sourceforge.net">http://libface.sourceforge.net</a>
 *
 * @date    2010-10-02
 * @brief   main window.
 *
 * @author Copyright (C) 2010 by Alex Jironkin
 *         <a href="alexjironkin at gmail dot com">alexjironkin at gmail dot com</a>
 * @author Copyright (C) 2010 by Aditya Bhatt
 *         <a href="adityabhatt at gmail dot com">adityabhatt at gmail dot com</a>
 * @author Copyright (C) 2010 by Gilles Caulier
 *         <a href="mailto:caulier dot gilles at gmail dot com">caulier dot gilles at gmail dot com</a>
 *
 * @section LICENSE
 *
 * This program is free software; you can redistribute it
 * and/or modify it under the terms of the GNU General
 * Public License as published by the Free Software Foundation;
 * either version 2, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * ============================================================ */

#ifndef CAMERACONTROLDLG_H
#define CAMERACONTROLDLG_H

#include <QtGui>
#include <QtCore>

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <QFileDialog>

#include "CanonCameraWrapper.h"
#include "BeiDou.h"

namespace Ui
{
    class MainWindow;
}

///using namespace libface;
using namespace std;

class MainWindow : public QMainWindow//, public ActionSource
{
    Q_OBJECT

public:

    MainWindow(QWidget *parent = 0);
    ~MainWindow();

//    CActionButton	_btnTakePicture;


public slots:

    void openImage();
    void openConfig();
    void InitCameras();
    void updateConfig();
    void takePicture();
    void saveConfig();
    void timerUpdate();
    void GPSInfoUpdate();

protected:

    void changeEvent(QEvent* e);

private:

    void clearScene();
    CanonCameraWrapper* pMe;
    BeiDou* pBeiDou = BeiDou::getInstance();

    //GPS
    int gps_stat;
    int ui_heading;
    float ui_longitude;//经度
    float ui_latitude;//纬度
    QString gpsStateStr;
    char headingStr[8] = {0};
    char longtitudeStr[64] = {0};
    char latitudeStr[64] = {0};
    char streetStr[MAX_STREET_LENGTH] = {0};


private:

    Ui::MainWindow*      ui;
    QGraphicsScene*      myScene;
    QGraphicsView*       myView;
    QGraphicsPixmapItem* lastPhotoItem;
    ///LibFace*             libFace;
    string               currentPhoto;
    double               scale;
    ///vector<Face>         currentFaces;
};

#endif // CAMERACONTROLDLG_H
