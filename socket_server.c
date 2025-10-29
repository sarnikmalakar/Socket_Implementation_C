#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<unistd.h>
#include<sys/uio.h>
#include<string.h> 

#define PORT 8181

int main(){
    int s,c;
    socklen_t addrlen; 
    struct sockaddr_in srv,cli;
    char buf[512];
    char *data;

    addrlen=0;

    memset(&srv,0,sizeof(srv));
    memset(&cli,0,sizeof(cli));

    s= socket(AF_INET,SOCK_STREAM,0);
    if(s<0){
        printf("Socket() error\n");
        return -1;
    }
    srv.sin_family = AF_INET;
    srv.sin_addr.s_addr = 0;
    srv.sin_port = htons(PORT);

    if(bind(s,(const struct sockaddr *)&srv,sizeof(srv))){
        printf("Bind() error\n");
        close(s);
        return -1;
    }

    if(listen(s,5)){
        printf("Listen() error\n");
        close(s);
        return -1;
    }
    printf("Listning on 0.0.0.0:%d\n",PORT);

    c = accept(s,(struct sockaddr *)&srv,&addrlen);
    if(c<0){
        printf("Accept() fail\n");
        close(s);
        close(c);
        return -1;
    }
    printf("Client connected\n");
    memset(buf,0,512);
    read(c,buf,511);
    data="httpd v1.0\n";
    write(c,data,strlen(data));
    close(c);
    close(s);
    return 0;

}