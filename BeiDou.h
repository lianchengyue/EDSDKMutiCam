#ifndef BEIDOU_H
#define BEIDOU_H

#include <stdlib.h>
#include <string>

#include <utils.h>
#include <EDCamErrors.h>

using namespace std;

class BeiDou //: public CPropertyComboBox, public ActionSource , public Observer
{
private:
        //singleton
        static BeiDou* instance;
        //singleton end
        int gpsstate;
        double longitude;//经度
        double latitude;//纬度
        int heading;
        char street[MAX_STREET_LENGTH];
        std::string InfoDirectory;

        int setDefaultPosition();
        int checkConnectStatus();
public:
        BeiDou();
        virtual ~BeiDou();
        //singleton
        static BeiDou* getInstance();
        //singleton end

        //interface
        int Init();
        int getPosition(int *, float *, float *);
        int getPosition(int *headVal, float *longitudeVal, float *latitudeVal, char *streetVal);
        void update();
        int getInfoFromInfoDirectory();
        int getGPSStatus();


protected:
        void IsPositionChanged();
};
#endif // BEIDOU_H
