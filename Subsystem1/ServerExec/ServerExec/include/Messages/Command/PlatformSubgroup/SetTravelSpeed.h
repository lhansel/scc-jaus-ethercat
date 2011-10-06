#ifndef _SETTRAVELSPEED
#define _SETTRAVELSPEED

#include <stdlib.h>
#include <string.h>

class SetTravelSpeed {

public:
    SetTravelSpeed::SetTravelSpeed(void);
    static unsigned char* SetTravelSpeed::
			createSetTravelSpeed(unsigned char* msg,unsigned short speed);
    static unsigned char SetTravelSpeed::
			retrieveSetTravelSpeedData(unsigned char* msg);
    static void SetTravelSpeed::printSetTravelSpeedArray(unsigned char* msg);
};

#endif _SETTRAVELSPEED