# if !defined(__GCOMM_H__)
# define __GCOMM_H__

#include <stdint.h>
#include <thread>
#include <mutex>
#define BUFFERLENGTH 1024

struct GStream{
  public:
    virtual uint8_t get_byte() = 0;
    virtual void set_byte(uint8_t) = 0;
};

struct GComm{
  public:
    GComm(GStream &, uint64_t);
    GComm(GStream &);
    uint16_t read(void *, uint16_t);
    void write(const void *, uint16_t);
    bool time_out();
  private:
    uint8_t get_byte();
    bool set_byte(uint8_t);
    GStream &_stream;
    uint16_t _rx_length;
    uint16_t _pending();
    static void _rx_update_(GComm&);
    static void _tx_update_(GComm&);
    std::thread _rx_thread;
    std::thread _tx_thread;
    uint8_t _rx_buffer[BUFFERLENGTH];
    uint16_t _rx_offset;
    uint16_t _rx_next;
    uint8_t _tx_buffer[BUFFERLENGTH];
    uint16_t _tx_offset;
    uint16_t _tx_next;
    uint64_t _timeout;
    std::mutex _rx_buffer_access;
};
#endif