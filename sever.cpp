#include <stdio.h>
#include <winsock2.h>
#include <windows.h>
#define NUM 1024
SOCKET clientsocket[NUM];
void tongxin(int idx);
int count;//接入数量

int main ()
{
    count = 0;//服务器数量
// 1.确定服务器版本
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2,2),&wsaData);
    if (LOBYTE(wsaData.wVersion)!=2||
        HIBYTE(wsaData.wVersion)!=2)//判断最低和最高的服务器版本是否正确
    {
        printf("确定玩过版本失败:%s \n",GetLastError());//获取错误原因
        system("pause");
        return -1;
    }
    printf("确定玩过版本成功\n");
// 2.创建socket
    SOCKET serverSocket = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
    if (-1 == serverSocket)//-1 代表错误
    {
        printf("确定失败");
        WSACleanup();//清理版本信息
        system("pause");
        return -1;
    }
    printf("确定socket成功\n");


// 3.确定服务器协议地址
    SOCKADDR_IN addr = { 0 };
    addr.sin_family = AF_INET;//指定ip地址为本人IP v4
    addr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");//IP地址
    addr.sin_port = htons(9527);//端口

// 4.绑定

    int r = bind (serverSocket,(struct sockaddr *)&addr,sizeof addr);
    //int r = bind(serverSocket,(sockaddr * )&addr,sizeof addr);
// 5.监听
    r = listen (serverSocket,10);
    if (-1 == r)//-1 代表错误
    {
        printf("监听失败");
        GetLastError();//错误信息
        system("pause");
        return -1 ; 
    }
    printf("监听成功\n");
// 6.接受客户端连接
    for (int i = 0; i < NUM; i++)
    {
        clientsocket[i]=accept(serverSocket,NULL,NULL);
        printf("有客户端连接\n");
        count++;
        CreateThread (NULL,NULL,(LPTHREAD_START_ROUTINE)tongxin,(LPVOID)i,NULL,NULL);
    };



}

void tongxin(int idx)
{
// 7.通信
int r;
char buff[56];
char temp[80];
    while (1)
    {
        r = recv(clientsocket[idx],buff,55,0);//接受消息
        if (r>0)
        {
            buff[r] = 0;//最后一个为结束符号
            printf(">> %s \n",buff);
            memset(temp,0,80);
            sprintf(temp,"%d:%s",idx,buff);
            //发送给所有的客户端
            for (int  i = 0; i < count; i++)
            {
                send(clientsocket[i],temp,strlen(temp),NULL);
                
            }
            
        }
        
    }
    
}
