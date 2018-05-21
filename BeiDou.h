#ifndef BEIDOU_H
#define BEIDOU_H

#include <stdlib.h>
#include <string>

using namespace std;

class BeiDou //: public CPropertyComboBox, public ActionSource , public Observer
{
private:
        int heading;
        float longitude;//经度
        float latitude;//纬度 //
        string a;
public:
        BeiDou();
        virtual ~BeiDou();

        //interface
        int Init();
        int getPosition(int *, float *, float *);
        void update();


protected:
        void OnPositionChange();
};
#endif // BEIDOU_H
