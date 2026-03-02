#include "variable.h"

char buffUART[MAX_PACKETSIZE];
unsigned int buffUARTIndex = 0;
unsigned long preUARTTick = 0;


char ssid[] = "usdguest"; // replace ****** with your network SSID (name)
char pass[] = ""; // replace ****** with your network password
int status = WL_IDLE_STATUS;
char packetBuffer[5]; 
WiFiEspUDP Udp;
unsigned int localPort = 8888;  // local port to listen on