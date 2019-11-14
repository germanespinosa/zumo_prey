// Client side C/C++ program to demonstrate Socket programming 
#include <stdio.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <unistd.h> 
#include <string.h> 
#include <gcomm/gsocket.h>
#define PORT 8080 


int connect (){
    int sock = 0; 
    struct sockaddr_in serv_addr;
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
    { 
        printf("\n Socket creation error \n"); 
        return -1; 
    } 
   
    serv_addr.sin_family = AF_INET; 
    serv_addr.sin_port = htons(PORT); 
       
    // Convert IPv4 and IPv6 addresses from text to binary form 
    if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0)  
    { 
        printf("\nInvalid address/ Address not supported \n"); 
        return -1; 
    } 
   
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) 
    { 
        printf("\nConnection Failed \n"); 
        return -1; 
    } 
    return sock;
}

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
    SocketGStream server("127.0.0.1",8080);
    set(server, "Hello from client");
    printf("Hello message sent\n"); 
    char buffer[1024] = {0}; 
    get(server,buffer);
    printf("%s\n",buffer ); 
    return 0; 
} 