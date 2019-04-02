#include "client.h"
#include "socket.h"

#include "stdio.h"
#include "stdlib.h"
#include "string.h"

void client_init(void)
{
  //define input parameters
  uint8_t  client_sn = 0;
  uint8_t  client_protocol = Sn_MR_TCP;
  uint16_t client_port = 2727;
  uint8_t  client_flag = 0;
  
//Opend socket 0  
  socket(client_sn, client_protocol, client_port, client_flag);
  
  while(getSn_SR(client_sn) != SOCK_INIT);
}