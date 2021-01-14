#ifndef MYTCPLISTENER_H
#define MYTCPLISTENER_H
#include"hpsocket/HPSocket.h"
#include"pthread.h"
#include"BodyController.h"
class MyTcpListener:CTcpClientListener
{

public:
    static MyTcpListener* getInstance();
    CTcpClientPtr mClient;
    EnServiceState getStatus();
    //1.开启客户端
    bool startClient();

    //2.关闭服务器
    bool stopClient();
    void GetCurTime(char* countTime);
public:
    //监听成功时触发
    EnHandleResult OnPrepareConnect(ITcpClient* pSender, SOCKET soListen);

    //接受到连接时触发
    EnHandleResult OnConnect(ITcpClient* pSender, CONNID dwConnID);

    //握手成功时触发
    EnHandleResult OnHandShake(ITcpClient* pSender, CONNID dwConnID);

    //收到数据时触发
    EnHandleResult OnReceive(ITcpClient* pSender, CONNID dwConnID, const BYTE* pData, int iLength);

    //发送数据成功触发
    EnHandleResult OnSend(ITcpClient* pSender, CONNID dwConnID, const BYTE* pData, int iLength);


    //关闭某个连接时触发
    EnHandleResult OnClose(ITcpClient* pSender, CONNID dwConnID, EnSocketOperation enOperation, int iErrorCode);
private:
    //单例实现
    MyTcpListener();
    MyTcpListener(const MyTcpListener&);
    MyTcpListener& operator=(const MyTcpListener&);
    virtual ~MyTcpListener();
    class CGarbo                    //
    {
    public:
        CGarbo() {}
        ~CGarbo()
        {
            if (MyTcpListener::mClientListener)
            {
                delete MyTcpListener::mClientListener;
            }
        }
    };
    static CGarbo mCGarbo;
private:
    static MyTcpListener* mClientListener;
    static pthread_mutex_t g_mutex_lock;
    static BodyController bodycontroller;
};

#endif // MYTCPLISTENER_H