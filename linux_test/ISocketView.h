#pragma once
#ifndef ISOCKETVIEW_H
#define ISOCKETVIEW_H
#include "hpsocket/HPSocket.h"

//此处仅当教程使用 具体回传参数根据需求来定

class ISocketView
{
public:
    void GetCurTime(char* pszTime);
    virtual EnHandleResult onPrepareListen(ITcpClient* pSender, CONNID dwConnID, SOCKET socket) = 0;
    virtual EnHandleResult onAccept(ITcpClient* pSender, CONNID dwConnID) = 0;
    virtual EnHandleResult onReceive(ITcpClient* pSender, CONNID dwConnID, const BYTE* pData, int iLength) = 0;
    virtual EnHandleResult onSend(ITcpClient* pSender, CONNID dwConnID, const BYTE* pData, int iLength) = 0;
    virtual EnHandleResult onClose(ITcpClient* pSender, CONNID dwConnID, EnSocketOperation enOperation, int iErrorCode) = 0;
};
#endif // ISOCKETVIEW_H