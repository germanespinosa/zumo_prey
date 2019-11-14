#include <gcomm/gcomm.h>
#include <gcomm/guart.h>
#include <gcomm/gsocket.h>
#include <iostream>
struct cmd{
  uint16_t x,y;
};

int main(int argc, char *argv[])
{
  int p=0;
  cmd h{0,0};
  
  //std::cout << "opening serial..." << std::endl;
  //UartGStream serial(UartGStream::baudrate::b57600);
  //std::cout << "opened" << std::endl;
  std::cout << "connecting to server..." << std::endl;
  SocketGStream clientsocket("127.0.0.1",8081);
  std::cout << "connected" << std::endl;
  //GComm gcomm(serial,200000);
  GComm client(clientsocket);
  h.x=0;
  h.y=10;
  //gcomm.write(&h,sizeof(cmd));
  while(true){
      if (client.read(&h,sizeof(cmd))==sizeof(cmd))
      {
        //gcomm.write(&h,sizeof(cmd));
        std::cout<<" received :"<< h.x << "," << h.y << std::endl;
      }
    }
}