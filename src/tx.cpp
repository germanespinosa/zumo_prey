#include <gcomm/gcomm.h>
#include <gcomm/gsocket.h>
#include <gcomm/gmemconnector.h>
#include <iostream>
#include <unistd.h>

struct cmd{
  uint16_t x,y;
};

int main(int argc, char *argv[])
{
  int p=0;
  cmd h{1,100};
  
  GMemConnector server(8081, GMemConnector::mode::master);
  GComm<cmd,cmd> comm(server);
  while(true){
      usleep(100000);
      h.x++;
      h.y++;
      comm.write_object(h);
      std::cout<<" sent :"<< h.x << "," << h.y << std::endl;
  }
}