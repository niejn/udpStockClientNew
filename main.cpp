#include <sys/types.h>
#include <sys/socket.h>                         // 包含套接字函数库
#include <stdio.h>
#include <netinet/in.h>                         // 包含AF_INET相关结构
#include <arpa/inet.h>                      // 包含AF_INET相关操作的函数
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <pthread.h>

#define MYPORT  4050
#define BUFFER_SIZE 1024

typedef struct
{
    int ab;
    int num[1000000];
}Node;

typedef struct
{
    char TradingDay[9];
    char InstrumentID[31];
    double LastPrice;
    int Volume;
}Ticker;

int main()
{
    int yes = 1;
    int status;
    ///sockfd
    int sock_cli = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);

    struct sockaddr_in servaddr;
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(MYPORT);
    servaddr.sin_addr.s_addr = htonl(INADDR_BROADCAST);
    int sinlen = sizeof(struct sockaddr_in);
//    if (connect(sock_cli, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
//    {
//        perror("connect");
//        exit(1);
//    }
    status = setsockopt(sock_cli, SOL_SOCKET, SO_BROADCAST, &yes, sizeof(int) );
    printf("Setsockopt Status = %d\n", status);



    //Node *myNode=(Node*)malloc(sizeof(Node));
    Ticker *myTicker=(Ticker*)malloc(sizeof(Ticker));
    myTicker->Volume = 1000;
    myTicker->LastPrice = 999.99;
    //sprintf(myTicker->InstrumentID, "test");
    strcpy(myTicker->InstrumentID, "testID");
    strcpy(myTicker->TradingDay, "testDay");
//    myNode->ab=123;
//    myNode->num[0]=110;
//    myNode->num[999999]=99;

    int needSend=sizeof(Ticker);
    char *buffer=(char*)malloc(needSend);
    memcpy(buffer,myTicker,needSend);
    //ticker_Size = siz
//    int pos=0;
//    int len=0;
    int sendTimes = 1000000;
    while(sendTimes > 0){
        sendTimes--;
        printf("send udp packet num %d\n", sendTimes);
        int pos=0;
        int len=0;

        status = sendto(sock_cli, buffer, BUFFER_SIZE, 0, (struct sockaddr *)&servaddr, sinlen);
        printf("send Status = %d\n", status);


        myTicker->LastPrice += 0.5;
        myTicker->Volume ++;
        memcpy(buffer,myTicker,needSend);
        sleep(1);
    }

    free(buffer);
    free(myTicker);
    close(sock_cli);
    printf("Send over!!!\n");
    return 0;
}