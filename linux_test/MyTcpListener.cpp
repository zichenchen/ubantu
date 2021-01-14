
#include <iostream>
#include <sys/time.h>
#include"MyTcpListener.h"
#include <string.h>
#include"CommonUtil.h"
#include"timertask.h"


using namespace std;



MyTcpListener* MyTcpListener::mClientListener = nullptr;
pthread_mutex_t MyTcpListener::g_mutex_lock;
BodyController MyTcpListener::bodycontroller;
MyTcpListener::MyTcpListener()
    :mClient(this)//要想监听生效 这个必须传入监听者对象
{

}


MyTcpListener::~MyTcpListener()
{

}

MyTcpListener* MyTcpListener::getInstance()
{
    MyTcpListener* tmp = mClientListener;
    if (tmp == nullptr)
    {
        pthread_mutex_lock(&g_mutex_lock);
        tmp = mClientListener;
        if (tmp == nullptr)
        {
            tmp = new MyTcpListener();
            mClientListener = tmp;
        }
    }
    return mClientListener;
}

void MyTcpListener::GetCurTime(char* pszTime)
{
    struct timeval tv;
    gettimeofday(&tv, NULL);

    struct tm tm = { 0 };
    localtime_r(&tv.tv_sec, &tm);

    unsigned int nYear = tm.tm_year + 1900;
    unsigned int nMon = tm.tm_mon + 1;
    unsigned int nDay = tm.tm_mday;

    unsigned int nHour = tm.tm_hour;
    unsigned int nMin = tm.tm_min;
    unsigned int nSec = tm.tm_sec;
    unsigned int uSec = tv.tv_usec / 1000;

    sprintf(pszTime, "[%04d-%02d-%02d %02d:%02d:%02d.%03d]", nYear, nMon, nDay, nHour, nMin, nSec, uSec);
}

bool MyTcpListener::startClient()
{
    

    return mClient->Start("192.168.0.61", 8888,TRUE,"0.0.0.0",7780);
}

bool MyTcpListener::stopClient()
{
    return mClient->Stop();
}

EnServiceState MyTcpListener::getStatus() {

    return mClient->GetState();
}


EnHandleResult MyTcpListener::OnPrepareConnect(ITcpClient* pSender, SOCKET soListen)
{
   
  
    return HR_OK;
}

EnHandleResult MyTcpListener::OnConnect(ITcpClient* pSender, CONNID dwConnID)
{
    TCHAR szAddress[50] = { 0 };
    int iAddressLen = sizeof(szAddress) / sizeof(TCHAR);
    USHORT usPort = 0;

    BOOL bResult = FALSE;
    bResult = pSender->GetRemoteHost(szAddress, iAddressLen, usPort);

    TCHAR szPort[8] = { 0 };
    sprintf(szPort, "%d", usPort);

    string strText = "连接成功：连接地址=";
    strText += szAddress;
    strText += " 连接端口=";
    strText += szPort;

    cout << strText << endl;

    return bResult ? HR_OK : HR_ERROR;
 
}

EnHandleResult MyTcpListener::OnHandShake(ITcpClient* pSender, CONNID dwConnID)
{
  

    return HR_OK;
}

EnHandleResult MyTcpListener::OnReceive(ITcpClient* pSender, CONNID dwConnID, const BYTE* pData, int iLength)
{
    /*CPU_OCCUPY* cpu_occupy;
    get_cpuoccupy((CPU_OCCUPY*)&cpu_occupy);
    t.StartTimer(10, std::bind(getcpuuserlv, cpu_occupy));*/

    char szTime[32] = { 0 };
    this->GetCurTime(szTime);
    cout << szTime << "OnReceive dwConnID=" << dwConnID << " Len=" << iLength  << endl;

     char msg_len_p[4];
    memcpy(msg_len_p,pData, 4);

    int msg_len = bytes2T<int>(msg_len_p);
    char msg_type_p[20];
    memcpy(msg_type_p, pData+4, 20); 
 
   
   /* if (msg_len != iLength - sizeof(int)) {
        return HR_ERROR;
    }else{*/
    char buffer[msg_len - 20];
    memcpy(buffer, pData + 24, sizeof(buffer));
 
    enumType msg_type = Msgtype_match(msg_type_p);
    bodycontroller.action(msg_type, buffer,msg_len);
    
    return HR_OK;
}



EnHandleResult MyTcpListener::OnSend(ITcpClient* pSender, CONNID dwConnID, const BYTE* pData, int iLength)
{
  

    char szTime[32] = { 0 };
    this->GetCurTime(szTime);

    cout << szTime << "OnSend dwConnID=" << dwConnID << " Len=" << iLength << endl;

    return HR_OK;
}


EnHandleResult MyTcpListener::OnClose(ITcpClient* pSender, CONNID dwConnID, EnSocketOperation enOperation, int iErrorCode)
{
    cout << "OnClose";

    EnServiceState State = pSender->GetState();

    cout << " CurState=" << State << endl;

    return HR_OK;
}

