#include <gcomm/gcomm.h>
#include <gcomm/gmemconnector.h>
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
  GMemConnector client(8081,GMemConnector::mode::slave);
  std::cout << "connected" << std::endl;
  //GComm gcomm(serial,200000);
  GComm <cmd, cmd> comm (client);
  h.x=0;
  h.y=10;
  //gcomm.write(&h,sizeof(cmd));
  while(true){
      if (comm.read_object(h))
      {
        //gcomm.write(&h,sizeof(cmd));
        std::cout<<" received :"<< h.x << "," << h.y << std::endl;
      }
    }
}