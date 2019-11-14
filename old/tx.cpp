#include <gcomm/gcomm.h>
#include <gcomm/gsocket.h>
#include <iostream>
#include <unistd.h>

struct cmd{
  uint16_t x,y;
};

int main(int argc, char *argv[])
{
  int p=0;
  cmd h{1,100};
  
  SocketGStream serversocket(8081);
  GComm server(serversocket);
  while(true){
	   usleep(1000000);
      h.x++;
      h.y++;
      server.write(&h,sizeof(cmd));
      std::cout<<" sent :"<< h.x << "," << h.y << std::endl;
  }
}