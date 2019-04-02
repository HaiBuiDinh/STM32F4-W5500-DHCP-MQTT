#include "socket.h"
#include "server.h"

#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#include "wizchip_conf.h"
#include "w5500.h"
#include "dhcp.h"

void server_init(void)
{
  //define input parameters
  uint8_t  socket_sn = 0;
  uint8_t  socket_protocol = Sn_MR_TCP;
  uint16_t socket_port = 2525;
  uint8_t  socket_flag = 0x00;
  
  //buffer received
  //uint8_t buff_recv[2] = {0};
  socket(socket_sn, socket_protocol, socket_port, socket_flag);
  
  while (getSn_SR(socket_sn) != SOCK_INIT)
    
  //listenning connect from client
  listen(socket_sn);


}

