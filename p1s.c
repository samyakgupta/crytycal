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

#include<stdio.h>
#include<string.h>
int search(char *pattern, char *file1)
{
	FILE *fp;
	if((fp=fopen(file1,"r"))==NULL)
		printf("Invalid File");
	else
	{
		char buffer[200];
		int line = 1, count=0;
		while(fgets(buffer,200,fp))
		{
			if(strstr(buffer,pattern))
			{
				//printf("%d.> %s",line, buffer);
				count++;
			}
			line++;
		}
		if(count==0)
			return 0;
		else
			return 1;
	}
}
int check(char *fname1,char *fname2) {
   FILE *fp1, *fp2;
   int ch1, ch2;

   fp1 = fopen(fname1, "r");
   fp2 = fopen(fname2, "r");
 
   ch1 = getc(fp1);
   ch2 = getc(fp2);
 
      while ((ch1 != EOF) && (ch2 != EOF) && (ch1 == ch2)) {
         ch1 = getc(fp1);
         ch2 = getc(fp2);
      }
      fclose(fp1);
      fclose(fp2);
      if (ch1 == ch2)
         return 1;
      else
	return 0; 
}
int exec_command(char *fname)
{
	int i;char c[2]=" ";
	for(i=0;i<strlen(fname);i++)
	{
		if(fname[i]=='.')
			break;
		c[0] = fname[i];
	}
	char input[20]="",output[20]="",fl[30]="",cmd1[100]="";
	strcat(input," input");
	strcat(output," serveroutput");
	strcat(input,c);	
	strcat(output,c);
	strcat(input,".txt");
	strcat(output,".txt");
	strcat(cmd1,"python checker1.py ");
	strcat(fl,fname);
	strcat(cmd1,fl);
	strcat(cmd1,input);
	strcat(cmd1,output);
	char *abc = "> result.txt";
	strcat(cmd1,abc);
	system(cmd1);
	int z = search("timeout","result.txt");
	if(z==0)
	{
		int x =check("result.txt","success.txt");
		return x;
	}
	else
		return 2;	
}
int main()
{
    struct sockaddr_in saddr,caddr;
    int sockfd, slen, clen,ads; long size=0;
    sockfd = socket(AF_INET,SOCK_STREAM,0);
    slen = sizeof(saddr);
    bzero(&saddr, slen);
    saddr.sin_family = AF_INET;
    saddr.sin_addr.s_addr = INADDR_ANY;
    saddr.sin_port = htons(17000);
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
		//printf("%ld",size);
		char buf[8];
		//printf("%s\n",fname);
		int fd = creat("add.c",S_IRWXU);
		bzero(buf,sizeof(buf));		
		while(1)
		{
			//printf("\n");			
			r = recv(sd,buf,sizeof(buf),0);
			//printf("\n");			
			n = write(fd,buf,r);			
			count = count + r;
			//printf("\n");
			if(count>=size)
				break;
			//bzero(buf,sizeof(buf));
			//printf("Received bytes %ld\n",count);
		}
		char suc[30]="";
		printf("File Uploaded\n");
		int c = exec_command(fname);
		if(c==1)
			strcat(suc,"Success!");
		else if(c==0)
			strcat(suc,"Wrong Answer");
		else
			strcat(suc,"Time Limit Exceeded!");
		printf("\n%s\n",suc);
		send(sd,suc,sizeof(suc),0);
		}
	   }
	}
    }
}
