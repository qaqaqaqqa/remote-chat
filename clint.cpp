#include <stdio.h>
#include <winsock2.h>
#include <windows.h>

int main ()
{
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

// 4.连接服务器

    int r = connect(serverSocket,(sockaddr*)&addr,sizeof addr);
    if (-1 ==r)
    {
        printf("服务器连接失败 \n");
        GetLastError ();
        closesocket (serverSocket);
        WSACleanup();
        system("pause");
        return -1;
    }
    printf("服务器连接成功 \n");
    
//7.通信
//循环接受，发送到服务器
char buff[56];
while (1)
{
    scanf ("%s",buff);
    send (serverSocket,buff,strlen(buff),NULL);
    
}

// 8.关闭socket
    closesocket (serverSocket);
// 9.清理协议版本信息


}