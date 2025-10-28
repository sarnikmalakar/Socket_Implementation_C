// reference from system call manuel (man function_name)
#include<stdio.h>
#include<sys/types.h> //connect
#include<sys/socket.h> //socket
#include<arpa/inet.h> //inet_addr
#include<netinet/in.h> //ip
#include<unistd.h> //close
#include<sys/uio.h> //read
#include<string.h> //string

#define IP "142.250.76.67" //www.google.co.in
#define PORT 80 //default port to transfer data over Http

int main(){
    int s; // s is socket descriptor
    struct sockaddr_in sock; //socket address structure
    char buf[512]; //created a buffer to store response from server
    char *data; //pointer to HTTP request string

    data ="HEAD / HTTP/1.0\n\n"; //just a simple HTTP request

    //AF_INET - IPv4
    //SOCK_STREAM - TCP connection
    //0 - default to TCP
    s=socket(AF_INET,SOCK_STREAM,0);
    if(s<0){ //handling failed to create socket
        printf("Socket() error\n"); 
        return -1;
    }
    sock.sin_addr.s_addr = inet_addr(IP); //convert the IP string into a 32-bit binary value in network byte order
    sock.sin_port = htons(PORT); //converts host byte order to network byte order
    sock.sin_family = AF_INET; //sets the address family of socket to IPv4

    if(connect(s,(struct sockaddr *)&sock,sizeof(sock))!=0){
        printf("Connect() error\n");
        close(s); // close() used to close socket 
        return -1;
    }
    write(s,data,strlen(data)); //write(filedestination,pointer to http request, length of http request body)
    memset(buf,0,512); //memset used to clear out the garbage data to 0
    read(s,buf,511); //read(filedestination,buffer,buffer size)
    close(s);
    printf("\n%s\n",buf); // print out the value in buffer

}