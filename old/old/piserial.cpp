#include "piserial.h"
#include <iostream>
bool PiSerial::_open ()
{
  _handler = -1;
  _handler = open("/dev/serial0", ((int)_mode) | O_NOCTTY | O_NDELAY);		//Open in non blocking read/write mode
  if (_handler<0) return false;
  struct termios options;
  tcgetattr(_handler, &options);
  options.c_cflag = ((int)_baudrate) | CS8 | CLOCAL | CREAD;//<Set baud rate
  options.c_iflag = IGNPAR;
  options.c_oflag = 0;
  options.c_lflag = 0;
  tcflush(_handler, TCIFLUSH);
  tcsetattr(_handler, TCSANOW, &options);
  return true;
}

bool PiSerial::send (unsigned char* data, size_t len) {
    return write(_handler, data, len) == len;
}

size_t PiSerial::receive (unsigned char* rx_buffer, size_t len) {
    int rx_length = read(_handler, (void*)rx_buffer, len);		//Filestream, buffer to store in, number of bytes to read (max)
    if (rx_length <= 0)
        return 0; // no data or error
    else
        return rx_length; //Bytes received
}

