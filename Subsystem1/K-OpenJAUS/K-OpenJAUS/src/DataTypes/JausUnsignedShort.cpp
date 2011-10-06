#include "stdafx.h"

// converts a JausUnsignedShort to a char array(char*)
// in little-endian form
unsigned char* JausUnsignedShort::jausUnsignedShortToCharArray(unsigned short s) {
	unsigned char* a = (unsigned char*)calloc(2,sizeof(unsigned char));
	a[0] = s & 0xff;
	a[1] = (s >> 8) & 0xff;
	return a;
}

// takes a byte array (char*) and converts it to
// an unsigned short in big-endian form.
unsigned short JausUnsignedShort::charArrayToJausUnsignedShort(unsigned char* a,int start) {
	unsigned short s = (a[start] & 0xff)
			| (a[start + 1] << 8) & 0xff00;
	return s;
}

// check if a bit is set in a JausUnsignedShort
int JausUnsignedShort::jausUnsignedShortIsBitSet(unsigned short b,int bit) {
    if(bit < 0 || bit > 15)
        return -1;
    else
        return (b & (0x01 << bit)) > 0 ? 1 : 0;
}

// set a bit in a JausUnsignedShort
int JausUnsignedShort::jausUnsignedShortSetBit(unsigned short* b,int bit) {
    if(bit > 15 || bit < 0) 
        return 0;
    else {
        *b |= 0x01 << bit;
        return 1;
    }
}

// clear a bit in a JausUnsignedShort
int JausUnsignedShort::jausUnsignedShortClearBit(unsigned short* b,int bit) {
    if(bit > 15 || bit < 0) 
        return 0;
    else {
        *b &= ~(0x01 << bit);
        return 1;
    }
}