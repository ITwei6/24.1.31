
#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <strings.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

using namespace std;

#include <iostream>
#include <strings.h>
#include <sys/types.h>
#include <cstring>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
using namespace std;
// 客户端
void Usage(std::string proc)
{
    std::cout << "\n\r./Usage: " << proc << " serverip serverport\n"
              << endl;
}
// 启动客户端时要求是： ./Client 服务器ip 服务器port
int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        Usage(argv[0]);
        exit(0);
    }
    std::string serverip = argv[1];
    uint16_t serverport = std::stoi(argv[2]);
     struct sockaddr_in server;
    bzero(&server, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr(serverip.c_str()); // 将string类型转换成int类型，并且是网络字节序
    server.sin_port = htons(serverport);
    socklen_t len = sizeof(server);
    
    // 1.创建套接字---本质就是打开网络文件
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0)
    {
        cout << "socket create err" << endl;
        return 1;
    }
    // 创建成功
    // 2.需要绑定吗？系统会给我自动绑定，首次发送的时候就会绑定

    // 3.往服务器的套接字里发送消息--需要知道服务器的ip和端口号,目的ip和目的port,将ip和port填入结构体对象里
   

    char outbuffer[1024];
    string message;
    while (true)
    {
        cout<<"Please enter@ ";
        getline(cin, message);
        //1.发送给服务器
        sendto(sockfd, message.c_str(), message.size(), 0, (const struct sockaddr *)&server, len);

        struct sockaddr_in temp;
        socklen_t l=sizeof(temp); 
        //2.接收服务器的应答
        
        ssize_t s=recvfrom(sockfd,outbuffer,1023,0,(struct sockaddr*)&temp,&l);
        if(s>0)
        {
        //接收成功
        outbuffer[s]=0;
        cout<<outbuffer<<endl;
        }
        
    }
    close(sockfd);
    return 0;
}
