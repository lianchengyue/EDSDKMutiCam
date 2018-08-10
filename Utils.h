#ifndef UTILS_H
#define UTILS_H

#define MAX_STREET_LENGTH 512

typedef enum {
    GPS_OK=0,
    GPS_WEAK,
    GPS_NO_SIGNAL,
    GPS_UNKNOWN,
    GPS_NOT_INITIALIZED,
} GPS_STATE;

#endif // UTILS_H
