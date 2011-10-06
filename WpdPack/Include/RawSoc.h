#include<pcap.h>

class RawSoc
{
	pcap_t *pcap_handle;
	char errbuf[PCAP_ERRBUF_SIZE];
public:
    RawSoc::RawSoc(char * device);
    void send(u_char * ppacket, int size);
    void receive();
    ~RawSoc();
};