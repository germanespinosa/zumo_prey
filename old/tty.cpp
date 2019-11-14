#include "uart.h"
#include <iostream>

int main(int argc, char *argv[])
{
  Uart serial(PiSerial::baudrate::b57600);
  std::string line = "";
  while (line != "quit")
  {
    std::getline(std::cin, line);
    if (line != "quit"){
      serial.write(line.c_str(), line.length() + 1);
      //u.send((unsigned char *)line.c_str(),line.length());
      //std::cout<<line;
    }
  }
}