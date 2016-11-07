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
typedef struct f1
{
	char name[20];
	long size;
}fp;
int main()
{
    struct sockaddr_in saddr,caddr;
    int sockfd, slen, clen,ads; long size=0;
    sockfd = socket(AF_INET,SOCK_STREAM,0);
    slen = sizeof(saddr);
    bzero(&saddr, slen);
    saddr.sin_family = AF_INET;
    saddr.sin_addr.s_addr = INADDR_ANY;
    saddr.sin_port = htons(13000);
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
	int pid = fork();
	if(pid==0)
	{
		while(1)
		{
		//close(sockfd);
		long count=0; fp a;
		int x = recv(sd,(fp *)&a,sizeof(a),0);
		strcpy(fname,a.name);	
		long size = a.size;
		fname[x]='\0';
		printf("%ld",size);
		char buf[8];
		printf("%s\n",fname);
		int fd = creat("qwerty.txt",S_IRWXU);
		bzero(buf,sizeof(buf));		
		while(1)
		{
			printf("Printing 1\n");			
			r = recv(sd,buf,sizeof(buf),0);
			printf("Printing 2\n");			
			n = write(fd,buf,r);			
			count = count + r;
			printf("Count\n");
			if(count>=size)
				break;
			//bzero(buf,sizeof(buf));
			printf("Received bytes %ld\n",count);
		}
		printf("Done!!\n");
		}
	}
	}
    }
}
