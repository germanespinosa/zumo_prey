# if !defined(__PISERIAL_H__)
# define __PISERIAL_H__

#include <unistd.h>			//Used for uart
#include <fcntl.h>			//Used for uart
#include <termios.h>		//Used for uart
#include <string.h>
#include <fstream>

struct PiSerial {
  public:
  enum class mode{
    read_only = O_RDONLY,
    write_only = O_WRONLY,
    read_write = O_RDWR
  };
  enum class baudrate{
    b1200 = B1200,
    b2400 = B2400,
    b4800 = B4800,
    b9600 = B9600,
    b19200 = B19200,
    b38400 = B38400,
    b57600 = B57600,
    b115200 = B115200,
    b230400 = B230400,
    b460800 = B460800,
    b500000 = B500000,
    b576000 = B576000,
    b921600 = B921600,
    b1000000 = B1000000,
    b1152000 = B1152000,
    b1500000 = B1500000,
    b2000000 = B2000000,
    b2500000 = B2500000,
    b3000000 = B3000000,
    b3500000 = B3500000,
    b4000000 = B4000000
  };
  PiSerial(PiSerial::mode pmode, PiSerial::baudrate pbaudrate)
    : _mode(pmode), _baudrate(pbaudrate) { _open();}
  bool send (unsigned char* data, size_t len);
  size_t receive (unsigned char* data, size_t len);
  private:
    bool _open();
    int _handler;
    PiSerial::mode _mode;
    PiSerial::baudrate _baudrate;
  
};
#endif