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

#include "CameraControlDlg.h"
#include "ui_CameraControlDlg.h"

#include <QTimer>

using namespace std;

MainWindow::MainWindow(QWidget* parent)
          : QMainWindow(parent),
            ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->connect(ui->openImageBtn, SIGNAL(clicked()), this, SLOT(openImage()));
    this->connect(ui->openConfigBtn, SIGNAL(clicked()), this, SLOT(openConfig()));
    this->connect(ui->InitCamerasBtn, SIGNAL(clicked()), this, SLOT(InitCameras()));
    this->connect(ui->takePictureBtn, SIGNAL(clicked()), this, SLOT(takePicture()));
    this->connect(ui->updateDatabaseBtn, SIGNAL(clicked()), this, SLOT(updateConfig()));
    this->connect(ui->saveConfigBtn, SIGNAL(clicked()), this, SLOT(saveConfig()));

    QTimer *timer = new QTimer(this);
    this->connect(timer,SIGNAL(timeout()),this,SLOT(timerUpdate()));
    timer->start(1000);

    myScene = new QGraphicsScene();

    QHBoxLayout* layout = new QHBoxLayout;
    myView              = new QGraphicsView(myScene);
    layout->addWidget(myView);

    ui->widget->setLayout(layout);

    myView->setRenderHints(QPainter::Antialiasing);
    myView->show();

    ui->configLocation->setText(QDir::currentPath());

    QDateTime current_date_time =QDateTime::currentDateTime();
    QString current_date =current_date_time.toString("yyyy.MM.dd hh:mm:ss.zzz ddd");
    //printf("current_date=%s\n", current_date);

    ///set Listener&Observer, FLQ
    pMe = CanonCameraWrapper::getInstance();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::changeEvent(QEvent* e)
{
    QMainWindow::changeEvent(e);
    switch (e->type())
    {
        case QEvent::LanguageChange:
            ui->retranslateUi(this);
            break;
        default:
            break;
    }
}

void MainWindow::openImage()
{
    QString file = QFileDialog::getOpenFileName(this,
            tr("Open Image"), QDir::currentPath(), tr("Image Files (*.png *.jpg *.bmp)"));

    clearScene();

    currentPhoto   = string(file.toLatin1().data());
    QPixmap* photo = new QPixmap(file);
    lastPhotoItem  = new QGraphicsPixmapItem(*photo);

    myScene->addItem(lastPhotoItem);
}

void MainWindow::openConfig()
{

}

void MainWindow::InitCameras()
{

}

void MainWindow::updateConfig()
{

}

void MainWindow::clearScene()
{

}

void MainWindow::takePicture()
{
    pMe->takePicture();
}

void MainWindow::saveConfig()
{
    //libFace->loadConfig(libFace->getConfig());
//    libFace->saveConfig(QDir::currentPath().toStdString());
//    libFace->saveConfig("/home/montafan/Qt5.6.2/project/libface_ui/");
}

void MainWindow::timerUpdate()
{
    QDateTime time = QDateTime::currentDateTime();
    QString str = time.toString("yyyy-MM-dd hh:mm:ss dddd");
    //ui->label->setText(str);
    ui->timeDisplayText->setText(str);
}


