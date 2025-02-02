#include<pthread.h>
#include<errno.h>
#include<stdio.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>


void *client_thread(void *arg)
{
		int clientfd = *(int *)arg;
		while(1){
			char buffer[1024]={0};
			int count = recv(clientfd,buffer,1024,0);
			printf("RECV: %s\n",buffer);
			
			count = send(clientfd,buffer,count,0);
			printf("send: %d\n",count);
		}
}


int main()
{
	int sockfd = socket(AF_INET,SOCK_STREAM,0);//用于listen

	struct sockaddr_in servaddr;

	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);//0.0.0.0
 	servaddr.sin_port = htons(2000);//0-1023
	if(-1 == bind(sockfd,(struct sockaddr*)&servaddr,sizeof(struct sockaddr))){
		printf("bind failed: %s\n",strerror(errno));
	}
	listen(sockfd,10);
	printf("listen finished\n");

	struct sockaddr_in clientaddr;
	socklen_t len=sizeof(clientaddr);

#if 0

	printf("accept\n");
	int clientfd = accept(sockfd,(struct sockaddr*)&clientaddr,&len);
	printf("accept finished\n");

	char buffer[1024]={0};
	int count = recv(clientfd,buffer,1024,0);
	printf("RECV: %s\n",buffer);
	
	count = send(clientfd,buffer,count,0);
	printf("send: %d\n",count);

#elif 0
	while(1){
		printf("accept\n");
		int clientfd = accept(sockfd,(struct sockaddr*)&clientaddr,&len);
		printf("accept finished\n");

		char buffer[1024]={0};
		int count = recv(clientfd,buffer,1024,0);
		printf("RECV: %s\n",buffer);
		
		count = send(clientfd,buffer,count,0);
		printf("send: %d\n",count);
	}

#else
		while(1){
			printf("accept\n");
			int clientfd = accept(sockfd,(struct sockaddr*)&clientaddr,&len);
			printf("accept finished\n");
			pthread_t thid;
			pthread_create(&thid,NULL,client_thread,&clientfd);
		
		}
#endif 
	
	getchar();	

	printf("exit\n");
	return 0;

}		

