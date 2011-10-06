#ifndef _JAUSUNSIGNEDSHORT
#define _JAUSUNSIGNEDSHORT

#include <stdlib.h>

class JausUnsignedShort
{

public:
    JausUnsignedShort::JausUnsignedShort(void);
    static unsigned char* JausUnsignedShort::jausUnsignedShortToCharArray(unsigned short s);
    static unsigned short JausUnsignedShort::charArrayToJausUnsignedShort(unsigned char* a,int start);
    int JausUnsignedShort::jausUnsignedShortIsBitSet(unsigned short b,int bit);
    int JausUnsignedShort::jausUnsignedShortSetBit(unsigned short* b,int bit);
    int JausUnsignedShort::jausUnsignedShortClearBit(unsigned short* b,int bit);
};

#endif _JAUSUNSIGNEDSHORT