#include "piserial.h"
#include<thread>
#include<mutex>
#include <sys/time.h>

struct Uart{
  public:
    Uart(PiSerial::baudrate baudrate);
    uint8_t read(void *, uint8_t maxsize);
    void write(const void *, uint8_t);
    static void update_rx_buffer(Uart &);
    PiSerial _piserial;
    uint8_t _length;

  private:
    std::thread _rx_thread;
};