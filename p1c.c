#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>
#include<arpa/inet.h>
#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include <fcntl.h>
#include<unistd.h>
#include<sys/stat.h>
int main()
{
    struct stat stat_buf;
	off_t offset = 0;      
   struct sockaddr_in saddr,caddr;
    int sockfd, slen, clen,ads;
    sockfd = socket(AF_INET,SOCK_STREAM,0);
    slen = sizeof(saddr);
    bzero(&saddr, slen);
    saddr.sin_family = AF_INET;
    saddr.sin_addr.s_addr = inet_addr("192.168.43.111");
    saddr.sin_port = htons(19000);
    slen = sizeof(saddr);
	int r=0;
    if((ads=connect(sockfd,(struct sockaddr *)&saddr,slen))<0)
    {
	printf("Exit \n");
	return 0;
    }
    while(1)
    {
    printf("\nEnter File name :");
    char buff[16],buf1[8];int r;
    bzero(buff,16);
    gets(buff);
    send(sockfd,buff,sizeof(buff),0);
    int f = open(buff,O_RDONLY);
    if(f==-1)
	printf("Invalid File name");
    else
    {
     printf("Valid File");
    fstat(f, &stat_buf);	
    offset=0;
    sendfile(sockfd,f,&offset,stat_buf.st_size);
    printf("Send Successful");
    close(f);
    }
 }
}
