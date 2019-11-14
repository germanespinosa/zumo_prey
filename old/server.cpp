// Server side C/C++ program to demonstrate Socket programming 
#include <unistd.h> 
#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h> 
#include<gcomm/gsocket.h>
#define PORT 8080 

void get (SocketGStream &sock, char *buffer){
    do{
      uint8_t byte = sock.get_byte();
      *buffer = (char) byte; 
    } while (*buffer++);
}

void set(SocketGStream &sock, char  *buffer){
  do{
    sock.set_byte((uint8_t) *buffer);
  } while (*buffer++);
}

int main(int argc, char const *argv[]) 
{ 
  {
    SocketGStream server(8080);

    char buffer[1024] = {0}; 
    get( server, buffer); 
    printf("%s\n",buffer ); 
    set(server,"Hello from server"); 
  }
  printf("Hello message sent\n"); 
  return 0; 
} 