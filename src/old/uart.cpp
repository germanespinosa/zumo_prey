#include "uart.h"
#include <iostream>

#define UART_BUFFER_LENGTH 512
#define UART_INC(var) ( var++ % UART_BUFFER_LENGTH )
#define UART_RX_PENDING ( _uart_rx_offset >= _uart_rx_next ? _uart_rx_offset - _uart_rx_next : _uart_rx_next - _uart_rx_offset )
#define UART_GETBYTE ( _uart_rx_buffer[UART_INC(_uart_rx_next)] )

uint8_t _uart_rx_buffer[UART_BUFFER_LENGTH];
uint16_t _uart_rx_offset = 0;
uint16_t _uart_rx_next = 0;
uint16_t _uart_rx_lost = 0 ;


Uart::Uart(PiSerial::baudrate baudrate)
:_piserial(PiSerial::mode::read_write, baudrate)
{
  _length = 0;    
  _rx_thread = std::thread (update_rx_buffer, std::ref(*this));
}

void Uart::update_rx_buffer(Uart &uart){
  timeval last_byte;
  uint8_t data;
  while (true){
    int r = uart._piserial.receive(&data, 1);
    if (r==1){
      timeval current_time;
      gettimeofday(&current_time, NULL);
      double elapsed=(double) (current_time.tv_usec - last_byte.tv_usec) / 1000000+             (double) (current_time.tv_sec - last_byte.tv_sec);      
      last_byte = current_time;
      if (elapsed>.0005) { 
        _uart_rx_offset = 0;
        _uart_rx_next = 0;
        uart._length=0;
        _uart_rx_lost++;
      }
      _uart_rx_buffer[_uart_rx_offset]=data;
      UART_INC(_uart_rx_offset);
    }
  }
}

void Uart::write(const void *data, uint8_t size){
  uint8_t cs = 0;
  unsigned char *data_c= (unsigned char *) data;
  for (int index = 0;index < size;index++)
    cs = cs^data_c[index];
  _piserial.send(&size,1);
  _piserial.send((unsigned char *)data_c,size);
  _piserial.send(&cs,1);
}

uint8_t Uart::read(void *dest, uint8_t maxsize ){
  uint16_t pending = UART_RX_PENDING;
  if (pending){
    if (!_length){
      _length = UART_GETBYTE;
    }
    if( pending > _length )
    {
      uint8_t *dest_c = (uint8_t *) dest;
      uint8_t cs = 0;
      for (int index=0;index<_length;index++){
        if (index<maxsize)
        dest_c[index] = UART_GETBYTE;
        cs = cs ^ dest_c[index];
      }
      uint8_t l = _length;
      _length = 0;
      return cs == UART_GETBYTE ? l:0;
    }
  }
  return 0;  
}