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
typedef struct f1
{
	char name[20];
	long size;
}fp;
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
    saddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    saddr.sin_port = htons(17000);
    slen = sizeof(saddr);
	int r=0;
    if((ads=connect(sockfd,(struct sockaddr *)&saddr,slen))<0)
    {
	printf("Exit \n");
	return 0;
    }
    while(1)
    {
    printf("\nEnter File name : ");
    char buff[16],buf1[8];int r;
    bzero(buff,16);
    gets(buff);
    int f = open(buff,O_RDONLY);
    off_t filesize  = lseek(f,0,SEEK_END);
    
    fp a;
    strcpy(a.name,buff);
    a.size = filesize;
    lseek(f,0,SEEK_SET);
    printf("File size : %ld , transferring..\n",a.size);
    send(sockfd,(fp *)&a,sizeof(a),0);
    if(f==-1)
	printf("Invalid File name\n");
    else
    {
    fstat(f, &stat_buf);	
    offset=0;
    sendfile(sockfd,f,&offset,stat_buf.st_size);
    printf("File Uploaded\n");
    printf("Checking....\n");
    char res[30];
    recv(sockfd,res,sizeof(res),0); 
    printf("\n%s\n",res);
    close(f);
    }
 }
}
