//#include "uart.h"
//#include <wiringPiI2C.h>
//#include <wiringPi.h>
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <sstream>
#include <sys/stat.h>
#include <signal.h>
#include <libpixyusb2.h>

Pixy2        pixy;

static bool  run_flag = true;

void handle_SIGINT(int unused)
{
  // On CTRL+C - abort! //
  run_flag = false;
}

bool exists (const std::string& name) {
  struct stat buffer;   
  return (stat (name.c_str(), &buffer) == 0); 
}
/*
struct comm{
  private:
  unsigned char _buffer[255];
  PiSerial _serial;
  unsigned char _index;

  public:
  unsigned char *data;
  unsigned char len;
  comm()
    : _serial(PiSerial::mode::write_only, PiSerial::baudrate::b19200){
    data = _buffer + 1;
    len = 0;
  }
  void append(unsigned char c){
    data[_index++]=c;
    len=_index;
  }
  void clean(){
    _index=0;
  }
  bool write(){
    *_buffer=len;
    _serial.send(_buffer,len+1);
    _index=0;
    len = 0;
  }
};*/

int main(int argc, char *argv[])
{
  //comm serial;
  signal (SIGINT, handle_SIGINT);

  printf ("Connecting to Pixy2...");
  {
    int Result = pixy.init();
    if (Result < 0){
      printf ("Error\n");
      printf ("pixy.init() returned %d\n", Result);
      return Result;
    }
    printf ("Success\n");
  }
  while (run_flag)
  {
    pixy.ccc.getBlocks();
    if (pixy.ccc.numBlocks){
      int angle = (pixy.ccc.blocks[0].m_x * 60 / 320);
      printf ("Angle: %d\n", angle);
      //serial.append(angle);
      //serial.write();
    }
  }
}