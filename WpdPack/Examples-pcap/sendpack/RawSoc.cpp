#include <pcap.h>
#include "RawSoc.h"

/* Open the adapter */
RawSoc::RawSoc(char * device)
{
	if ((pcap_handle = pcap_open_live(device,		// name of the device
        							  65536,		// portion of the packet to capture. It doesn't matter in this case 
		        					  1,			// promiscuous mode (nonzero means promiscuous)
				        			  1000,			// read timeout
						        	  errbuf		// error buffer
							          )) == NULL)
	{
		fprintf(stderr,"\nUnable to open the adapter. %s is not supported by WinPcap\n", device);
	}
}

/* Send down the packet */
void RawSoc::send(u_char * ppacket, int size)
{
	if (pcap_sendpacket(pcap_handle,	        // Adapter
		                ppacket,	// buffer with the packet
		                size        // size of the packet
                        ) != 0)
	{
		fprintf(stderr,"\nError sending the packet: %s\n", pcap_geterr(pcap_handle));
	}
	else{printf("Data is sent successfully !\n");}
}

void RawSoc::receive()
{
	int res;
	struct tm *ltime;
	char timestr[16];
	struct pcap_pkthdr *header;
	const u_char *pkt_data;
	time_t local_tv_sec;

    /* Retrieve the packets */
	while((res = pcap_next_ex( pcap_handle, &header, &pkt_data)) >= 0)
    {	
		if(res == 0)
			/* Timeout elapsed */
			break;
		
		/* convert the timestamp to readable format */
		local_tv_sec = header->ts.tv_sec;
		ltime=localtime(&local_tv_sec);
		strftime( timestr, sizeof timestr, "%H:%M:%S", ltime);
		
		printf("%s,%.6d len:%d\n", timestr, header->ts.tv_usec, header->len);
	}
	
	if(res == -1)
    {
		printf("Error reading the packets: %s\n", pcap_geterr(pcap_handle));
//		return -1;
	}
}

/* Close the Adapter */
RawSoc::~RawSoc()
{
	pcap_close(pcap_handle);	
}
