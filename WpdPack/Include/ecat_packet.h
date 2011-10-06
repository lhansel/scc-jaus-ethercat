
#ifndef ECAT_PACKET_H
#define ECAT_PACKET_H

#define MAC_ADDRESS_LENGTH 6

#define APRD  1
#define APWR  2
#define APRW  3
#define FPRD  4
#define FPWR  5
#define FPRW  6
#define BRD   7
#define BWR   8
#define BRW   9
#define LRD  10
#define LWR  11
#define LRW  12
#define ARMW 13
#define FRMW 14

struct EthernetHeader
{
    u_char destination[MAC_ADDRESS_LENGTH];
    u_char source[MAC_ADDRESS_LENGTH];
    UINT16 type;
};

struct EthercatFrameHeader
{
    UINT16 Res_Len_Type;
};

struct EthercatDatagramHeader
{
    u_char Cmd;
    u_char Idx;
    UINT32 Address;    // stored little endian
    UINT16 Len_R_C_R_M;  // stored little endian
    UINT16 IRQ;          // stored little endian
};

struct WorkingCounter
{
    UINT16 WKC;
};

struct EthercatPacket
{
    EthernetHeader ethernet_header;
    EthercatFrameHeader ethercat_header;
    EthercatDatagramHeader ethercat_datagram_header;
    u_char data[100];
};

// little endian to big endian, unsigned short
inline UINT16 endian_change_u16(UINT16 n)
{
    return (n << 8) | (n >> 8 );
}

// little endian to big endian, unsigned int
inline UINT32 endian_change_u32(UINT32 n)
{
    n = ((n << 8) & 0xFF00FF00 ) | ((n >> 8) & 0xFF00FF );
    return (n << 16) | (n >> 16);
}

#endif // ECAT_PACKET_H