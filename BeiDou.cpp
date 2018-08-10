#include "BeiDou.h"

#include  <io.h>
#include<sys/stat.h>
#include <windows.h>

void malloc_error()
{
    fprintf(stderr, "Malloc error\n");
    exit(-1);
}

int fgetl(FILE *fp, int* m_gpsstate,double* m_longitude, double* m_latitude, int* m_heading, char* m_street)
{
    int count = 0;

    if(feof(fp)) return 0;
    size_t size = MAX_STREET_LENGTH;
    char *line =  (char *)malloc(size*sizeof(char));
    if(!fgets(line, size, fp)){
        free(line);
        //exit(0);
        printf("GPS file has no content!\n");
        return ED_GPS_FILE_EMPTY;
    }

    //set GPS value start, GPS Status
    printf("GPS State from BeiDou=%s\n", line);

    if (0 == strncmp(line, "Succ", 4))
    {
        *m_gpsstate = GPS_OK;
        count++;
    }
    else if (0 == strncmp(line, "Weak", 4))
    {
        *m_gpsstate = GPS_WEAK;
        count++;
        return ED_GPS_SIGNAL_WEAK;
    }
    else if (0 == strncmp(line, "Fail", 4))
    {

        *m_gpsstate = GPS_NO_SIGNAL;
        return ED_GPS_NO_SIGNAL;
    }
    else if (0 == strncmp(line, "NIni", 4))
    {
        *m_gpsstate = GPS_NOT_INITIALIZED;
        return ED_GPS_NO_SIGNAL;
    }
    else
    {
        *m_gpsstate = GPS_UNKNOWN;
        return ED_GPS_STATE_UNKNOWN;
    }

    //set GPS value end

    size_t curr = strlen(line);

    while((line[curr-1] == '\n') && !feof(fp)){
        if(curr == size-1){
            size *= 2;
            line = (char *)realloc(line, size*sizeof(char));
            if(!line) {
                printf("%ld\n", size);
                malloc_error();
            }
        }
        size_t readsize = size-curr;
        if(readsize > INT_MAX) readsize = INT_MAX-1;
        //fgets(&line[curr], readsize, fp);
        //add
        memset(line, 0, size);
        fgets(&line[0], readsize, fp);
        //add end
        curr = strlen(line);
        //set GPS value start
        if(1 == count){
            *m_longitude = atof(line);
            printf("longitude=%5.8lf\n", *m_longitude);
            count++;
        } else if(2 == count){
            *m_latitude = atof(line);
            printf("latitude=%5.8lf\n", *m_latitude);
            count++;
        } else if(3 == count){
            *m_heading = atoi(line);
            printf("heading=%d\n", *m_heading);
            count++;
        } else if(4 == count){
            //m_street = line;
            memcpy(m_street, line, size);
            printf("street=%s\n", m_street);
            count++;
        }
        //set GPS value end
    }
    if(line[curr-1] == '\n') line[curr-1] = '\0';

    //printf("line=%s\n", line);
    return ED_SUCCESS;
}

BeiDou::BeiDou()
{
    Init();
}

BeiDou::~BeiDou()
{
}

BeiDou* BeiDou::instance = new BeiDou();
BeiDou* BeiDou::getInstance()
{
    return instance;
}

int BeiDou::Init()
{
//    InfoDirectory = "/storage/emulated/0/GPS_DataStoragelatAndlon";
    InfoDirectory = "./debug/GPS_DataStoragelatAndlon";

    setDefaultPosition();
    printf("Init longitude=%5.8lf\n", longitude);
    printf("Init latitude=%5.8lf\n", latitude);
    printf("Init heading=%d\n", heading);
    printf("Init street=%s\n\n", street);
    return 0;
}

int BeiDou::getPosition(int *headVal, float *longitudeVal, float *latitudeVal)
{
    *headVal = heading;
    *longitudeVal = longitude;
    *latitudeVal = latitude;
    return 0;
}

int BeiDou::setDefaultPosition()
{
    gpsstate = GPS_NOT_INITIALIZED;
    heading = 0;
    longitude = 0.0;
    latitude = 0.0;
    memset(street, 0, MAX_STREET_LENGTH);

    return 0;
}

int BeiDou::getPosition(int *headVal, float *longitudeVal, float *latitudeVal, char *streetVal)
{
    *headVal = heading;
    *longitudeVal = longitude;
    *latitudeVal = latitude;
    memcpy(streetVal, street, MAX_STREET_LENGTH*sizeof(char));
    return 0;
}

int BeiDou::getGPSStatus()
{
    if (GPS_OK == gpsstate)
    {
        return GPS_OK;
    }
    else if (GPS_WEAK == gpsstate)
    {
        return GPS_WEAK;
    }
    else if (GPS_NO_SIGNAL == gpsstate)
    {
        return GPS_NO_SIGNAL;
    }
    else if (GPS_NOT_INITIALIZED == gpsstate)
    {
        return GPS_NOT_INITIALIZED;
    }
    else
    {
        return GPS_UNKNOWN;
    }
}

void BeiDou::IsPositionChanged()
{

}

void BeiDou::update()
{

}

int BeiDou::checkConnectStatus()
{
    return true;
}

int BeiDou::getInfoFromInfoDirectory()
{
    //GPS_DataStoragelatAndlon是否存在
    if(-1 ==  _access("./debug/GPS_DataStoragelatAndlon", 0))
    {
        printf("no file!!! =%d\n", _access(InfoDirectory.c_str(), 0));
        return -10;
    }

    //详细文件信息结构体
    struct stat statbuf;
    stat(InfoDirectory.c_str(), &statbuf); //./debug/GPS_DataStoragelatAndlon

    FILE *infile = fopen(InfoDirectory.c_str(), "rb");
    int ret = fgetl(infile, &gpsstate, &longitude, &latitude, &heading, street);
    if(ED_GPS_FILE_EMPTY == ret)//第一次启动程序
    {
        printf("XXX\n");
        return ED_GPS_FILE_EMPTY;
    }
    //printf("streetLAST=%s\n", street);

    fclose(infile);

    return true;
}
