#include "mqtt_func.h"
#include "signal.h"
#include "stdio.h"
#include "string.h"

/* Include MQTT library */
#include "mqtt_interface.h"
#include "MQTTClient.h"

#define TCP_SOCKET      0
#define BUFFER_SIZE	2048

unsigned char tempBuffer[BUFFER_SIZE] = {0};

unsigned char targetIP[4] = {192,168,1,234};
unsigned int targetPort = 1883;

volatile int toStop = 0;
void cfinish(int sig)
{
  signal(SIGINT, NULL);
  toStop = 1;
}

struct opts_struct
{
	char* clientid;
	int nodelimiter;
	char* delimiter;
	enum QoS qos;
	char* username;
	char* password;
	char* host;
	int port;
	int showtopics;
} opts =
{ 
  (char*)"subscriber", 0, (char*)"\n", QOS0, "admin", "admin123", (char*)"localhost", 1883, 0 
};

void ConnectToServer (void)
{
    int rc = 0;
    MQTTClient c;
    Network n;
    
    NewNetwork(&n, TCP_SOCKET);
    ConnectNetwork(&n, targetIP, targetPort);
    
    unsigned char buf[100];
    MQTTClientInit(&c, &n, 1000, buf, 100, tempBuffer, 2048);
    
    //LWT can dang ki truoc khi connect
    //data for will
    char payload_will[100];
    sprintf(payload_will, "Invalid disconnection!!!");
    
    MQTTPacket_willOptions will_data = MQTTPacket_willOptions_initializer;
    will_data.retained = 0;
    will_data.qos = QOS0;
    will_data.topicName.cstring = "abc";
    will_data.message.cstring = payload_will;
    
    
    //data for connect
    MQTTPacket_connectData data =  MQTTPacket_connectData_initializer;
    data.willFlag = 0;
    data.MQTTVersion = 3;
    
    data.clientID.cstring = opts.clientid;
    data.username.cstring = opts.username;
    data.password.cstring = opts.password;
    
    data.will = will_data;
    data.willFlag = 1;
    data.keepAliveInterval = 10;
    data.cleansession = 1;
    
    rc = MQTTConnect(&c, &data);
    printf("Connected %d\r\n", rc); //Co the bo qua dong nay
    opts.showtopics = 1;
    
    //data for message
    char payload[100];
    sprintf(payload, "Hello broker");
    
    MQTTMessage msg;
    msg.payload = payload;
    msg.payloadlen = strlen(payload) + 1;
    msg.qos = QOS0;
    msg.retained = 0;
    
    rc = MQTTPublish(&c, "abc", &msg);
    
    while(!toStop)
    {
      MQTTYield(&c,data.keepAliveInterval);
    }
    
    MQTTDisconnect(&c);
    //NetworkDisconnect(&n);
}