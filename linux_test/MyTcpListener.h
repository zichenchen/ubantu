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
    //1.�����ͻ���
    bool startClient();

    //2.�رշ�����
    bool stopClient();
    void GetCurTime(char* countTime);
public:
    //�����ɹ�ʱ����
    EnHandleResult OnPrepareConnect(ITcpClient* pSender, SOCKET soListen);

    //���ܵ�����ʱ����
    EnHandleResult OnConnect(ITcpClient* pSender, CONNID dwConnID);

    //���ֳɹ�ʱ����
    EnHandleResult OnHandShake(ITcpClient* pSender, CONNID dwConnID);

    //�յ�����ʱ����
    EnHandleResult OnReceive(ITcpClient* pSender, CONNID dwConnID, const BYTE* pData, int iLength);

    //�������ݳɹ�����
    EnHandleResult OnSend(ITcpClient* pSender, CONNID dwConnID, const BYTE* pData, int iLength);


    //�ر�ĳ������ʱ����
    EnHandleResult OnClose(ITcpClient* pSender, CONNID dwConnID, EnSocketOperation enOperation, int iErrorCode);
private:
    //����ʵ��
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