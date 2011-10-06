#include <pcap.h>
#include "RawSoc.h"
#include "functions.h"
#include "ecat_packet.h"
#include "sendpack.h"
#include "ClientSetup.h"
#include "stdafx.h"

extern RawSoc * raw_soc;
extern ClientSetup *clientSetup;

u_char test_dest_1[MAC_ADDRESS_LENGTH] = {1, 1, 1, 1, 1, 1};
u_char test_src_1[MAC_ADDRESS_LENGTH]  = {2, 2, 2, 2, 2, 2};

const UINT16 ETHERCAT_FRAME_HEADER_TYPE_1 = 0x1000;

// all ethernet packets will have the same header, so do it in one place
void initialize_EtherNET_header(EthercatPacket & packet)
{
    memcpy(packet.ethernet_header.destination, test_dest_1, MAC_ADDRESS_LENGTH);
    memcpy(packet.ethernet_header.source, test_src_1, MAC_ADDRESS_LENGTH);
    packet.ethernet_header.type = endian_change_u16(0x88a4);
}

void initialize_EtherCAT_frame_header_1(EthercatPacket & packet, const UINT16 DGRAM_LENGTH)
{
    EthercatFrameHeader test_ecat_frm_hdr_1;
    test_ecat_frm_hdr_1.Res_Len_Type = sizeof(EthercatDatagramHeader) + DGRAM_LENGTH + sizeof(WorkingCounter) | ETHERCAT_FRAME_HEADER_TYPE_1;
    packet.ethercat_header = test_ecat_frm_hdr_1;
}

void LRD_1()
{
    const UINT16 DGRAM_LENGTH = 40;
    EthercatPacket packet;

    initialize_EtherNET_header(packet);

    initialize_EtherCAT_frame_header_1(packet, DGRAM_LENGTH);

    // initialize EtherCAT datagram header
    /*                                           Cmd   Idx            Address                   Len_R_C_R_M           IRQ     */
    EthercatDatagramHeader test_ecat_dg_hdr_1 = {LRD,   1,    endian_change_u32(0x12345678),   DGRAM_LENGTH,   endian_change_u16(0x1234)};
    packet.ethercat_datagram_header = test_ecat_dg_hdr_1;

    // working counter
    UINT16 & WCT = (UINT16 &)packet.data[DGRAM_LENGTH];
    WCT = 4;

    int packet_length = sizeof(EthernetHeader) + sizeof(EthercatFrameHeader) + sizeof(EthercatDatagramHeader) + DGRAM_LENGTH + sizeof(WorkingCounter);
	raw_soc->send( (u_char *) &packet, packet_length);
}

void LWR_1()
{
    const UINT16 DGRAM_LENGTH = 40;
    EthercatPacket packet;

    initialize_EtherNET_header(packet);

    initialize_EtherCAT_frame_header_1(packet, DGRAM_LENGTH);

    // initialize EtherCAT datagram header
    /*                                           Cmd   Idx            Address                   Len_R_C_R_M           IRQ     */
    EthercatDatagramHeader test_ecat_dg_hdr_1 = {LWR,   1,    endian_change_u32(0x12345678),   DGRAM_LENGTH,   endian_change_u16(0x1234)};
    packet.ethercat_datagram_header = test_ecat_dg_hdr_1;

    packet.data[0] = 0x10;
	packet.data[1] = 0x00;
	packet.data[2] = 0x10;
	packet.data[3] = 0x00;
	
	//Add JAUS packet to ethercat datagram data
	for(int i=0; i < jaus_packet_length; i++) {
	    packet.data[4+i] = jaus_packet[i];
	}
	
    // working counter?
    int packet_length = sizeof(EthernetHeader) + sizeof(EthercatFrameHeader) + sizeof(EthercatDatagramHeader) + DGRAM_LENGTH + jaus_packet_length + sizeof(WorkingCounter);
	raw_soc->send( (u_char *) &packet, packet_length);
}

void LWR_2()
{
    const UINT16 DGRAM_LENGTH = 40;
    EthercatPacket packet;

    initialize_EtherNET_header(packet);

    initialize_EtherCAT_frame_header_1(packet, DGRAM_LENGTH);

    // initialize EtherCAT datagram header
    /*                                           Cmd   Idx            Address                   Len_R_C_R_M           IRQ     */
    EthercatDatagramHeader test_ecat_dg_hdr_1 = {LWR,   1,    endian_change_u32(0x12345678),   DGRAM_LENGTH,   endian_change_u16(0x1234)};
    packet.ethercat_datagram_header = test_ecat_dg_hdr_1;
    
    packet.data[0] = 0x10;
	packet.data[1] = 0x00;
	packet.data[2] = 0x00;
	packet.data[3] = 0x00;
	
	//Add JAUS packet to ethercat datagram data
	for(int i=0; i < jaus_packet_length; i++) {
	    packet.data[4+i] = jaus_packet[i];
	}
	
    // working counter?
    int packet_length = sizeof(EthernetHeader) + sizeof(EthercatFrameHeader) + sizeof(EthercatDatagramHeader) + DGRAM_LENGTH + jaus_packet_length + sizeof(WorkingCounter);
	raw_soc->send( (u_char *) &packet, packet_length);
}

void LWR_3()
{
    const UINT16 DGRAM_LENGTH = 40;
    EthercatPacket packet;

    initialize_EtherNET_header(packet);

    initialize_EtherCAT_frame_header_1(packet, DGRAM_LENGTH);

    // initialize EtherCAT datagram header
    /*                                           Cmd   Idx            Address                   Len_R_C_R_M           IRQ     */
    EthercatDatagramHeader test_ecat_dg_hdr_1 = {LWR,   1,    endian_change_u32(0x12345678),   DGRAM_LENGTH,   endian_change_u16(0x1234)};
    packet.ethercat_datagram_header = test_ecat_dg_hdr_1;
    
    packet.data[0] = 0x00;
	packet.data[1] = 0x00;
	packet.data[2] = 0x10;
	packet.data[3] = 0x00;
	
	//Add JAUS packet to ethercat datagram data
	for(int i=0; i < jaus_packet_length; i++) {
	    packet.data[4+i] = jaus_packet[i];
	}
	
    // working counter?
    int packet_length = sizeof(EthernetHeader) + sizeof(EthercatFrameHeader) + sizeof(EthercatDatagramHeader) + DGRAM_LENGTH + jaus_packet_length + sizeof(WorkingCounter);
	raw_soc->send( (u_char *) &packet, packet_length);
}

void LWR_0()
{
    const UINT16 DGRAM_LENGTH = 40;
    EthercatPacket packet;

    initialize_EtherNET_header(packet);

    initialize_EtherCAT_frame_header_1(packet, DGRAM_LENGTH);

    // initialize EtherCAT datagram header
    /*                                           Cmd   Idx            Address                   Len_R_C_R_M           IRQ     */
    EthercatDatagramHeader test_ecat_dg_hdr_1 = {LWR,   1,    endian_change_u32(0x12345678),   DGRAM_LENGTH,   endian_change_u16(0x1234)};
    packet.ethercat_datagram_header = test_ecat_dg_hdr_1;

    packet.data[0] = 0;
	packet.data[1] = 0;
	packet.data[2] = 0;
	packet.data[3] = 0;
    // working counter?
    int packet_length = sizeof(EthernetHeader) + sizeof(EthercatFrameHeader) + sizeof(EthercatDatagramHeader) + DGRAM_LENGTH + sizeof(WorkingCounter);
	raw_soc->send( (u_char *) &packet, packet_length);
}

void receive()
{
    raw_soc->receive();
}

void jauscat()
{
        //Part 1. Receive the JAUS message from Subsytem 1
        //Receiving the message
        char* msg = clientSetup->receiveMessage(JAUS_MESSAGE_HEADER_LENGTH 
            + SET_WRENCH_EFFORT_LENGTH);
        UINT16 command_code = endian_change_u16((msg[2] << 8) | msg[3]);
        SetWrenchEffortMessage * swe;
        //SetWrenchEffort
        if(command_code == 1029) {
        
            printf("\nSet Wrench Effort");
            printf("\n----------------------------------------");
            swe = (SetWrenchEffortMessage *) msg;
            printSetWrenchEffort(*swe);
        }
        
        //Part 2. Transfer the JAUS packet to functions.cpp and concatenate the packet into ethercat datagram data     
        jaus_packet = msg;
        jaus_packet_length = JAUS_MESSAGE_HEADER_LENGTH + (int)swe->jausMsgHdr.DataControl;
        
        LWR_1();
}