#ifndef CANONCAMERAWRAPPER_H
#define CANONCAMERAWRAPPER_H

#pragma once

//Written by Theo Watson - theo@openframeworks.cc

//NOTE
//We are missing code for legacy devices
//We are missing some mac specific snippets
//Both should be easy to integrate

//You also need the Canon SDK which you can request from them or possibily find by other means floating around in the ether.

#include "EDSDK.h"
#include "EDSDKErrors.h"
#include "EDSDKTypes.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "BeiDou.h"

#include <string>
using namespace std;

//#define HAVE_OF


#ifndef BYTE
//    #define BYTE unsigned char
#endif

#define CAM_NUM_MAX 10

typedef enum{
    CAMERA_UNKNOWN,
    CAMERA_READY,
    CAMERA_OPEN,
    CAMERA_CLOSED,
}cameraState;

static int sdkRef = 0;

static void easyRelease(EdsBaseRef &ref){
    if(ref != NULL){
        EdsRelease(ref);
        ref = NULL;
    }
}

//NOTE
//We are missing code for legacy devices
//We are missing some mac specific snippets
//Both should be easy to integrate

class CanonCameraWrapper{
private:
    //singleton
    static CanonCameraWrapper* instance;
    //singleton end
public:
    //singleton
    static CanonCameraWrapper* getInstance();
    //singleton end

 //---------------------------------------------------------------------
    CanonCameraWrapper();
    ~CanonCameraWrapper();

    //---------------------------------------------------------------------
    //  SDK AND SESSION MANAGEMENT
    //---------------------------------------------------------------------
    //bool InitCam(int cameraID);   //You must call this to init the canon sdk
    bool InitMutiCam();
    //void destroy();             //To clean up - also called by destructor
    void destroyMutiCam();

    bool openMutiCamSession();
    //bool openSession();         //Begins communication with camera
    bool closeMutiCamSession();
    //bool closeSession();        //Ends communication with camera.
                                //Note on sessions: Commands like takePicture
                                //will open a session if none exists. This
                                //is slower though so consider calling it
                                //once at the begining of your app.

    //---------------------------------------------------------------------
    //  CONFIG
    //---------------------------------------------------------------------

    void setDeleteFromCameraAfterDownload(bool deleteAfter);
    void setDownloadPath(string downloadPathStr);
    void enableDownloadOnTrigger();     //Trigger meaning takePicture
    void disableDownloadOnTrigger();    //Trigger meaning takePicture

    //---------------------------------------------------------------------
    //  ACTIONS
    //---------------------------------------------------------------------
    bool takePicture();   //Takes a picture. If enabled it will also download
                          //the image to the folder set by the download path.

    bool sendCommand( EdsCameraCommand inCommand,  EdsInt32 inParam = 0);


    //---------------------------------------------------------------------
    //  LIVE VIEW
    //---------------------------------------------------------------------

    bool beginLiveView();                   //starts live view
    bool endLiveView();                     //ends live view

    bool grabPixelsFromLiveView(int rotateByNTimes90 = 0); //capture the live view to rgb pixel array
    bool saveImageFromLiveView(string saveName);

    bool getLiveViewActive();               //true if live view is enabled
    int getLiveViewFrameNo();               //returns the number of live view frames passed
    void resetLiveViewFrameCount();         //resets to 0

    bool isLiveViewPixels();                //true if there is captured pixels
    int getLiveViewPixelWidth();            //width of live view pixel data
    int getLiveViewPixelHeight();           //height of live view pixel data
    unsigned char * getLiveViewPixels();    //returns captured pixels

    //---------------------------------------------------------------------
    //  MISC EXTRA STUFF
    //---------------------------------------------------------------------

    string getLastImageName();  //The full path of the last downloaded image
    string getLastImagePath();  //The name of the last downloaded image

    //This doesn't work perfectly - for some reason it can be one image behind
    //something about how often the camera updates the SDK.
    //Having the on picture event registered seems to help.
    //But downloading via event is much more reliable at the moment.

    //WARNING - If you are not taking pictures and you have bDeleteAfterDownload set to true
    //you will be deleting the files that are on the camera.
    //Simplified: be careful about calling this when you haven't just taken a photo.
    bool downloadLastImage();

    //Hmm - might be needed for threading - currently doesn't work
    bool isTransfering();


    protected:
        //---------------------------------------------------------------------
        //  PROTECTED STUFF
        //---------------------------------------------------------------------

        bool downloadImage(EdsDirectoryItemRef directoryItem);
        static EdsError EDSCALLBACK handleObjectEvent(EdsObjectEvent inEvent, EdsBaseRef object, EdsVoid *inContext);
        static EdsError EDSCALLBACK handlePropertyEvent(EdsPropertyEvent inEvent,  EdsPropertyID inPropertyID, EdsUInt32 inParam, EdsVoid * inContext);
        static EdsError EDSCALLBACK handleStateEvent(EdsStateEvent inEvent, EdsUInt32 inEventData, EdsVoid * inContext);


        void registerCallback();
        bool preCommand();
        void postCommand();

        int livePixelsWidth;
        int livePixelsHeight;
        unsigned char * livePixels;

        EdsUInt32 evfMode;
        EdsUInt32 device;

        int liveViewCurrentFrame;

        string lastImageName;
        string lastImagePath;
        string downloadPath;
        string downloadMutiPath[CAM_NUM_MAX];
        bool downloadEnabled;
        bool bDeleteAfterDownload;
        bool registered;
        bool needToOpen;

        cameraState state;
        EdsCameraRef        theCamera ;
        EdsCameraRef        theMutiCamera[CAM_NUM_MAX] ;
        //EdsCameraRef        theCamera1;
        //EdsCameraRef        theCamera2;
        EdsCameraListRef	theCameraList;

        EdsUInt32 cameraCount;
};

#endif // CANONCAMERAWRAPPER_H
