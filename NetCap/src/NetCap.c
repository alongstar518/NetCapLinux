#include <stdio.h>
#include "pthread.h"
#include "pcap.h"

int keepingCapture = 0;
char* CaptureOutFilePath = "/mrdvr/netcapture.pcap";
char* dev = "eth0", errbuffer[PCAP_ERRBUF_SIZE];
pcap_t *handle = NULL;
pcap_dumper_t *pd = NULL;


int CheckDeviceAvaliable(char* Device)
{
	dev = pcap_lookupdev(errbuffer);
	if (NULL == dev)
	{
		printf("Can not Determine Network Device.\n");
		return 0;
	}
	printf("Device: %s is ready for capture\n",dev);
	return 1;
}

int InitCapturePrecedure()
{
	handle = pcap_open_live(dev, BUFSIZ, 1, 1000, errbuffer);
	pd = pcap_dump_open(handle, CaptureOutFilePath);

	if (NULL == handle || NULL == pd)
	{
		printf("Error Init Capture Precedure handle=%d dump handle=%d\n",handle,pd);
		return 0;
	}
	printf("Success Init Capture Precedure handle=%d dump handle=%d\n",handle,pd);
	return 1;
}

int RunningCapture()
{
	printf("Capturing package to file:%s on device:%s\n",CaptureOutFilePath,dev);
	while (keepingCapture)
	{
		pcap_dispatch(handle, -1, &pcap_dump, (u_char*)pd);
	}
}

void *CaptureNetworkTraffic(void *vargp)
{
	keepingCapture = InitCapturePrecedure();
	if (keepingCapture)
	{
	    RunningCapture();
	}
	
	printf("Network Capture Stopped.\n");
	return NULL;
}

void StopCapture()
{
	keepingCapture = 0;
}


int main(int argc, char* argv[])
{
	pthread_t tid;
        if(argc == 2)
	{
		dev = argv[1];
        }
        if(argc == 3) 
	{
		dev = argv[1];
		CaptureOutFilePath = argv[2];
        }
	if (CheckDeviceAvaliable(dev) ==0)
	{
	    return -1;
	}
        pthread_create(&tid, NULL, CaptureNetworkTraffic,NULL);
        printf("Press Enter to stop Capture.\n");
	char c= getchar();
        StopCapture();
        pcap_dump_close(pd);
	return 0;
}

