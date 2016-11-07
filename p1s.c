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
int main()
{
    struct sockaddr_in saddr,caddr;
    int sockfd, slen, clen,ads;
    sockfd = socket(AF_INET,SOCK_STREAM,0);
    slen = sizeof(saddr);
    bzero(&saddr, slen);
    saddr.sin_family = AF_INET;
    saddr.sin_addr.s_addr = INADDR_ANY;
    saddr.sin_port = htons(19000);
    bind(sockfd, (struct sockaddr *)&saddr,sizeof(saddr));
    listen(sockfd,5);
    printf("Listening...\n");
    while(1)
    {
	char c; int i=0,n,r;
	char fname[16];
	clen = sizeof(caddr);	
	int sd = accept(sockfd,(struct sockaddr*)&caddr,&clen);
	if(sd>0)
	{		
		char str[100];
		printf("Connected : ");
		inet_ntop(AF_INET, &caddr.sin_addr, str, sizeof(str));
         	printf("%s\n",str);
	}        
	int pid = fork();
	if(pid==0)
	{
		//close(sockfd);
		int count=0;
		int x = recv(sd,fname,sizeof(fname),0);
		fname[x]='\0';
		char buf[8];		
		printf("%s\n",fname);
		int fd = creat(fname,S_IRWXU);
		bzero(buf,sizeof(buf));		
		while(1)
		{
			r = recv(sd,buf,sizeof(buf),0);
			if(r<=0)
				break;
			n = write(fd,buf,r);
			if(n <= 0)
			{ 
			buf[n]='\0';
				break;
			}			
			count = count + n;
			bzero(buf,sizeof(buf));
			printf("\rReceived bytes %d",count);
		}
	}
	close(sd);
    }
}
